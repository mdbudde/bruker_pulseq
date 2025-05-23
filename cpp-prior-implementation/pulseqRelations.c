/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/parsRelations.c,v $
 *
 *
 ****************************************************************/

static const char resid[] = "$Id: parsRelations.c,v 1.73.2.1 2013/12/10 16:21:57 mawi Exp $ (C) 2002 Bruker BioSpin MRI GmbH";

#define DEBUG		1
#define DB_MODULE	0
#define DB_LINE_NR	0

#define VersionTag "v0.1"

#include "method.h"
#include "time.h"
#include "pulseqTypes.h"
#include "pulseq_wrapper.h"


void InitPulseq(void) {

        PARX_change_dims("ExpPpgFile",PATH_MAX);
        PARX_change_dims("ScanPpgFile",PATH_MAX);
        PARX_change_dims("PulseqFileFullPath",PATH_MAX);

        // exp pulse program location
        PvOvlUtilGetExpnoPath(ExpPpgFile, PATH_MAX, "pulseq_exp.ppg");
            
        // user pulse program location
        PvPathMkHomePv(ScanPpgFile, NULL);
        strcat(ScanPpgFile, "/exp/lists/pp/pulseq_scan.ppg");

}



void UpdatePulseq(void) {
    
        UpdateSeqList();
        int seqInd;
        int success = 0;
        TempSeq = PulseqFileDynEnum;  
        ParxRelsParGetEnumValueAsInt("TempSeq", &seqInd);
        const char *seq_file = ParxRelsIntToEnumStr("TempSeq", seqInd);
        strcpy(PulseqFileBase,seq_file);
        

        PvPathMkHomePv(PulseqFileFullPath, NULL);
        strcat(PulseqFileFullPath, "/exp/lists/seq/");      
        strcat(PulseqFileFullPath, seq_file);      
    
}


void UpdateSeqList(void)
{
        char seqpath[100];/* seq directory path   */
        PvPathMkHomePv(seqpath, NULL);  //Create a string  PVINSTDIR/prog/curdir/USER/ParaVision.
        strcat(seqpath,"/exp/lists/seq/");
        
        //Update list of available files
        PTB_InitDynEnumWithRegFileNames("PulseqFileDynEnum", seqpath);
        PTB_InitDynEnumWithRegFileNames("TempSeq", seqpath);
}



// Update when the Seq selector is changed, reverts if file doesn't load correctly.
void PulseqFileHandler(void)
{
    DB_MSG(("-->Seq Handler1"));
    
        UpdateSeqList();  
        
        UT_SetRequest("PulseqFileDynEnum");
        int reqIndex = UT_RequestIndex(0);
        
        
        int seqInd;
        TempSeq = PulseqFileDynEnum;        
        
        int hasValSet = ParxRelsEnumHasDynamicValueSet("TempSeq");
        if (hasValSet == No)
        {
            UT_ClearRequest();
            return;
        }
        YesNo hasVal = ParxRelsParGetEnumValueAsInt("TempSeq", &seqInd);
        
        if (hasVal == No)
        {
            UT_ClearRequest();
            return;
        }
        
        const char *seq_file = ParxRelsIntToEnumStr("TempSeq", seqInd);

        
        char seqpath[PATH_MAX];/* directory path   */
        PvPathMkHomePv(seqpath, NULL);
        strcat(seqpath, "/exp/lists/seq/");      
        strcat(seqpath, seq_file);  
        int success = LoadSeqFile(seqpath);
        
        if ((success)) 
        {
            strcpy(PulseqFileBase,seq_file);
            strcpy(PulseqFileFullPath,seqpath);
            //UT_RequestParOrigValue(TempShape);
        }
            
        UT_ClearRequest();
        backbone();
        
    
    DB_MSG(("--<PulseqFileHandler"));
}


int PvTranslateSeqToPpg() {

    int dim;
    dim = PTB_GetSpatDim();

    ExternalSequenceHandle seq = ExternalSequence_create();
    if (ExternalSequence_load(seq, PulseqFileFullPath)) {
        double d0, d1, d2;
        Seq_getFOV((ExternalSequence*)seq, &d0, &d1, &d2);
        PVM_Fov[0] = d0*100;
        PVM_Fov[1] = d1*100;
        if (dim > 2) {
            PVM_Fov[2] = d2*1000 * PVM_Matrix[2];
            PVM_SliceThick = PVM_Fov[2];
        } else {
            PVM_SliceThick = d2*1000;
        }
        Seq_getTotalTime((ExternalSequence*)seq, &PVM_ScanTime);
        UT_ScanTimeStr(PVM_ScanTimeStr,PVM_ScanTime);
        
        /* this writes the ppg to the current exp directory */
        TranslateSeqToPpg(PulseqFileFullPath, ExpPpgFile);

/* PV has up to 32 grad shapes predefined, do these make it to ppg defines as well?
    ...
    PVM_ppgGradShape32Size;
    PVM_ppgGradShape32[];
    PVM_ppgGradShapeArraySize[2];
    PVM_ppgGradShapeArray[][];
*/

    }
    return 0;

}



/* set parameters just before acquisition */
void SetBeforeAcquisition( void )
{
  DB_MSG(("-->SetBeforeAcquisition"));

  int success = 0;
  if (PVM_AcqScanHandler == Scan_Experiment) 
  {
      success = CopyPPGScan();
  }

  DB_MSG(("<--SetBeforeAcquisition"));
}


int WriteExpPpgFile()
{
  
    FILE *fp = fopen(ExpPpgFile, "w");  // Open file for writing (overwrite if exists)
    if (fp == NULL) {
        perror("Failed to open file");
        return 0;
    }

    fprintf(fp, ";method generated ppg file\n");
    
    
    fprintf(fp, "#include <MRI.include>\n");
    fprintf(fp, "preset off\n\n");
    fprintf(fp, "INIT_DEVICES\n\n");
    fprintf(fp, "exit\n\n");
   
    fclose(fp);  // Close the file
    
    return 1; //success
}
    
   //called from SetBeforeAcquisition and callback handler for testing
int CopyPPGScan()
{
    
    DB_MSG(("-->CopyPPGScan\n"));

    PvUtilCopyFile(ScanPpgFile, ExpPpgFile); // note this is (dest, source))
    
    DB_MSG(("<--CopyPPGScan\n"));
    return 1;
}


