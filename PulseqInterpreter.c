//GPT-assisted pure c for loading pulseq files. 
//Designed to be easier to integrate into method loading than c++. 
//need to include many additional functions/features from ExternalSequences.cpp



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <time.h>
#include "PulseqInterpreter.h"

#define ParavisionPulseqVersion "1.0.0" // Version of this interpreter

//---- GLOBAL STORAGE; these will move to paravision variables in the sequence method
Version version;
Definitions SeqDefinitions;
BLOCKTABLE SeqBlockTable; 
RFTABLE SeqRFTable; 
TRAPTABLE SeqTrapTable; 
ADCTABLE SeqADCTable; 
SHAPE SeqShapes[MAX_SHAPES]; 
GRADSHAPE SeqGradients[MAX_SHAPES]; 

double *SeqRFFrequencyList; // List of RF frequencies
double *SeqRFPowerList; // List of RF powers
double *SeqRFPhaseList; // List of RF phases

double *SeqADCFrequencyList; // List of ADC freq
double *SeqADCPhaseList; // List of ADC phases

char SeqFilename[256] = ""; // Name of the sequence file to load
char SeqIdentString[256] = ""; // Name stored in seq file

double aqq;

double gyromagnetic_ratio = 42.576e3; // MHz/T for 1H, will get from PV for this nucleus
double GradMax = 494.0; // Maximum gradient amplitude in mT/m, will get from PV
int InterGradientWaitTime = 8; // in microseconds, will get from PV
// PVM_GradCalConst defines the frequency deviation of the proton resonance frequency per mm, when the maximum gradient is applied. 42.577Hz/mm = 1mT/m.

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


    SeqDefinitions.Totaltime = 0;
    for (int i=0; i < Seq_NBlocks; i++) {
        SeqDefinitions.Totaltime += SeqBlockTable.dur[i];
    }
    
    SetPVparams();

    UpdateRF();
    UpdateADC();
    UpdateGrad();

    //GradShapeToPPGShape();

    WritePPG("pulseq.ppg");

    printf("<--End UpdateSeq\n\n");
}



void SetPVparams(void){
    /* 

        PVM_Fov[0] = SeqDefinitions.FOV[0]*100;
        PVM_Fov[1] = SeqDefinitions.FOV[1]*100;
        if (PVM_SpatDim > 2) {
            PVM_Fov[2] = SeqDefinitions.FOV[1]*1000 * PVM_Matrix[2];
            PVM_SliceThick = PVM_Fov[2];
        } else {
            PVM_SliceThick = SeqDefinitions.FOV[1]*1000;
        }

        PVM_ScanTime = SeqDefinitions.Totaltime/1000;
        UT_ScanTimeStr(PVM_ScanTimeStr,PVM_ScanTime);

        ACQ_O1B_list[0] = ADC freq. 

        //Just assume it is all a 2D scan (since there's no reco)
        PARX_change_dims("ACQ_size",2);
        ACQ_dim = 2;
        ACQ_size[0] = SeqADCTable.num[0]; // Will not accept different num for each ADC, so just use the first
        ACQ_size[1] = 1; // 1 slice, no slice selection in this seq file
        ACQ_phase_factor = 1;
        NI = 1; // we could include the number of slices?
        NA = 1;
        NR = 1;
        NAE = 1;
        ACQ_ns_list_size = 1;
        de is ADC_INIT implicit delay from pulse to ADC, quoted approx 6us.  
        aqq assign to ADC_START 
        8 us is the min ADC_END time. 

        convert ADC dwell time in ADC table to PV parameters: SW_h 1/dwell
        


        min start and end of acquisition:
        define delay deosc = { $DEOSC }
        “deosc = 1.0E-6*abs(deosc)”
        
        min time END to START of next ADC: about 700 us 


        //Likely we just use the pv interface to show the rf pulse and it's features?
        //or do it all behind the scenes?
        ACQ_RfShapes[] for the RF shapes, we can use the SeqRFTable to fill this
        ACQ_RfShapes[].name = filename for the RF shapes, we can use the SeqRFTable to fill this
        // at a minimum, warn if power/flip angles are not being met with the current setup. 

        STB_InitRFPulse(...)
    */

    // Will not accept different num for each ADC, so just use the first
    aqq = SeqADCTable.dwell[0] * SeqADCTable.num[0] * 1e-3; // acquisition time in ms, converted from ns
}


