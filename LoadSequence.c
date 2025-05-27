//GPT-based pure c for loading pulseq files. 
//Designed to be easier to integrate into method loading. 
//need to include many additional functions/features from ExternalSequences.cpp



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LoadSequence.h"


// GLOBAL STORAGE; these will move to paravision variables in the sequence method
Version version;
Definitions defs;
BLOCKTABLE SeqBlockTable; 
RFTABLE SeqRFTable; 
TRAPTABLE SeqTrapTable; 
ADCTABLE SeqADCTable; 
SHAPE SeqShapes[MAX_SHAPES]; 
GRADSHAPE SeqGradients[MAX_SHAPES]; 


int Seq_NBlocks = 0;
int Seq_NRF = 0;
int Seq_NTrap = 0;
int Seq_NADC = 0;
int Seq_NShapes = 0;
int Seq_NGrad = 0;

// Function to trim newline characters from a string
void trim_newline(char *line) {
    line[strcspn(line, "\r\n")] = 0;
}

// Function to free allocated memory for shapes
void free_shapes() {
    for (int i = 0; i < Seq_NShapes; i++) {
        free(SeqShapes[i].samples);
    }
}


void UpdateSeq(void) {

    for (int i = 0; i < Seq_NShapes; i++) {
        char filename[64];
        snprintf(filename, sizeof(filename), "pulseq_shape_%d.exc", SeqShapes[i].id);
        WriteShapeToExp(SeqShapes[i], filename);
    }

    // Convert trapezoids to gradient shapes
    double gradrastertime = 8e-6; // in seconds
    GradTrapToGradShape(gradrastertime);
}

