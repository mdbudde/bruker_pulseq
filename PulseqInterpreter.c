//GPT-assisted pure c for loading pulseq files. 
//Designed to be easier to integrate into method loading than c++. 
//need to include many additional functions/features from ExternalSequences.cpp



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>
#include "PulseqInterpreter.h"


//---- GLOBAL STORAGE; these will move to paravision variables in the sequence method
Version version;
Definitions defs;
BLOCKTABLE SeqBlockTable; 
RFTABLE SeqRFTable; 
TRAPTABLE SeqTrapTable; 
ADCTABLE SeqADCTable; 
SHAPE SeqShapes[MAX_SHAPES]; 
GRADSHAPE SeqGradients[MAX_SHAPES]; 

double SeqRFFrequencyList[] = {0.0}; // List of RF frequencies, will be filled in by RF table
double SeqRFPowerList[] = {0.0}; // List of RF powers, will be filled in by RF table
double SeqRFPhaseList[] = {0.0}; // List of RF phases, will be filled in by RF table

char SeqFilename[256] = ""; // Name of the sequence file to load
char SeqIdentString[256] = ""; // Name stored in seq file

double gyromagnetic_ratio = 42.576e3; // MHz/T for 1H, will get from PV for this nucleus
double GradMax = 494.0; // Maximum gradient amplitude in mT/m, will get from PV
int InterGradientWaitTime = 20; // in microseconds, will get from PV

int Seq_NBlocks = 0;
int Seq_NRF = 0;
int Seq_NTrap = 0;
int Seq_NADC = 0;
int Seq_NShapes = 0;
int Seq_NGrad = 0;

//---- END of variables that will be moved to paravision variables in the sequence method



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
    printf("-->Starting UpdateSeq.\n");

    printf("\n\nWriting shape files...\n");
    for (int i = 0; i < Seq_NShapes; i++) {
        char filename[64];
        snprintf(filename, sizeof(filename), "pulseq_shape_%d.exc", SeqShapes[i].id);
        WriteShapeToExp(SeqShapes[i], filename);
    }
    printf("Done.\n");

    // Convert trapezoids to gradient shapes
    double gradrastertime = 8e-3; // in seconds; for testing make small. 
    GradTrapToGradShape(gradrastertime);

    //GradShapeToPPGShape();

    WritePPG("pulseq.ppg");

    printf("<--End UpdateSeq\n\n");
}

