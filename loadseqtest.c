

#include <stdio.h>
#include "LoadSequence.h"

int main() {
    const char *filename = "gre.seq";
    int result;

    // Attempt to load the sequence file
    result = LoadSequenceFile(filename);

    if (result == 0) {
        printf("Sequence file '%s' loaded successfully.\n", filename);
    } else {
        printf("Failed to load sequence file '%s'. Error code: %d\n", filename, result);
    }

    UpdateSeq();

    return 0;
}