// Function to load a sequence file
int LoadSequenceFile(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    char line[MAX_LINE], section[MAX_LINE] = "";
    int shape_sample_mode = 0; // if > 0, we're in SHAPES data
    int num_loaded = 0; // Count of loaded samples
    SHAPE *curr_shape = NULL;
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (line[0] == '#' || strlen(line) == 0)
            continue;

        if (line[0] == '[') {
            strncpy(section, line, sizeof(section));
            shape_sample_mode = 0;
            continue;
        }

        if (strcmp(section, "[VERSION]") == 0) {
            sscanf(line, "major %d", &version.major);
            sscanf(line, "minor %d", &version.minor);
            sscanf(line, "revision %d", &version.revision);
        } else if (strcmp(section, "[DEFINITIONS]") == 0) {
            sscanf(line, "FOV %lf %lf %lf", &defs.FOV[0], &defs.FOV[1], &defs.FOV[2]);
            sscanf(line, "GradientRasterTime %lf", &defs.GradientRasterTime);
        } else if (strcmp(section, "[BLOCKS]") == 0) {
            if (Seq_NBlocks < MAX_BLOCKS) {
                int num, dur, rf, gx, gy, gz, adc, ext;
                if (sscanf(line, "%d %d %d %d %d %d %d %d",
                    &num, &dur, &rf, &gx, &gy, &gz, &adc, &ext) == 8) { 
                    SeqBlockTable.num[Seq_NBlocks] = num;
                    SeqBlockTable.dur[Seq_NBlocks] = dur;
                    SeqBlockTable.rf[Seq_NBlocks] = rf;
                    SeqBlockTable.gx[Seq_NBlocks] = gx;
                    SeqBlockTable.gy[Seq_NBlocks] = gy;
                    SeqBlockTable.gz[Seq_NBlocks] = gz;
                    SeqBlockTable.adc[Seq_NBlocks] = adc;
                    SeqBlockTable.ext[Seq_NBlocks] = ext;
                    Seq_NBlocks++;
                }
            }
        } else if (strcmp(section, "[RF]") == 0) {
            if (Seq_NRF < MAX_RF) {
                int id, shape_id;
                double delay, freq, phase, amp;
                if (sscanf(line, "%d %lf %lf %lf %lf %d", 
                    &id, &delay, &freq, &phase, &amp, &shape_id) == 6) {
                    SeqRFTable.id[Seq_NRF] = id;
                    SeqRFTable.delay[Seq_NRF] = delay;
                    SeqRFTable.freq[Seq_NRF] = freq;
                    SeqRFTable.phase[Seq_NRF] = phase;
                    SeqRFTable.amp[Seq_NRF] = amp;
                    SeqRFTable.shape_id[Seq_NRF] = shape_id;
                    Seq_NRF++;
                }
            }
        } else if (strcmp(section, "[TRAP]") == 0) {
            if (Seq_NTrap < MAX_TRAP) {
                int id;
                double amp, rise_time, flat_time, fall_time, delay;
                if (sscanf(line, "%d %lf %lf %lf %lf %lf", 
                    &id, &amp, &rise_time, &flat_time, &fall_time, &delay) == 6) {
                    SeqTrapTable.id[Seq_NTrap] = id;
                    SeqTrapTable.amp[Seq_NTrap] = amp;
                    SeqTrapTable.rise_time[Seq_NTrap] = rise_time;
                    SeqTrapTable.flat_time[Seq_NTrap] = flat_time;
                    SeqTrapTable.fall_time[Seq_NTrap] = fall_time;
                    SeqTrapTable.delay[Seq_NTrap] = delay;
                    Seq_NTrap++;
                }
            }
        } else if (strcmp(section, "[ADC]") == 0) {
            if (Seq_NADC < MAX_ADC) {
                int id, num_samples, delay;
                double dwell;
                if (sscanf(line, "%d %d %lf %d", 
                    &id, &num_samples, &dwell, &delay) == 4) {
                    SeqADCTable.id[Seq_NADC] = id;
                    SeqADCTable.num_samples[Seq_NADC] = num_samples;
                    SeqADCTable.dwell[Seq_NADC] = dwell;
                    SeqADCTable.delay[Seq_NADC] = delay;
                    Seq_NADC++;
                }
            }
        } else if (strcmp(section, "[SHAPES]") == 0) {
            if (shape_sample_mode > 0 && curr_shape) {
                // Reading shape samples
                int sample_index = curr_shape->num_samples - shape_sample_mode;
                if (sample_index >= 0 && sample_index < curr_shape->num_samples) {
                    curr_shape->samples[sample_index] = atof(line);
                    num_loaded++;
                    curr_shape->samples_loaded = num_loaded;
                }
                shape_sample_mode--;
                if (shape_sample_mode == 0) {
                    curr_shape = NULL; // Finished reading this shape
                }
            } else {
                // Start of a new shape or shape metadata
                int id, num_samples;
                num_loaded = 0;
                if (sscanf(line, "shape_id %d", &id) == 1) {
                    printf("Loading shape with ID: %d\n", id);
                    Seq_NShapes++;
                    if (Seq_NShapes < MAX_SHAPES) {
                        curr_shape = &SeqShapes[Seq_NShapes - 1];
                        curr_shape->id = id;
                        curr_shape->num_samples = 0; // Initialize to 0 until num_samples is read
                        curr_shape->samples = NULL;
                    }
                } else if (strncmp(line, "shape_label", 11) == 0 && curr_shape) {
                    sscanf(line, "shape_label %s", curr_shape->shape_label);
                } else if (sscanf(line, "num_samples %d", &num_samples) == 1 && curr_shape) {
                    curr_shape->num_samples = num_samples;
                    curr_shape->samples = (double*)malloc(num_samples * sizeof(double));
                    shape_sample_mode = num_samples; // Enter sample reading mode
                }
            }
            // } else {
            //     printf("Warning: Unrecognized SHAPES line: %s\n", line);
            // }
        }
    }

    fclose(fp);
    printf("Sequence file '%s' loaded successfully.\n", filename);

    // Print Summary
    printf("VERSION: %d.%d.%d\n", version.major, version.minor, version.revision);
    printf("FOV: %.3lf %.3lf %.3lf | GradientRasterTime: %.6lf\n",
           defs.FOV[0], defs.FOV[1], defs.FOV[2], defs.GradientRasterTime);
    printf("BLOCKS: %d | RF: %d | TRAP: %d | ADC: %d | SHAPES: %d\n",
           Seq_NBlocks, Seq_NRF, Seq_NTrap, Seq_NADC, Seq_NShapes);


    for (int i = 0; i < Seq_NShapes; i++) {
        if (SeqShapes[i].num_samples > SeqShapes[i].samples_loaded) {
            printf("Shape ID %d: runtime compressed\n", SeqShapes[i].id);
            double shape[SeqShapes[i].num_samples]; // Allocate shape array
            if (decompressShape(SeqShapes[i], shape)) {
                for (int j = 0; j < SeqShapes[i].num_samples; j++) {
                    SeqShapes[i].samples[j] = shape[j];
                }
            }
        } else {
            printf("Shape ID %d: not runtime compressed\n", SeqShapes[i].id);
        }
    }


    // Free shapes
    //free_shapes();
    return 0;
}


