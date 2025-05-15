// parsemr_wrapper.h
#ifndef PARSEMR_WRAPPER_H
#define PARSEMR_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// typedef void* ExternalSequenceHandle;

// int ExternalSequence_load(ExternalSequenceHandle handle, const char* path);

int LoadSeqFile(const char* path_seq);
int TranslateSeqToPpg(const char* path_seq, const char* path_ppg);


// Opaque pointer handle for C interface
typedef void* ExternalSequenceHandle;

// Struct forward-declared for typed access (used only with pointer)
typedef struct ExternalSequence ExternalSequence;


/**
 * Create a new ExternalSequence instance.
 * Returns a handle to the object.
 */
ExternalSequenceHandle ExternalSequence_create();

/**
 * Load a sequence from a directory path.
 * Returns 1 on success, 0 on failure.
 */
int ExternalSequence_load(ExternalSequenceHandle handle, const char* path);
void ExternalSequence_destroy(ExternalSequenceHandle handle);

/**
 * Extract FOV values .
 */
void Seq_getFOV(ExternalSequence* handle, double* fov0, double* fov1, double* fov2);

/**
 * Calculate total time from all events.
 */
double Seq_getTotalTime(ExternalSequence* handle, double* totaltime);


#ifdef __cplusplus
}
#endif

#endif