// Function to load a sequence file
int LoadSequenceFile(const char* filename) {

    printf("-->Starting LoadSequenceFile.\n");

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        SeqFilename[0] = '\0'; // Clear filename on error
        return 1;
    }
    strcpy(SeqFilename, filename);

    printf("Loading seq file %s\n",filename);
    char line[MAX_LINE], section[MAX_LINE] = "";
    int shape_sample_mode = 0; // if > 0, we're in SHAPES data
    int num_loaded = 0; // Count of loaded samples
    SHAPE *curr_shape = NULL;
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (line[0] == '#' || strlen(line) == 0)
            continue;

        if (line[0] == '[') {
            printf("  Loading Section %s\n",line);
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
            sscanf(line, "Name %s", SeqIdentString);
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
                int id, rise_time, flat_time, fall_time, delay;
                double amp;
                if (sscanf(line, "%d %lf %d %d %d %d", 
                    &id, &amp, &rise_time, &flat_time, &fall_time, &delay) == 6) {
                    SeqTrapTable.id[Seq_NTrap] = id;
                    SeqTrapTable.amp[Seq_NTrap] = amp;
                    SeqTrapTable.rise_time[Seq_NTrap] = rise_time;
                    SeqTrapTable.flat_time[Seq_NTrap] = flat_time;
                    SeqTrapTable.fall_time[Seq_NTrap] = fall_time;
                    SeqTrapTable.delay[Seq_NTrap] = delay;
                    SeqTrapTable.amp_percent[Seq_NTrap] = (amp / gyromagnetic_ratio / GradMax) * 100.0; // convert Hz/m to mT/m and percent of gradient max
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
                    printf("  Loading shape with ID: %d\n", id);
                    Seq_NShapes++;
                    if (Seq_NShapes < MAX_SHAPES) {
                        curr_shape = &SeqShapes[Seq_NShapes - 1];
                        curr_shape->id = id;
                        curr_shape->num_samples = 0; // Initialize to 0 until num_samples is read
                        curr_shape->samples = NULL;
                    }
                } else if (strncmp(line, "shape_label", 11) == 0 && curr_shape) {
                    sscanf(line, "shape_label %s", curr_shape->shape_label);
                } else if (strncmp(line, "shape_type", 10) == 0 && curr_shape) {
                    sscanf(line, "shape_type %s", curr_shape->shape_type);
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
    printf("Sequence file '%s' loaded successfully.\n\n", filename);

    // Print Summary
    printf("VERSION: %d.%d.%d\n", version.major, version.minor, version.revision);
    printf("FOV: %.3lf %.3lf %.3lf | GradientRasterTime: %.6lf\n",
           defs.FOV[0], defs.FOV[1], defs.FOV[2], defs.GradientRasterTime);
    printf("BLOCKS: %d | RF: %d | TRAP: %d | ADC: %d | SHAPES: %d\n",
           Seq_NBlocks, Seq_NRF, Seq_NTrap, Seq_NADC, Seq_NShapes);

    printf("\nChecking shape compression...\n");
    for (int i = 0; i < Seq_NShapes; i++) {
        if (SeqShapes[i].num_samples > SeqShapes[i].samples_loaded) {
            printf("  Shape ID %d: runtime compressed\n", SeqShapes[i].id);
            double shape[SeqShapes[i].num_samples]; // Allocate shape array
            if (decompressShape(SeqShapes[i], shape)) {
                for (int j = 0; j < SeqShapes[i].num_samples; j++) {
                    SeqShapes[i].samples[j] = shape[j];
                }
            }
        } else {
            printf("  Shape ID %d: not runtime compressed\n", SeqShapes[i].id);
        }
    }
    printf("Done.\n");

    printf("<--End LoadSequenceFile.\n");

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
    printf("  Shape ID %d: Decompressed to %d samples\n", encoded.id, numSamples);
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
    
    printf("  Writing shape file...\n");

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

    printf("  Shape written to %s\n", filename);

}


void GradTrapToGradShape(double gradrastertime) {

    printf("\n\nConverting trapezoids to gradient shapes...\n");
    // Convert trapezoids to gradient shapes
    for (int i = 0; i < Seq_NTrap; i++) {
        int found = 0;
        int shape_id = -1;

        // Check if this combination already exists
        for (int j = 0; j < i; j++) {
            if ((SeqTrapTable.rise_time[i] == SeqTrapTable.rise_time[j]) &&
                (SeqTrapTable.flat_time[i] == SeqTrapTable.flat_time[j]) &&
                (SeqTrapTable.fall_time[i] == SeqTrapTable.fall_time[j]))  {
                found = 1;
                shape_id = SeqTrapTable.grad_shape_id[j]; // Use existing shape ID
                printf("  Trapezoid %d matches %d, with shapeindex %d\n", SeqTrapTable.id[i], SeqTrapTable.id[j], shape_id);
                break;
            }
        }

        if (!found) {
            // Add new shape
            if (Seq_NGrad < MAX_SHAPES) {
                shape_id = Seq_NGrad; // Use the new gradient shape ID
                printf("  Creating new gradient shape for trapezoid %d, with shapeindex %d\n", SeqTrapTable.id[i], shape_id);
                SeqGradients[Seq_NGrad].id = Seq_NGrad;

                int n_rise = (int)round(SeqTrapTable.rise_time[i] / gradrastertime);
                int n_flat = (int)round(SeqTrapTable.flat_time[i] / gradrastertime);
                int n_fall = (int)round(SeqTrapTable.fall_time[i] / gradrastertime);
                int n_total = n_rise + n_flat + n_fall;

                SeqGradients[Seq_NGrad].num_samples = n_total;
                SeqGradients[Seq_NGrad].samples = (double*)malloc(n_total * sizeof(double));


                //TODO: Will convery these to paravision GRADSHAPE type function calls for consistency with other code

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

            }

            Seq_NGrad++;
        }

        // Store grad_shape_id for this trap
        SeqTrapTable.grad_shape_id[i] = shape_id;
    }

    printf("Done.\n");
}

/*
* Only available in paravision; PVM_ppgGradShape1 and PVM_ppgGradShape1Size .... are declared variables.
void GradShapeToPPGShape(void);
{
    if (Seq_NGrad > 0) {
        PVM_ppgGradShape1Size = SeqGradients[0].num_samples;
        //PARX_change_dims("PVM_ppgGradShape1",PVM_ppgGradShape1Size);
        LoadPPGShape(&PVM_ppgGradShape1, 0, PVM_ppgGradShape1Size);
    }
    if (Seq_NGrad > 1) {
        PVM_ppgGradShape2Size = SeqGradients[1].num_samples;
        //PARX_change_dims("PVM_ppgGradShape2",PVM_ppgGradShape1Size);
        LoadPPGShape(&PVM_ppgGradShape2, 1, PVM_ppgGradShape2Size);
    }
    if (Seq_NGrad > 2) {
        PVM_ppgGradShape3Size = SeqGradients[2].num_samples;
        //PARX_change_dims("PVM_ppgGradShape3",PVM_ppgGradShape1Size);
        LoadPPGShape(&PVM_ppgGradShape3, 2, PVM_ppgGradShape3Size);
    }
    if (Seq_NGrad > 3) {
        PVM_ppgGradShape4Size = SeqGradients[3].num_samples;
        //PARX_change_dims("PVM_ppgGradShape4",PVM_ppgGradShape1Size);
        LoadPPGShape(&PVM_ppgGradShape4, 3, PVM_ppgGradShape4Size);
    }
    if (Seq_NGrad > 4) {
        PVM_ppgGradShape5Size = SeqGradients[4].num_samples;
        //PARX_change_dims("PVM_ppgGradShape5",PVM_ppgGradShape1Size);
        LoadPPGShape(&PVM_ppgGradShape5, 4, PVM_ppgGradShape5Size);
    }
    if (Seq_NGrad > 5) {
        PVM_ppgGradShape6Size = SeqGradients[5].num_samples;
        //PARX_change_dims("PVM_ppgGradShape6",PVM_ppgGradShape1Size);
        LoadPPGShape(&PVM_ppgGradShape6, 5, PVM_ppgGradShape6Size);
    }
}

void LoadPPGShape(double *ppgGradShape, int shapeind, int shapesize)
{
        for (int i=0; i<shapesize; i++) {
            ppgGradShape[i] = SeqGradients[shapeind].samples[i];
        }
}
*/


void WritePPG(const char* ppgfile) 
{
    FILE *fid = fopen(ppgfile, "w");
    if (!fid) {
        perror("Failed to open PPG file for writing");
        return;
    }

    printf("\n\nWriting PPG file...\n");
    printf("  %s\n",ppgfile);

    fprintf(fid, "; PPG file\n");
    fprintf(fid, ";\n");
    fprintf(fid, "; Created from seq file: %s \n", SeqFilename);
    fprintf(fid, "; Seq file Name tag: %s \n", SeqIdentString);

    // Get current date and time
   
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    // Write formatted date and time to the file
    fprintf(fid, "; Date: %04d-%02d-%02d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    fprintf(fid, "; Time: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);

    fprintf(fid, ";\n\n");


    //didn't need to declare shapes in ppg, these are already accessible as the variables
    // for (int i =0; i<Seq_NGrad; i++) {
    //     fprintf(fid, "#declare list<gradient> ppgGrad%d = {$PVM_ppgGradShape%d}  ;grad id %d\n",i, i, SeqGradients[i].id);
    // }

    fprintf(fid,"\n\n");

    fprintf(fid, ";-------include files-------\n");
    fprintf(fid, "#include <MRI.include>\n\n");


    fprintf(fid, "\n;-------rf lists-------\n");
    fprintf(fid, "define list<frequency> freqList = {$SeqRFFrequencyList}\n");
    fprintf(fid, "define list<phase> phaseList = {$SeqRFPhaseList}\n");
    fprintf(fid, "define list<power> powList = {Watt $SeqRFPowerList}\n");
    fprintf(fid, "\n");


    fprintf(fid, ";-----gradient shapes-----\n");
    fprintf(fid, "; for reference, unnecessary to explicitly redefine here in ppg\n");
    fprintf(fid, "; rise  flat  fall \n");
    for (int i = 0; i < Seq_NTrap; i++) {
        int found = 0;
        // Check if this combination already reported
        for (int j = 0; j < i; j++) {
            if (SeqTrapTable.grad_shape_id[j] == SeqTrapTable.grad_shape_id[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int shapeind = SeqTrapTable.grad_shape_id[i];
            fprintf(fid,"  ; PVM_ppgGradShape%d is %du %du %du\n", shapeind, SeqTrapTable.rise_time[shapeind], SeqTrapTable.flat_time[shapeind], SeqTrapTable.fall_time[shapeind]);
        }
    }



    fprintf(fid, "\n;-------definitions-------\n");
    fprintf(fid, "preset off\n\n");
    fprintf(fid, "INIT_DEVICES\n\n");

    fprintf(fid, ";-------sequence-------\n");
    fprintf(fid, "start,\n");

    int fpcnt = 0;
    int CommentColumn = 120; // Column to start comments
    for (int b = 0; b < Seq_NBlocks; b++) {

        if (SeqBlockTable.rf[b] > 0) {

            fpcnt = fprintf(fid, "    10u gc_control ");
            fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
            fprintf(fid, "; block %d w RF\n", SeqBlockTable.num[b]);
            fprintf(fid, "    {\n");

            fprintf(fid, "        %du ", SeqBlockTable.dur[b]);
            if (SeqBlockTable.gx[b] > 0 || SeqBlockTable.gy[b] > 0 || SeqBlockTable.gz[b] > 0) {
                int gxind, gyind, gzind;
                fpcnt += fprintf(fid, "grad_shape{");
                if (SeqBlockTable.gx[b] > 0) {
                    gxind = SeqBlockTable.gx[b] - 1;
                    fprintf(fid, "PVM_ppgGradShape%d * %.3lf, ", SeqTrapTable.grad_shape_id[gxind], SeqTrapTable.amp_percent[gxind]);
                } else {
                    fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gy[b] > 0) {
                    gyind = SeqBlockTable.gy[b] - 1;
                    fprintf(fid, "PVM_ppgGradShape%d * %.3lf, ", SeqTrapTable.grad_shape_id[gyind], SeqTrapTable.amp_percent[gyind]);
                } else {
                    fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gz[b] > 0) {
                    gzind = SeqBlockTable.gz[b] - 1;
                    fprintf(fid, "PVM_ppgGradShape%d * %.3lf", SeqTrapTable.grad_shape_id[gzind], SeqTrapTable.amp_percent[gzind]);
                } else {
                    fprintf(fid, "0");
                }
                fprintf(fid, "}\n");
                fprintf(fid, "    } ");


                //int freqsettime = 60;  //need to figure this out.
                fprintf(fid, "  freqList:f1  powList:f1  gatepulse 1  ; possible in gc_control command?\n");
                //fprintf(fid, "    ;%du ", SeqBlockTable.dur[b]);
                fpcnt = fprintf(fid, "        (p0:sp0(currentpower) phaseList):f1 ");
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, "; continuation\n");
                
                fpcnt = fprintf(fid, "        %du freqList.inc powList.inc phaseList.inc ",InterGradientWaitTime);
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, "; implied block, igwt\n");

                fprintf(fid, "\n");

            } 
            

        } else if (SeqBlockTable.adc[b] > 0) {

            // fpcnt = fprintf(fid, "    10u gc_control ");
            // fprintf(fid, "    {\n");




            fpcnt = fprintf(fid, "    %du ADC_START ", SeqBlockTable.dur[b]);
            if (SeqBlockTable.gx[b] > 0 || SeqBlockTable.gy[b] > 0 || SeqBlockTable.gz[b] > 0) {
                int gxind, gyind, gzind;
                fpcnt += fprintf(fid, "grad_shape{");
                if (SeqBlockTable.gx[b] > 0) {
                    gxind = SeqBlockTable.gx[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d * %.3lf, ", SeqTrapTable.grad_shape_id[gxind], SeqTrapTable.amp_percent[gxind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gy[b] > 0) {
                    gyind = SeqBlockTable.gy[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d * %.3lf, ", SeqTrapTable.grad_shape_id[gyind], SeqTrapTable.amp_percent[gyind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gz[b] > 0) {
                    gzind = SeqBlockTable.gz[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d * %.3lf", SeqTrapTable.grad_shape_id[gzind], SeqTrapTable.amp_percent[gzind]);
                } else {
                    fpcnt += fprintf(fid, "0");
                }
                fpcnt += fprintf(fid, "} ");
                // fprintf(fid, "    }; end gc_control\n");

                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, "; block %d w ADC\n", SeqBlockTable.num[b]);

                // fprintf(fid, "    %du ", SeqBlockTable.dur[b]);

                fpcnt = fprintf(fid, "        %du ADC_END ", InterGradientWaitTime);
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, "; implied block, igwt\n");
                fprintf(fid, " \n");

            }

        } else {
        // No RF or ADC, just a gradient or delay block

            fpcnt = fprintf(fid, "    %du ", SeqBlockTable.dur[b]);

            if (SeqBlockTable.gx[b] > 0 || SeqBlockTable.gy[b] > 0 || SeqBlockTable.gz[b] > 0) {

                int gxind, gyind, gzind;
                fpcnt += fprintf(fid, "grad_shape{");

                if (SeqBlockTable.gx[b] > 0) {
                    gxind = SeqBlockTable.gx[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d * %.3lf, ", SeqTrapTable.grad_shape_id[gxind], SeqTrapTable.amp_percent[gxind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gy[b] > 0) {
                    gyind = SeqBlockTable.gy[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d * %.3lf, ", SeqTrapTable.grad_shape_id[gyind], SeqTrapTable.amp_percent[gyind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gz[b] > 0) {
                    gzind = SeqBlockTable.gz[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d * %.3lf", SeqTrapTable.grad_shape_id[gzind], SeqTrapTable.amp_percent[gzind]);
                } else {
                    fpcnt += fprintf(fid, "0");
                }
                fpcnt += fprintf(fid, "} ");

            } 
            
            fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
            fprintf(fid, "; block %d\n", SeqBlockTable.num[b]);

        }

        // write the ADC initialization if the next block has ADC
        if ((b > 0) && (SeqBlockTable.adc[b + 1] > 0)) {
            fpcnt = fprintf(fid, "    ADC_INIT_B(NOPH, phaseRList) ");
            fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
            fprintf(fid, "; implied block, igwt\n");
        }

        
    }


    fprintf(fid, "\n\nbye,    1u\n");
    fprintf(fid, "exit,\n");


    printf("Done. %s...\n\n", ppgfile);

}