void UpdateRF(void) {


    printf("\n\nUpdating RF pulses...\n");
    int currmag, currphase;
    for (int i = 0; i < Seq_NRF; i++) {
        currmag = SeqRFTable.mag_id[i];
        currphase = SeqRFTable.phase_id[i];

        // Check if the shape was already written
        static int writtenShapes[MAX_SHAPES] = {0}; // Array to track written shapes
        if ((currmag > 0) && (currphase > 0)) {
            if (SeqShapes[currmag - 1].num_samples == SeqShapes[currphase - 1].num_samples) {

                if (writtenShapes[currmag - 1] == 0) {
                    printf("  Assuming mag shape %d and phase shape %d are always used together\n",currmag, currphase);
                    
                    char filename[64];
                    snprintf(filename, sizeof(filename), "pulseq_shape%d.exc", SeqShapes[i].id);
                    WriteRFShapeToExp(SeqShapes[currmag - 1], filename, SeqShapes[currphase - 1].samples);
                    writtenShapes[currmag - 1] = 1; // Mark the magnitude shape as written
                    //STB_InitRFPulse("PulseSeqPulse1", name = pulseq_shape_1.exc);
                }
            }
        }
    }


    int RFListSize = 0;
    for (int i = 0; i < Seq_NBlocks; i++) {
        if (SeqBlockTable.rf[i] > 0) {
            RFListSize += 1;
        }
    }

    //PARX_change_dims("SeqRFFrequencyList",RFListSize);
    //PARX_change_dims("SeqRFPowerList",RFListSize);
    //PARX_change_dims("SeqRFPhaseList",RFListSize);
    
    SeqRFFrequencyList = (double*)malloc(RFListSize * sizeof(double));
    SeqRFPowerList = (double*)malloc(RFListSize * sizeof(double));
    SeqRFPhaseList = (double*)malloc(RFListSize * sizeof(double));

    /* 
    YesNo refAttIsAvailable=No;
    double referenceAttenuation=0;
    if(PVM_DeriveGains == Yes)
        refAttIsAvailable = STB_GetRefAtt(1,PVM_Nucleus1,&referenceAttenuation);
    else
        refAttIsAvailable = No;
    */

    // int flipangle=0;
    // int maxFlipangle = 180;
    double pow;
    for (int i=0; i< Seq_NBlocks; i++) {
        if (SeqBlockTable.rf[i] > 0) {
            SeqRFFrequencyList[i] = SeqRFTable.freq[SeqBlockTable.rf[i] - 1];
            SeqRFPhaseList[i] = SeqRFTable.phase[SeqBlockTable.rf[i] - 1] / M_PI * 180.0; // Convert to degrees
            pow = SeqRFTable.amplitude[SeqBlockTable.rf[i] - 1];
            //fa=360 * fB1 * t
            // flipangle = 360.0 * pow * time?
        
            /* PulseSeqPulse1.Flipangle = MIN_OF(flipangle, maxFlipangle);
            STB_UpdateRFPulse("PulseSeqPulse1",1,PVM_DeriveGains,Conventional);
            STB_UpdateRFShapeAmplitude("PulseSeqPulse1",Yes);
            SeqRFPowerList[i] = PulseSeqPulse1.Pow; 
            */
            SeqRFPowerList[i] = pow; 
        }
    }
    printf("Done.\n");

}