/***********************************************************/
// Decompress shape: returns 1 on success, 0 on failure
int decompressShape(SHAPE encoded, double *shape)
{
    if (encoded.num_samples == encoded.samples_loaded) {
        // Not compressed, just copy
        for (int i = 0; i < encoded.num_samples; i++) {
            shape[i] = encoded.samples[i];
        }
        return 1;
    }
    // for (int i = 0; i < encoded.samples_loaded; i++) {
    //     printf("  %lf\n", encoded.samples[i]); // Initialize shape array
    // }
    // Compressed shape: decompress using run-length encoding
    double *packed = encoded.samples;
    int numPacked = encoded.samples_loaded;
    int numSamples = encoded.num_samples;

    int packIdx = 0;
    int unpackIdx = 0;
    while (packIdx < numPacked && unpackIdx < numSamples) {
        if (packIdx + 2 < numPacked && packed[packIdx] == packed[packIdx + 1]) {
            // Run detected
            int rep = (int)packed[packIdx + 2] + 2;
            // printf("   run  detected %d\n", rep);
            if (rep <= 0 || unpackIdx + rep > numSamples) {
                printf("ERROR: compressed shape format error detected\n");
                return 0;
            }
            for (int i = 0; i < rep; i++) {
                shape[unpackIdx++] = packed[packIdx];
            }
            packIdx += 3;
        } else {
            // Single value
            shape[unpackIdx++] = packed[packIdx++];
        }
    }
    if (unpackIdx != numSamples) {
        printf("ERROR: decompressed sample count mismatch (got %d, expected %d)\n", unpackIdx, numSamples);
        return 0;
    }
    // Cumulative sum
    for (int i = 1; i < numSamples; i++) {
        shape[i] = shape[i] + shape[i - 1];  
        // printf("  %d  %lf\n", i, shape[i]);
    }
    printf("Shape ID %d: Decompressed to %d samples\n", encoded.id, numSamples);
    return 1;
}



