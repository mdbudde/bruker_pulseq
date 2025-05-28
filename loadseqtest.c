

#include <stdio.h>
#include "PulseqInterpreter.h"

int main() {
    const char *filename = "gre.seq";
    
    // Attempt to load the sequence file
    LoadSequenceFile(filename);

    UpdateSeq();

    return 0;
}