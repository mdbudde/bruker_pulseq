#GPT-based pure c for loading pulseq files. 
# Designed to be easier to integrate into method loading. 
# need to include many additional functions/features from ExternalSequences.cpp



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_BLOCKS 2048
#define MAX_RF 256
#define MAX_TRAP 256
#define MAX_ADC 256
#define MAX_SHAPES 512

// SECTION STRUCTS

typedef struct {
    int major, minor, revision;
} Version;

typedef struct {
    double FOV[3];
    double GradientRasterTime;
} Definitions;

typedef struct {
    int num, dur, rf, gx, gy, gz, adc, ext;
} Block;

typedef struct {
    int id;
    double delay, freq, phase, amp;
    int shape_id;
} RFEvent;

typedef struct {
    int id;
    double amp, rise_time, flat_time, fall_time, delay;
} Trap;

typedef struct {
    int id;
    int num_samples;
    double dwell;
    int delay;
} ADC;

typedef struct {
    int id;
    int num_samples;
    double *data;
} Shape;

// GLOBAL STORAGE
Version version;
Definitions defs;
Block blocks[MAX_BLOCKS]; int block_count = 0;
RFEvent rf_events[MAX_RF]; int rf_count = 0;
Trap traps[MAX_TRAP]; int trap_count = 0;
ADC adc_events[MAX_ADC]; int adc_count = 0;
Shape shapes[MAX_SHAPES]; int shape_count = 0;

// UTIL
void trim_newline(char *line) {
    line[strcspn(line, "\r\n")] = 0;
}

void free_shapes() {
    for (int i = 0; i < shape_count; i++) {
        free(shapes[i].data);
    }
}

// MAIN PARSER
int main() {
    FILE *fp = fopen("gre.seq", "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    char line[MAX_LINE], section[MAX_LINE] = "";
    int shape_sample_mode = 0; // if > 0, we're in SHAPES data
    Shape *curr_shape = NULL;
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
                Block *b = &blocks[block_count];
                if (sscanf(line, "%d %d %d %d %d %d %d %d",
                    &b->num, &b->dur, &b->rf, &b->gx, &b->gy, &b->gz, &b->adc, &b->ext) == 8)
                    block_count++;
            }
        }

        else if (strcmp(section, "[RF]") == 0) {
            if (rf_count < MAX_RF) {
                RFEvent *rf = &rf_events[rf_count];
                if (sscanf(line, "%d %lf %lf %lf %lf %d", &rf->id, &rf->delay, &rf->freq,
                           &rf->phase, &rf->amp, &rf->shape_id) == 6)
                    rf_count++;
            }
        }

        else if (strcmp(section, "[TRAP]") == 0) {
            if (trap_count < MAX_TRAP) {
                Trap *t = &traps[trap_count];
                if (sscanf(line, "%d %lf %lf %lf %lf %lf", &t->id, &t->amp, &t->rise_time,
                           &t->flat_time, &t->fall_time, &t->delay) == 6)
                    trap_count++;
            }
        }

        else if (strcmp(section, "[ADC]") == 0) {
            if (adc_count < MAX_ADC) {
                ADC *a = &adc_events[adc_count];
                if (sscanf(line, "%d %d %lf %d", &a->id, &a->num_samples, &a->dwell, &a->delay) == 4)
                    adc_count++;
            }
        }

        else if (strcmp(section, "[SHAPES]") == 0) {
            // Start of a new shape
            int id, num_samples;
            if (sscanf(line, "%d %d", &id, &num_samples) == 2) {
                if (shape_count < MAX_SHAPES) {
                    curr_shape = &shapes[shape_count++];
                    curr_shape->id = id;
                    curr_shape->num_samples = num_samples;
                    curr_shape->data = (double*)malloc(num_samples * sizeof(double));
                    shape_sample_mode = 1;
                    continue;
                }
            }
            if (shape_sample_mode && curr_shape) {
                curr_shape->data[curr_shape->num_samples - shape_sample_mode] = atof(line);
                shape_sample_mode--;
                curr_shape = (shape_sample_mode > 0) ? curr_shape : NULL;
            }
        }
    }

    fclose(fp);

    // Print Summary
    printf("VERSION: %d.%d.%d\n", version.major, version.minor, version.revision);
    printf("FOV: %.3f %.3f %.3f | GradientRasterTime: %.6f\n",
           defs.FOV[0], defs.FOV[1], defs.FOV[2], defs.GradientRasterTime);
    printf("BLOCKS: %d | RF: %d | TRAP: %d | ADC: %d | SHAPES: %d\n",
           block_count, rf_count, trap_count, adc_count, shape_count);

    // Free shapes
    free_shapes();
    return 0;
}
