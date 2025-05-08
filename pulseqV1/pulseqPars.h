
#include "pulseqTypes.h"

char parameter
{
    display_name "Version Tag";
    editable false;
} SeqVersionTag[100];

DYNSEQFILE parameter
{
    display_name "Pulseq File";
    relations PulseqFileHandler;
} PulseqFileDynEnum;

DYNSEQFILE parameter TempSeq;

char parameter
{
    display_name "Pulsew File String";
    relations backbone;
} PulseqFileStrArr[100];

char parameter
{
    display_name "Version Tag";
    editable false;
} MethodVersionTag[100];

parclass
{   
    SeqVersionTag;
    PulseqFileDynEnum;
    PulseqFileStrArr;
    TempSeq;
    MethodVersionTag;
} PulseqParameters;