
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

double parameter
{
    display_name "Delays";
    editable false;
    units "ms";
} DelayArray[];

double parameter
{
    display_name "Gradient";
    editable false;
    units "ms";
} GradientShapeArray[];

void parameter 
{
    display_name "PPG testwrite";
    relations CopyPPGScan;
} TestPPGfileGen;


char parameter 
{
    editable false;
} ExpPpgFile[];