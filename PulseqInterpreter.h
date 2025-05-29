/**
 * @file LoadSequence.h
 * @brief Header file for loading and handling pulse sequence data for Bruker ParaVision.
 *
 * This file defines constants, data structures, and function prototypes used for
 * loading, parsing, and managing pulse sequence files and related data blocks.
 *
 * Structures defined include representations for versioning, sequence definitions,
 * block tables, RF tables, gradient trapezoid tables, ADC tables, and shape data.
 * 
 * Functions are provided for loading sequence files, decompressing and writing shape data,
 * exporting shapes, writing PPG files, and converting gradient trapezoids to gradient shapes.
 *
 * Constants define maximum sizes for various sequence components.
 */
#ifndef LOADSEQUENCE_H
#define LOADSEQUENCE_H

// Include necessary headers
#include <string.h>


#define MAX_LINE 1024
#define MAX_BLOCKS 2048
#define MAX_RF 256
#define MAX_TRAP 256
#define MAX_ADC 256
#define MAX_SHAPES 512

// SECTION STRUCTS; these will become paravision types in the sequence method
// internal additions to the pulseq-defined types include "added" in the comment
typedef struct {
    int major;
    int minor;
    int revision;
} Version;

typedef struct {
    double FOV[3];
    double GradientRasterTime;
    char Name[64]; // added: name of the sequence
} Definitions;

typedef struct {
    int num[MAX_BLOCKS];
    int dur[MAX_BLOCKS];
    int rf[MAX_BLOCKS];
    int gx[MAX_BLOCKS];
    int gy[MAX_BLOCKS];
    int gz[MAX_BLOCKS];
    int adc[MAX_BLOCKS];
    int ext[MAX_BLOCKS];
} BLOCKTABLE;

typedef struct {
    int id[MAX_RF];
    double delay[MAX_RF];
    double freq[MAX_RF]; 
    double phase[MAX_RF];
    double amp[MAX_RF];
    int shape_id[MAX_RF];
} RFTABLE;

typedef struct {
    int id[MAX_TRAP];
    double amp[MAX_TRAP]; 
    int rise_time[MAX_TRAP];  //int in microseconds
    int flat_time[MAX_TRAP];  //int in microseconds
    int fall_time[MAX_TRAP];  //int in microseconds
    int delay[MAX_TRAP];
    int grad_shape_id[MAX_TRAP]; // added: ID of the gradient shape created with this trapezoid
    double amp_percent[MAX_TRAP]; // added: amp calculated as percentage of max gradient
} TRAPTABLE;

typedef struct {
    int id[MAX_ADC];
    int num_samples[MAX_ADC];
    int dwell[MAX_ADC];  //int in nanoseconds
    int delay[MAX_ADC];  //in in microseconds
    double freq[MAX_ADC];
    double phase[MAX_ADC];
} ADCTABLE;

typedef struct {
    int id;
    int num_samples;
    double* samples;
    int samples_loaded;    //added: to track how many samples have been loaded; is shape compressed if samples_loaded < num_samples? 
    char shape_label[64];  //added: to help identify shapes/external files
    char shape_type[64];   //added: to help identify shapes/external files
} SHAPE;

typedef struct {
    int id;
    int num_samples;
    double* samples;
} GRADSHAPE;

/**
 * @brief Loads a sequence from a file.
 * 
 * This function reads a sequence file specified by the filename, parses its contents,
 * and loads the sequence data into the appropriate data structures.
 *
 * @param filename The path to the sequence file.
 * @return int Returns 0 on success, or an error code on failure.
 */
int LoadSequenceFile(const char* filename);

/**
 * @brief Updates the sequence data. Main Paravision function in backbone
 */
void UpdateSeq(void);


/**
 * @brief Decompresses an encoded shape into a raw shape array.
 * 
 * This function takes an encoded SHAPE structure and decompresses its data into
 * the provided shape array.
 *
 * @param encoded The encoded SHAPE structure.
 * @param shape Pointer to the output array where decompressed samples will be stored.
 * @return int Returns 0 on success, or an error code on failure.
 */
int decompressShape(SHAPE encoded, double *shape);

/**
 * @brief Writes a shape to an export file.
 * 
 * This function exports the given encoded SHAPE structure to a file specified by filename.
 *
 * @param encoded The encoded SHAPE structure to write.
 * @param filename The path to the output file.
 * @return int Returns 0 on success, or an error code on failure.
 */
void WriteShapeToExp(SHAPE encoded, const char* filename);

/**
 * @brief Writes a PPG (Pulse Program) file.
 * 
 * This function generates and writes a PPG file based on the currently loaded sequence data.
 *
 * @param ppgfile The path to the output PPG file.
 * @return int Returns 0 on success, or an error code on failure.
 */
void WritePPG(const char* ppgfile);

/**
 * @brief Converts gradient trapezoids to gradient shapes.
 * 
 * This function processes the loaded gradient trapezoid data and converts it into
 * gradient shape representations.
 *
 * @return int Returns 0 on success, or an error code on failure.
 */
void GradTrapToGradShape(double gradrastertime);
void GradShapeToPPGShape(void);
void LoadPPGShape(double *ppgGradShape, int shapeind, int shapesize);


#endif // LOADSEQUENCE_H