void WriteShapeToExp(SHAPE shape, const char* filename) 
{

    double s_max = shape.samples[0];
    double s_min = shape.samples[0];
    double s_sum = 0;
    for (int i = 1; i < shape.num_samples; i++) {
        s_max = fmax(s_max, shape.samples[i]);
        s_min = fmin(s_min, shape.samples[i]);
        s_sum += shape.samples[i];
    }
    double integralRatio = s_sum / (100.0 * shape.num_samples);
    

    FILE *fid = fopen(filename, "w");
    if (!fid) {
        perror("Failed to open output file");
        return;
    }
    fprintf(fid,"##TITLE=%s\n",filename);
    fprintf(fid,"##JCAMP-DX= 5 BRUKER JCAMP library\n");
    fprintf(fid,"##DATA TYPE= Shape Data\n");
    fprintf(fid,"##ORIGIN= MATLAB\n");
    fprintf(fid,"##OWNER= <klayton>\n");
    fprintf(fid,"##DATE= 20/10/14\n");
    fprintf(fid,"##TIME= 14:29:34\n");
    fprintf(fid,"##MINX= %.6e\n",s_min);
    fprintf(fid,"##MAXX= %.6e\n",s_max);
    // fprintf(fid,"##MINY= %.6e\n",min(phase));
    // fprintf(fid,"##MAXY= %.6e\n",max(phase));
    fprintf(fid,"##$SHAPE_EXMODE= Excitation\n");
    fprintf(fid,"##$SHAPE_TOTROT= 9.000000e+01\n");
    fprintf(fid,"##$SHAPE_BWFAC= 2.025000e+01\n");
    fprintf(fid,"##$SHAPE_INTEGFAC= %.6e\n",integralRatio);
    fprintf(fid,"##$SHAPE_REPHFAC= 50\n");
    fprintf(fid,"##$SHAPE_TYPE= conventional\n");
    fprintf(fid,"##$SHAPE_MODE= 0\n");
    fprintf(fid,"##NPOINTS= %d\n",shape.num_samples);
    fprintf(fid,"##XYPOINTS= (XY..XY)\n");
    
    for (int i = 1; i < shape.num_samples; i++) {
        // fprintf(fid, "%.6e %.6e\n", shape.samples[i], shape.samples[i]); If we want phase, write two col
        fprintf(fid, "%.6e\n", shape.samples[i]);
    }
    fprintf(fid,"##END=\n");

    fclose(fid);

    printf("Shape written to %s\n", filename);

}


void GradTrapToGradShape(double gradrastertime) {
    // Convert trapezoids to gradient shapes
    for (int i = 0; i < Seq_NTrap; i++) {
        int found = 0;
        int shape_id = -1;

        // Check if this combination already exists
        for (int j = 0; j < i; j++) {
            if (fabs(SeqTrapTable.rise_time[i] - SeqTrapTable.rise_time[j]) < 1e-9 &&
                fabs(SeqTrapTable.flat_time[i] - SeqTrapTable.flat_time[j]) < 1e-9 &&
                fabs(SeqTrapTable.fall_time[i] - SeqTrapTable.fall_time[j]) < 1e-9) {
                found = 1;
                shape_id = SeqTrapTable.id[j];
                printf("Trapezoid %d matches %d\n", SeqTrapTable.id[i], SeqTrapTable.id[j]);
                break;
            }
        }

        if (!found) {
            // Add new shape
            if (Seq_NGrad < MAX_SHAPES) {
                printf("Creating new gradient shape for trapezoid %d\n", SeqTrapTable.id[i]);
                Seq_NGrad++;
                SeqGradients[Seq_NGrad].id = Seq_NGrad;

                int n_rise = (int)round(SeqTrapTable.rise_time[i] / gradrastertime);
                int n_flat = (int)round(SeqTrapTable.flat_time[i] / gradrastertime);
                int n_fall = (int)round(SeqTrapTable.fall_time[i] / gradrastertime);
                int n_total = n_rise + n_flat + n_fall;

                SeqGradients[Seq_NGrad].num_samples = n_total;
                SeqGradients[Seq_NGrad].samples = (double*)malloc(n_total * sizeof(double));

                // Linear ramp up
                for (int k = 0; k < n_rise; k++) {
                    SeqGradients[Seq_NGrad].samples[k] =  (k + 1) / n_rise;
                }
                // Flat top
                for (int k = 0; k < n_flat; k++) {
                    SeqGradients[Seq_NGrad].samples[n_rise + k] = 1;
                }
                // Linear ramp down
                for (int k = 0; k < n_fall; k++) {
                    SeqGradients[Seq_NGrad].samples[n_rise + n_flat + k] =
                         (1.0 - (double)(k + 1) / n_fall);
                }

                // Optionally allocate and fill samples here
                Seq_NGrad++;
            }
        }

        // Store grad_shape_id for this trap
        SeqTrapTable.grad_shape_id[i] = shape_id;
    }
}