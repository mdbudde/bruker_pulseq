
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
    display_name "Seq File String";
    relations backbone;
} PulseqFileBase[100];

char parameter
{
    display_name "Seq File Path";
    editable false;
} PulseqFileFullPath[];

char parameter
{
    display_name "Version Tag";
    editable false;
} MethodVersionTag[100];

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
    relations PvTranslateSeqToPpg;
} SeqToPpgFunction;


char parameter 
{
    editable false;
} ExpPpgFile[];

char parameter 
{
    editable false;
} ScanPpgFile[];


parclass
{   
    SeqVersionTag;
    PulseqFileDynEnum;
    PulseqFileBase;
    PulseqFileFullPath;
    TempSeq;
    MethodVersionTag;
    ExpPpgFile;
    ScanPpgFile;
    SeqToPpgFunction;
} PulseqParameters;
