/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/parsRelations.c,v $
 *
 * Copyright (c) 2002 - 2003
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: parsRelations.c,v 1.73.2.1 2013/12/10 16:21:57 mawi Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: parsRelations.c,v 1.73.2.1 2013/12/10 16:21:57 mawi Exp $ (C) 2002 Bruker BioSpin MRI GmbH";

#define DEBUG		1
#define DB_MODULE	0
#define DB_LINE_NR	0

//trick to string-ify PVDIR from makefile
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
// PVDIR is added as -DPVDIR in Makefile, but if not, just define it here.
#ifndef PVDIR 
#define PVDIR /opt/PV6.0.1/  //don't quote since we need the same behavior as the passed -DPVDIR 
#endif

#define VersionTag "v0.1"

#include "method.h"
#include "time.h"
#include "pulseqTypes.h"
#include "pulseq_wrapper.h"


void UpdatePulseq(void) {
    UpdateSeqList();
        int seqInd;
        TempSeq = PulseqFileDynEnum;  
        ParxRelsParGetEnumValueAsInt("TempSeq", &seqInd);
        const char *seq_file = ParxRelsIntToEnumStr("TempSeq", seqInd);
        strcpy(PulseqFileStrArr,seq_file);
        
        
     PARX_change_dims("ExpPpgFile",PATH_MAX);
     PvOvlUtilGetExpnoPath(ExpPpgFile, PATH_MAX, "pulseq_exp.ppg");
      
    
     WriteExpPpgFile();
}


void UpdateSeqList(void)
{
        char seqpath[100];/* gp directory path   */
        char *user= getenv("USER");
        const char *pvdir = STR(PVDIR);
        //char *pvdir = getenv("XWINNMRHOME");  This could be used, but multiple versions installed in the same system would be an issue
        strcpy(seqpath, pvdir);
        //strcpy(shapepath, pvdir);
        strcat(seqpath, "/prog/curdir/");
        strcat(seqpath, user);
        strcat(seqpath, "/ParaVision/exp/lists/seq/");
        
        //Update list of available files
        PTB_InitDynEnumWithRegFileNames("PulseqFileDynEnum", seqpath);
        PTB_InitDynEnumWithRegFileNames("TempSeq", seqpath);
}



// Update when the Gradient Shape is changed.
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


        int MAXCHAR = 100;    
        char seqpath[MAXCHAR];
        
        char *pvhome= getenv("XWINNMRHOME");        
        char *user= getenv("USER");
        
        strcpy(seqpath, pvhome);
        strcat(seqpath, "/prog/curdir/");
        strcat(seqpath, user);
        strcat(seqpath, "/ParaVision/exp/lists/seq/");      
        strcat(seqpath, seq_file);        


        printf("Update of seq %s  .\n",seqpath); 
        PARX_sprintf("Update of seq %s .\n",seqpath); 

        int success = LoadSeqFile(seqpath);
        
        if ((success)) 
        {
            strcpy(PulseqFileStrArr,seq_file);
            //UT_RequestParOrigValue(TempShape);
        }
            
        UT_ClearRequest();
        backbone();
        
    
    DB_MSG(("--<PulseqFileHandler"));
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
  /* else
  {
    
  } */

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
    
    
    /* time_t now = time(NULL);                 // Get current time
    char *time_str = ctime(&now);
    fprintf(fp, ";timestamp: %s\n", time_str);
    */
    
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
    
    // user pulse program location
    char scanPpgFile[100];
    char *user= getenv("USER");
    const char *pvdir = STR(PVDIR);
    strcpy(scanPpgFile, pvdir);
    strcat(scanPpgFile, "/prog/curdir/");
    strcat(scanPpgFile, user);
    strcat(scanPpgFile, "/ParaVision/exp/lists/pp/pulseq_scan.ppg");
        
    printf("scanPpgFile: %s\n", scanPpgFile);
    PARX_sprintf("scanPpgFile: %s\n", scanPpgFile);
    
    PvUtilCopyFile(scanPpgFile, ExpPpgFile); // note this is (dest, source))
    
        
    DB_MSG(("<--CopyPPGScan\n"));
    return 1;
}