void UpdateADC(void) {


    printf("\n\nUpdating ADC parameters.\n");
    int ADCListSize = 0;
    for (int i = 0; i < Seq_NBlocks; i++) {
        if (SeqBlockTable.adc[i] > 0) {
            ADCListSize += 1;
        }
    }
    //PARX_change_dims("SeqADCFrequencyList",ADCListSize);
    //PARX_change_dims("SeqADCPhaseList",ADCListSize);
    
    SeqADCFrequencyList = (double*)malloc(ADCListSize * sizeof(double));
    SeqADCPhaseList = (double*)malloc(ADCListSize * sizeof(double));


    for (int i=0; i< Seq_NBlocks; i++) {
        if (SeqBlockTable.adc[i] > 0) {
            SeqADCFrequencyList[i] = SeqADCTable.freq[SeqBlockTable.adc[i] - 1];
            SeqADCPhaseList[i] = SeqADCTable.phase[SeqBlockTable.adc[i] - 1] / M_PI; // use convention where 0 1 2 is 0, 90 180 etc
        }
    }

    printf("Done.\n");
}

void UpdateGrad(void) {


    printf("\n\nUpdating Gradients, including Trap->Shapes.\n");
    // Convert trapezoids to gradient shapes
    double gradrastertime = 8e-3; // in seconds; for testing make small. 


    int found = 0;
    int shape_id = -1;
    Seq_NGrad = 0;
    for(int i=0; i<Seq_NBlocks ; i++ ) {
        for (int g=0; g<3; g++ ) {
        
            int trap_id = 0;
            if (g==0) {
                trap_id = SeqBlockTable.gx[i];
            } else if (g==1) {
                trap_id = SeqBlockTable.gy[i];
            } else if (g==2) {
                trap_id = SeqBlockTable.gz[i]; 
            }

            if (trap_id <= 0) {
                continue; // No gradient for this block
            }
            found = 0; // Reset found for each block
            int currdur = SeqBlockTable.dur[i];
            int currrise = SeqTrapTable.rise_time[trap_id - 1];
            int currflat = SeqTrapTable.flat_time[trap_id - 1];
            int currfall = SeqTrapTable.fall_time[trap_id - 1];

            for (int j=0; j<Seq_NGrad; j++) {
                if ((currrise == SeqGradients[j].rise_time) &&
                    (currflat == SeqGradients[j].flat_time) &&
                    (currfall == SeqGradients[j].fall_time) && 
                    (currdur == SeqGradients[j].duration )) { 
                        found = 1;
                        shape_id = SeqGradients[j].id; // Use existing shape ID
                        //printf("  Existing match shapeindex %d\n", shape_id);
                        break;
                    }
            }

            if (!found) {
                // Add new shape
                if (Seq_NGrad < MAX_SHAPES) {
                    shape_id = Seq_NGrad; // Use the new gradient shape ID
                    printf("  New unique grad shape: block %d, trap %d, (dur %d rise %d flat %d fall %d) newshapeindex %d\n", 
                                SeqBlockTable.num[i], trap_id, currdur, currrise, currflat, currfall, shape_id);
                    SeqGradients[Seq_NGrad].id = Seq_NGrad;

                    int n_rise = (int)round(currrise / gradrastertime);
                    int n_flat = (int)round(currflat / gradrastertime);
                    int n_fall = (int)round(currfall / gradrastertime);
                    int n_dur = (int)round((currdur - currrise - currflat - currfall) / gradrastertime);
                    int n_total = n_rise + n_flat + n_fall + n_dur;

                    SeqGradients[Seq_NGrad].num_samples = n_total;
                    SeqGradients[Seq_NGrad].samples = (double*)malloc(n_total * sizeof(double));
                    SeqGradients[Seq_NGrad].rise_time = currrise;
                    SeqGradients[Seq_NGrad].flat_time = currflat;
                    SeqGradients[Seq_NGrad].fall_time = currfall;
                    SeqGradients[Seq_NGrad].duration = currdur;


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
                    // zeroes
                    for (int k = 0; k < n_dur; k++) {
                        SeqGradients[Seq_NGrad].samples[n_rise + n_flat + n_fall + k] = 0;
                    }

                }
                Seq_NGrad++;
            }

            if (g==0) {
                SeqBlockTable.gx_shape_id[i] = shape_id + 1;
            } else if (g==1) {
                SeqBlockTable.gy_shape_id[i] = shape_id + 1;
            } else if (g==2) {
                SeqBlockTable.gz_shape_id[i] = shape_id + 1;
            }
        }
    }

    printf("Done.\n");

}

