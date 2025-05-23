
#define MAX_SHAPES 6

#include "DwiWaveformTypes.h"

char parameter
{
    display_name "Version Tag";
    editable false;
} DwVersionTag[100];

double parameter
{
    display_name "Gradient Duration1";
    format "%.02f";
    units "ms";
    editable false;
    relations backbone;
} DwGradDur1;

double parameter
{
    display_name "Gradient Duration2";
    format "%.02f";
    units "ms";
    editable false;
    relations backbone;
} DwGradDur2;

double parameter 
{ 
    display_name "Delay between Dw Gradients";
    format "%.02f";
    units "ms";
    editable false;
    relations backbone;
} DwGradSep;

double parameter { format "%.02f"; } DwDelay1;
double parameter { format "%.02f"; } DwDelay2;
double parameter { format "%.02f"; } DwModuleDur;
double parameter { format "%.02f"; } DwMinSep;
double parameter DwD1;
double parameter DwD2;
double parameter DwD3;
double parameter DwD4;
double parameter DwD5;

double parameter Dw_acqgradmatrix_override[][3][3];


char parameter
{
    display_name "POINTS/DUR Check:";
    editable false;
} DwStatusString[100];


double parameter {
  display_name "Gradient Separation";
  relations backbone;
  format "%.02f";
  units "ms";  
} DwGradTsep;


double parameter DW1GS0R[];
double parameter DW1GS0P[];
double parameter DW1GS0S[];
double parameter DW1GS1R[];
double parameter DW1GS1P[];
double parameter DW1GS1S[];
double parameter DW1GS2R[];
double parameter DW1GS2P[];
double parameter DW1GS2S[];
double parameter DW1GS3R[];
double parameter DW1GS3P[];
double parameter DW1GS3S[];
double parameter DW1GS4R[];
double parameter DW1GS4P[];
double parameter DW1GS4S[];
double parameter DW1GS5R[];
double parameter DW1GS5P[];
double parameter DW1GS5S[];


double parameter DwR00[];
double parameter DwR01[];
double parameter DwR02[];
double parameter DwR10[];
double parameter DwR11[];
double parameter DwR12[];
double parameter DwR20[];
double parameter DwR21[];
double parameter DwR22[];

double parameter DwGAmpRot00[];
double parameter DwGAmpRot01[];
double parameter DwGAmpRot02[];
double parameter DwGAmpRot10[];
double parameter DwGAmpRot11[];
double parameter DwGAmpRot12[];
double parameter DwGAmpRot20[];
double parameter DwGAmpRot21[];
double parameter DwGAmpRot22[];

double parameter DwBval[];

/**** Custom sequence table */
char parameter
{
    display_name "Custom Seq string1";
    relations backbone;
} DwCustomStrArr1[][100];

DYNDWSEQFILE parameter
{
    display_name "DW Seq File";
    relations DwSeqFileHandler;
} DwSeqFileDynEnum;

DYNDWSEQFILE parameter TempSeq;

char parameter
{
    display_name "Dw Seq File String";
    relations backbone;
} DwSeqFileBase[100];

char parameter
{
    display_name "Seq File Path";
    editable false;
} DwSeqFileFullPath[];

char parameter
{
    display_name "Seq File Exp Path";
    editable false;
} ExpDwSeqFileFullPath[];
        
void parameter 
{
    display_name "Load DwSeq File";
    relations DwSeqLoadHandler;
} DwSeqLoadFunction;

int parameter DwShape1IndArray[];
int parameter DwShape2IndArray[];

DWSEQDEFS parameter DwSeqDefinitions;
DWSEQENTRYTABLE parameter DwSeqEntryTable;
DWSEQDIRTABLE parameter DwSeqDirTable;
DWSEQSHAPE parameter DwSeqShapeTable[MAX_SHAPES];

int parameter {editable false;} DwSeqNumEntries ;
int parameter {editable false;} DwSeqNumDirs;
int parameter {editable false;} DwSeqNumShapes;

char parameter
{
    display_name "SeqFile Internal Name";
    editable false;
} DwSeqFileName[64];



parclass
{
    DwCustomStrArr1;
    DwSeqFileName;
    DwSeqFileDynEnum;
    TempSeq;
    DwSeqFileBase;
    DwSeqFileFullPath;
    ExpDwSeqFileFullPath;
    DwSeqEntryTable;
    DwSeqDirTable;
    DwSeqShapeTable;
    DwSeqDefinitions;
    DwSeqNumEntries;
    DwSeqNumDirs;
    DwSeqNumShapes;
} DwSeqPars;


parclass
{   
    DwVersionTag;
    DwStatusString;
    DwGradDur1;
    DwGradDur2;
    DwGradSep;
    DwDelay1;
    DwDelay2;
    DwGradTsep;
    DwModuleDur;
    DwMinSep;
    DW1GS0R;
    DW1GS0P;
    DW1GS0S;
    DW1GS1R;
    DW1GS1P;
    DW1GS1S;
    DW1GS2R;
    DW1GS2P;
    DW1GS2S;
    DW1GS3R;
    DW1GS3P;
    DW1GS3S;
    DW1GS4R;
    DW1GS4P;
    DW1GS4S;
    DW1GS5R;
    DW1GS5P;
    DW1GS5S;
    DwR00;
    DwR11;
    DwR22;
    DwR01;
    DwR02;
    DwR10;
    DwR12;
    DwR20;
    DwR21;
    DwGAmpRot00;
    DwGAmpRot11;
    DwGAmpRot22;
    DwGAmpRot01;
    DwGAmpRot02;
    DwGAmpRot10;
    DwGAmpRot12;
    DwGAmpRot20;
    DwGAmpRot21;
    DwShape1IndArray;
    DwShape2IndArray;
    Dw_acqgradmatrix_override;
    DwSeqPars;
} DwiWaveform;