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

#ifdef __cplusplus
}
#endif

#endif