/*
* Only available in paravision; PVM_ppgGradShape1 and PVM_ppgGradShape1Size through 32 are declared variables.
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
            sscanf(line, "FOV %lf %lf %lf", &SeqDefinitions.FOV[0], &SeqDefinitions.FOV[1], &SeqDefinitions.FOV[2]);
            sscanf(line, "GradientRasterTime %lf", &SeqDefinitions.GradientRasterTime);
            sscanf(line, "Name %s", SeqDefinitions.Name);
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
                int id, mag_id, phase_id, time_shape_id, delay;
                double freq, phase, amplitude;
                if (sscanf(line, "%d %lf %d %d %d %d %lf %lf", 
                    &id, &amplitude, &mag_id, &phase_id, &time_shape_id, &delay, &freq, &phase) == 8) {
                    SeqRFTable.id[Seq_NRF] = id;
                    SeqRFTable.amplitude[Seq_NRF] = amplitude;
                    SeqRFTable.mag_id[Seq_NRF] = mag_id;
                    SeqRFTable.phase_id[Seq_NRF] = phase_id;
                    SeqRFTable.shape_id[Seq_NRF] = time_shape_id;
                    SeqRFTable.delay[Seq_NRF] = delay;
                    SeqRFTable.freq[Seq_NRF] = freq;
                    SeqRFTable.phase[Seq_NRF] = phase;
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
                int id, num, delay, dwell;
                double freq, phase;
                if (sscanf(line, "%d %d %d %d %lf %lf", 
                    &id, &num, &dwell, &delay, &freq, &phase) == 6) {  
                    SeqADCTable.id[Seq_NADC] = id;
                    SeqADCTable.num[Seq_NADC] = num;
                    SeqADCTable.dwell[Seq_NADC] = dwell;
                    SeqADCTable.delay[Seq_NADC] = delay;
                    SeqADCTable.freq[Seq_NADC] = freq;
                    SeqADCTable.phase[Seq_NADC] = phase;
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
           SeqDefinitions.FOV[0], SeqDefinitions.FOV[1], SeqDefinitions.FOV[2], SeqDefinitions.GradientRasterTime);
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



void WriteRFShapeToExp(SHAPE shape, const char* filename, double* phase_samples) 
{

    int addPhase = 1;
    if (phase_samples == NULL) {
        addPhase = 0; // No phase samples provided, do not write phase
    }

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
        if (addPhase) {
            fprintf(fid, "%.6e %.6e\n", shape.samples[i]*100.0, phase_samples[i]/0.5*180.0); // Convert amp to % (100max); phase to degrees
        } else {
            fprintf(fid, "%.6e\n", shape.samples[i]);
        }
    }
    fprintf(fid,"##END=\n");

    fclose(fid);

    printf("  Shape written to %s\n", filename);

}



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
    fprintf(fid, "; Seq file Name tag: %s \n", SeqDefinitions.Name);
    fprintf(fid, "; Total scan time: %lf seconds \n", SeqDefinitions.Totaltime/1000);
  
    // Get current date and time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    // Write formatted date and time to the file
    fprintf(fid, "; Date: %04d-%02d-%02d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    fprintf(fid, "; Time: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
    fprintf(fid, "; Paravision Pulseq Interpreter Version: %s\n", ParavisionPulseqVersion);
    fprintf(fid, ";\n\n");


    //didn't need to declare shapes in ppg, these are already accessible as the variables
    // for (int i =0; i<Seq_NGrad; i++) {
    //     fprintf(fid, "#declare list<gradient> ppgGrad%d = {$PVM_ppgGradShape%d}  ;grad id %d\n",i, i, SeqGradients[i].id);
    // }

    fprintf(fid,"\n\n");

    fprintf(fid, ";-------include files-------\n");
    fprintf(fid, "#include <MRI.include>\n\n");


    fprintf(fid, "\n;-------rf lists-------\n");
    fprintf(fid, "define list<frequency> freqRFList = {$SeqRFFrequencyList}\n");
    fprintf(fid, "define list<phase> phaseRFList = {$SeqRFPhaseList}\n");
    fprintf(fid, "define list<power> powRFList = {Watt $SeqRFPowerList}\n");
    fprintf(fid, "\n");

    fprintf(fid, "\n;-------adc lists-------\n");
    fprintf(fid, "define list<frequency> freqADCList = {$SeqADCFrequencyList}\n");
    fprintf(fid, "define list<phase> phaseADCList = {$SeqADCPhaseList}\n");
    fprintf(fid, "\n");


    fprintf(fid, ";-----gradient shapes-----\n");
    fprintf(fid, "; for reference, unnecessary to explicitly redefine here in ppg\n");
    fprintf(fid, ";         dur  rise  flat  fall \n");
    for (int i = 0; i < Seq_NGrad; i++) {
        int shapeind = SeqGradients[i].id;
        fprintf(fid,"  ; PVM_ppgGradShape%d is %du %du %du %du\n", shapeind, SeqGradients[shapeind].duration, SeqGradients[shapeind].rise_time, SeqGradients[shapeind].flat_time, SeqGradients[shapeind].fall_time);
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
            // RF block

            fprintf(fid, "\n");
            fpcnt = fprintf(fid, "    1u gc_control ");
            fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
            fprintf(fid, "; block %d w RF\n", SeqBlockTable.num[b]);
            fprintf(fid, "    {\n");

            fprintf(fid, "        %du ", SeqBlockTable.dur[b]);
            if (SeqBlockTable.gx[b] > 0 || SeqBlockTable.gy[b] > 0 || SeqBlockTable.gz[b] > 0) {
                int gxind, gyind, gzind;
                fpcnt += fprintf(fid, "grad_shape{");
                if (SeqBlockTable.gx[b] > 0) {
                    gxind = SeqBlockTable.gx_shape_id[b] - 1;
                    fprintf(fid, "PVM_ppgGradShape%d() * %.3lf, ", gxind, SeqTrapTable.amp_percent[gxind]);
                } else {
                    fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gy[b] > 0) {
                    gyind = SeqBlockTable.gy_shape_id[b] - 1;
                    fprintf(fid, "PVM_ppgGradShape%d() * %.3lf, ", gyind, SeqTrapTable.amp_percent[gyind]);
                } else {
                    fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gz[b] > 0) {
                    gzind = SeqBlockTable.gz_shape_id[b] - 1;
                    fprintf(fid, "PVM_ppgGradShape%d() * %.3lf", gzind, SeqTrapTable.amp_percent[gzind]);
                } else {
                    fprintf(fid, "0");
                }
                fprintf(fid, "}\n");
                fprintf(fid, "    }\n");


                //int freqsettime = 60;  //need to figure this out.
                fpcnt = fprintf(fid, "    %du freqRFList:f1  powRFList:f1  gatepulse 1 ", SeqRFTable.delay[SeqBlockTable.rf[b]]);                
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, ";   rf delay\n");
                fpcnt = fprintf(fid, "    (%dup:sp0(currentpower) phaseRFList):f1 ",SeqBlockTable.dur[b]);
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, ";   pulse\n");
                
                fpcnt = fprintf(fid, "    %du freqRFList.inc powRFList.inc phaseRFList.inc ", InterGradientWaitTime);
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, ";   implied block + igwt\n");

                fprintf(fid, "\n");

            } 
            

        } else if (SeqBlockTable.adc[b] > 0) {
            // ADC block


            fprintf(fid, "\n");
            fpcnt = fprintf(fid, "    1u gc_control ");
            fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
            fprintf(fid, "; block %d w ADC\n", SeqBlockTable.num[b]);
            fprintf(fid, "    {\n");


            fprintf(fid, "        %du ", SeqBlockTable.dur[b]);
            if (SeqBlockTable.gx[b] > 0 || SeqBlockTable.gy[b] > 0 || SeqBlockTable.gz[b] > 0) {
                int gxind, gyind, gzind;
                fpcnt += fprintf(fid, " grad_shape{");
                if (SeqBlockTable.gx[b] > 0) {
                    gxind = SeqBlockTable.gx_shape_id[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d() * %.3lf, ", gxind, SeqTrapTable.amp_percent[gxind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gy[b] > 0) {
                    gyind = SeqBlockTable.gy_shape_id[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d() * %.3lf, ", gyind, SeqTrapTable.amp_percent[gyind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gz[b] > 0) {
                    gzind = SeqBlockTable.gz_shape_id[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d() * %.3lf", gzind, SeqTrapTable.amp_percent[gzind]);
                } else {
                    fpcnt += fprintf(fid, "0");
                }
                fpcnt += fprintf(fid, "} \n");
                fprintf(fid, "    } \n");

                fpcnt = fprintf(fid, "    %du ", SeqADCTable.delay[SeqBlockTable.adc[b] - 1]);
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, ";   adc delay\n");

                fpcnt = fprintf(fid, "    aqq ADC_START ");
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, ";   adc start\n");

                // fprintf(fid, "    %du ", SeqBlockTable.dur[b]);

                fpcnt = fprintf(fid, "    %du ADC_END  phaseADCList.inc", InterGradientWaitTime);
                fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
                fprintf(fid, ";   implied block + igwt\n");
                fprintf(fid, " \n");

            }

        } else {
        // No RF or ADC, just a gradient or delay block

            fpcnt = fprintf(fid, "    %du ", SeqBlockTable.dur[b]);

            if (SeqBlockTable.gx[b] > 0 || SeqBlockTable.gy[b] > 0 || SeqBlockTable.gz[b] > 0) {

                int gxind, gyind, gzind;
                fpcnt += fprintf(fid, "grad_shape{");

                if (SeqBlockTable.gx[b] > 0) {
                    gxind = SeqBlockTable.gx_shape_id[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d() * %.3lf, ", gxind, SeqTrapTable.amp_percent[gxind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gy[b] > 0) {
                    gyind = SeqBlockTable.gy_shape_id[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d() * %.3lf, ", gyind, SeqTrapTable.amp_percent[gyind]);
                } else {
                    fpcnt += fprintf(fid, "0, ");
                }
                if (SeqBlockTable.gz[b] > 0) {
                    gzind = SeqBlockTable.gz_shape_id[b] - 1;
                    fpcnt += fprintf(fid, "PVM_ppgGradShape%d() * %.3lf", gzind, SeqTrapTable.amp_percent[gzind]);
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
            fpcnt = fprintf(fid, "    ADC_INIT_B(NOPH, phaseADCList) ");
            fprintf(fid, "%*s", CommentColumn - fpcnt, "");  // pad with spaces
            fprintf(fid, "; implied block + de\n");
        }

        
    }


    fprintf(fid, "\n\nbye,    1u\n");
    fprintf(fid, "\n\nSETUP_GOTO(start)\n");
    fprintf(fid, "exit,\n");


    printf("Done. %s...\n\n", ppgfile);

}