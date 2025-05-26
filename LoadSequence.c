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


int block_count = 0;
int rf_count = 0;
int trap_count = 0;
int adc_count = 0;
int shape_count = 0;

// Function to trim newline characters from a string
void trim_newline(char *line) {
    line[strcspn(line, "\r\n")] = 0;
}

// Function to free allocated memory for shapes
void free_shapes() {
    for (int i = 0; i < shape_count; i++) {
        free(SeqShapes[i].samples);
    }
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
        }

        else if (strcmp(section, "[DEFINITIONS]") == 0) {
            sscanf(line, "FOV %lf %lf %lf", &defs.FOV[0], &defs.FOV[1], &defs.FOV[2]);
            sscanf(line, "GradientRasterTime %lf", &defs.GradientRasterTime);
        }

        else if (strcmp(section, "[BLOCKS]") == 0) {
            if (block_count < MAX_BLOCKS) {
                int num, dur, rf, gx, gy, gz, adc, ext;
                if (sscanf(line, "%d %d %d %d %d %d %d %d",
                    &num, &dur, &rf, &gx, &gy, &gz, &adc, &ext) == 8) { 
                    SeqBlockTable.num[block_count] = num;
                    SeqBlockTable.dur[block_count] = dur;
                    SeqBlockTable.rf[block_count] = rf;
                    SeqBlockTable.gx[block_count] = gx;
                    SeqBlockTable.gy[block_count] = gy;
                    SeqBlockTable.gz[block_count] = gz;
                    SeqBlockTable.adc[block_count] = adc;
                    SeqBlockTable.ext[block_count] = ext;
                    block_count++;
                }
            }
        }

        else if (strcmp(section, "[RF]") == 0) {
            if (rf_count < MAX_RF) {
                int id, shape_id;
                double delay, freq, phase, amp;
                if (sscanf(line, "%d %lf %lf %lf %lf %d", 
                    &id, &delay, &freq, &phase, &amp, &shape_id) == 6) {
                    SeqRFTable.id[rf_count] = id;
                    SeqRFTable.delay[rf_count] = delay;
                    SeqRFTable.freq[rf_count] = freq;
                    SeqRFTable.phase[rf_count] = phase;
                    SeqRFTable.amp[rf_count] = amp;
                    SeqRFTable.shape_id[rf_count] = shape_id;
                    rf_count++;
                }
            }
        }

        else if (strcmp(section, "[TRAP]") == 0) {
            if (trap_count < MAX_TRAP) {
                int id;
                double amp, rise_time, flat_time, fall_time, delay;
                if (sscanf(line, "%d %lf %lf %lf %lf %lf", 
                    &id, &amp, &rise_time, &flat_time, &fall_time, &delay) == 6) {
                    SeqTrapTable.id[trap_count] = id;
                    SeqTrapTable.amp[trap_count] = amp;
                    SeqTrapTable.rise_time[trap_count] = rise_time;
                    SeqTrapTable.flat_time[trap_count] = flat_time;
                    SeqTrapTable.fall_time[trap_count] = fall_time;
                    SeqTrapTable.delay[trap_count] = delay;
                    trap_count++;
                }
            }
        }

        else if (strcmp(section, "[ADC]") == 0) {
            if (adc_count < MAX_ADC) {
                int id, num_samples, delay;
                double dwell;
                if (sscanf(line, "%d %d %lf %d", 
                    &id, &num_samples, &dwell, &delay) == 4) {
                    SeqADCTable.id[adc_count] = id;
                    SeqADCTable.num_samples[adc_count] = num_samples;
                    SeqADCTable.dwell[adc_count] = dwell;
                    SeqADCTable.delay[adc_count] = delay;
                    adc_count++;
                }
            }
        }
        else if (strcmp(section, "[SHAPES]") == 0) {
            if (shape_sample_mode == 0) {
            // Start of a new shape
            int id, num_samples;
            num_loaded = 0;
            if (sscanf(line, "shape_id %d", &id) == 1) {
                shape_count++;
                if (shape_count < MAX_SHAPES) {
                curr_shape = &SeqShapes[shape_count - 1];
                curr_shape->id = id;
                curr_shape->num_samples = 0; // Initialize to 0 until num_samples is read
                curr_shape->samples = NULL;
                }
            } else if (sscanf(line, "num_samples %d", &num_samples) == 1 && curr_shape) {
                curr_shape->num_samples = num_samples;
                curr_shape->samples = (double*)malloc(num_samples * sizeof(double));
                shape_sample_mode = num_samples; // Enter sample reading mode
            }
            } else if (shape_sample_mode > 0 && curr_shape) {
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
            }
        }
    }

    fclose(fp);
    printf("Sequence file '%s' loaded successfully.\n", filename);

    // Print Summary
    printf("VERSION: %d.%d.%d\n", version.major, version.minor, version.revision);
    printf("FOV: %.3lf %.3lf %.3lf | GradientRasterTime: %.6lf\n",
           defs.FOV[0], defs.FOV[1], defs.FOV[2], defs.GradientRasterTime);
    printf("BLOCKS: %d | RF: %d | TRAP: %d | ADC: %d | SHAPES: %d\n",
           block_count, rf_count, trap_count, adc_count, shape_count);


    for (int i = 0; i < shape_count; i++) {
        if (SeqShapes[i].num_samples > SeqShapes[i].samples_loaded) {
            printf("Shape ID %d: runtime compressed\n", SeqShapes[i].id);
            double shape[SeqShapes[i].num_samples]; // Allocate shape array
            if (decompressShape(SeqShapes[i], shape)) {
                SeqShapes[i].samples = shape;
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
// COPILOT GENERATED CODE
int decompressShape(SHAPE encoded, double *shape)
{
    if (encoded.num_samples == encoded.samples_loaded) {
        // Not compressed, just copy
        for (int i = 0; i < encoded.num_samples; i++) {
            shape[i] = (float)encoded.samples[i];
        }
        return 1;
    }
    // Compressed shape: decompress using run-length encoding
    double *packed = encoded.samples;
    int numPacked = encoded.samples_loaded;
    int numSamples = encoded.num_samples;

    int countPack = 1;
    int countUnpack = 1;
    while (countPack < numPacked) {
        if (packed[countPack - 1] != packed[countPack]) {
            shape[countUnpack - 1] = (float)packed[countPack - 1];
            countPack++; countUnpack++;
        } else {
            int rep = ((int)packed[countPack + 1]) + 2;
            if (fabs(packed[countPack + 1] + 2 - rep) > 1e-6) {
                printf("ERROR: compressed shape format error detected\n");
                return 0;
            }
            for (int i = countUnpack - 1; i <= countUnpack + rep - 2; i++)
                shape[i] = (float)packed[countPack - 1];
            countPack += 3;
            countUnpack += rep;
        }
    }
    if (countPack == numPacked) {
        shape[countUnpack - 1] = (float)packed[countPack - 1];
    }
    // Cumulative sum
    for (int i = 1; i < numSamples; i++) {
        shape[i] = shape[i] + shape[i - 1];
    }
    printf("Shape ID %d: Decompressed to %d samples\n", encoded.id, numSamples);
    return 1;
}
