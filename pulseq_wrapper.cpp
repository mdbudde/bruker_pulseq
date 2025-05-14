// parsemr_wrapper.cpp

#include "ExternalSequence.h"
//#include <cstdint>
#include <stdint.h>
#include <string>

extern "C" {

int LoadSeqFile(const char* path_cstr) {
    std::string path_cpp(path_cstr);
    ExternalSequence seq;
    seq.load(path_cpp);
    // Do whatever minimal work you need here, or call another helper class
    return 1;
}

}
    