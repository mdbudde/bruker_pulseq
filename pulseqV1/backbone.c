
/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/backbone.c,v $
 *
 * Copyright (c) 2009
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: backbone.c,v 1.50.2.1 2015/03/23 07:43:19 mawi Exp $
 *
 * ***************************************************************/


static const char resid[] = "$Id $ (c) 2007Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	0
#define DB_LINE_NR	0

#include "method.h"

/* global variables */
double EchoDelay, EffPulseDur;

void backbone(void)
{
  double minFov[3];
  double minSliceThick;

  DB_MSG(("-->backbone"));

  /* update nuclei parameter group                            */

  STB_UpdateNuclei(No);

  /* update encoding parameter group                          */
  
  STB_UpdateEncoding(
    NULL,
    SEG_SEQUENTIAL,
    Yes,
    Yes,
    Yes,
    &PVM_EchoPosition);
 
  /* update parameters controlling the data sampling period   */

  STB_UpdateDigPars(&PVM_EffSWh,
                    PVM_EncMatrix[0],
                    &PVM_AntiAlias[0],
                    &PVM_AcquisitionTime);

  /* update excitation pulse                                  */  
  
  UpdateRFPulses();
    

  /* general features of the method */

  PVM_NEchoImages = 1;

  /* coexistance of modules: */
  if(PVM_SelIrOnOff == On)
  {
    PVM_BlBloodOnOff = Off;
    PVM_NMovieFrames = 1;
  }

  /* set limits for read, phase and slice gradients            */

  ControlGradientLimits(PVM_MajSliceOri);
  

  /* calculate minima for FOV and slice thickness             */

  UpdateGeometryMinima(minFov,
                       &minSliceThick);

 
  UpdatePulseq();
  
  /* update geometry parameters                               */
  
  int dim=PTB_GetSpatDim();

  // only one package if black-blood module on
  int maxPackages = PVM_BlBloodOnOff == On? 1:0;

  // only one slice per package if 3D
  int maxPerPackage = dim>2? 1:0;

  STB_UpdateImageGeometry(dim, 
                          PVM_Matrix,
                          minFov,
                          0, // total slices (no restr)
                          maxPackages,
                          maxPerPackage,
                          minSliceThick,
                          1.0); // sliceFovRatio in 3D

  /* update slice spoiler */
  double mindurSlice = 1.5*CFG_GradientRiseTime();
  double spoilerThick = dim>2 ? PVM_SpatResol[2]*PVM_EncZf[2] : PVM_SliceThick;
  MRT_UpdateSpoiler("SliceSpoiler",2.0,ExcSliceGradLim,mindurSlice,PVM_GradCalConst,spoilerThick);

  /* handling of modules */
  STB_UpdateFatSupModule(PVM_Nucleus1, PVM_DeriveGains, spoilerThick);
  STB_UpdateMagTransModule(PVM_DeriveGains);
  STB_UpdateFovSatModule(PVM_Nucleus1, PVM_DeriveGains);
  STB_UpdateFlowSaturationModule(PVM_Nucleus1,PVM_DeriveGains);
  STB_UpdateTriggerModule();
  STB_UpdateTaggingModule(PVM_Fov,PVM_Matrix,PVM_SpatResol[0]*PVM_EncZf[0],PVM_DeriveGains);  
  STB_UpdateEvolutionModule();
  
  /* Black Blood Module   */
  {
    double slabthick = PVM_SPackArrSliceDistance[0] * (PVM_SPackArrNSlices[0]-1)
      + PVM_SliceThick;
    
    double fixedTime = SliceSpoiler.dur + CFG_AmplifierEnable() 
      + ExcPulse1.Length/2.0 + PVM_TaggingModuleTime;
    
    STB_UpdateBlBloodModule(&slabthick,PVM_SPackArrSliceOffset,1,fixedTime,PVM_SliceThick,PVM_DeriveGains);
  }
  
  UpdateMovie();
  UpdateRFSpoiling();

  /* Calculate read and slice gradients */
  UpdateReadSliceGradients();

  /* Sequence elements, TE, TR, total time: */
  UpdateSequenceTiming();

  /* Dummy Scans */
  int averages;
  if(PVM_MotionSupOnOff==On || AngioMode ==Yes)
    averages = 1;
  else
    averages = PVM_NAverages;

  STB_UpdateDummyScans(PVM_RepetitionTime,averages);
 
  /* calculate dephasing and phase-encoding gradients         */
  UpdatePhaseGradients();

  /* calculate frequency offsets                              */
  UpdateFrequencyOffsets();

  /* update mapshim parameter class */
  STB_UpdateMapShim(PVM_Nucleus1,"PVM_SliceGeoObj");
  STB_UpdateStartupShims();

  /* Set ACQP parameters */
  SetBaseLevelParam();

  /* Set RECO parameters */
  SetRecoParam();
  
  DB_MSG(("<--backbone"));
  return;
}

/*-------------------------------------------------------
 * local utility routines to simplify the backbone 
 *------------------------------------------------------*/


void UpdateSequenceTiming()
/* -------------------------------------------------------
   Adapt sequence elements to the current geometry 
   (in this method, only EncGradDur is concerned),
   update TE and TR.
   ReadGrad and ExSliceGrad must be already set.
   ------------------------------------------------------*/
{
  double minEnc2d, minEnc3d, minRephSlice, minDephRead, 
         extensionPossible, extensionAllowed, extension;
  int nSlices;

  /* Part of the exctiation pulse to be refocused: */
  EffPulseDur = ExcPulse1.Length * (ExcPulse1.Rpfac/100);

  /* Part of the echo to be refocused */
  EchoDelay = PVM_AcquisitionTime * PVM_EchoPosition / 100;

  /* Minimum durations of all phase-gradient pulses */

  minEnc2d     = PTB_GetSpatDim()>1? 
                 MRT_EncodingTime(PVM_SpatResol[1],
                                  PVM_GradCalConst*Phase2DGradLim/100)
                 : 0;
  minEnc3d     = PTB_GetSpatDim()>2? 
                 MRT_EncodingTime(PVM_SpatResol[2],
                                     PVM_GradCalConst*Phase3DGradLim/100) 
                 : 0;
  
  minRephSlice = MRT_DephaseTime(EffPulseDur, 
                                 CFG_GradientRiseTime(),
                                 ExcSliceGrad,
                                 ExcSliceRephGradLim);
  
  minDephRead  = MRT_DephaseTime(EchoDelay, 
                                 CFG_GradientRiseTime(),
                                 ReadGrad,
                                 ReadDephGradLim);

 
  /* In this sequence all phase-gradient pulses are
     simultaneous with duration EncGradDur. We set it first
     to the common (longest) minimum: */

  EncGradDur = MAX_OF( MAX_OF(minEnc2d ,  minEnc3d),
                       MAX_OF(minRephSlice ,minDephRead ) ); 

  /* EncGradDur should also contain one ramp, thus: */
 
  EncGradDur = RewGradDur = MAX_OF(EncGradDur, CFG_GradientRiseTime());

  DB_MSG(("minimum EncGradDur = %f", EncGradDur));

  /* Update TE with the mimimum EncGradDur */

  UpdateEchoTime();


  /* If there is some freedom, make EncGradDur longer
     (to avoid unnecessarily strong phase gradients), 
     but not longer than allowed by gradient resolution */

  extensionPossible = PVM_EchoTime - PVM_MinEchoTime; 
  extensionAllowed  = PTB_GetSpatDim()>1? MRT_MaxEncodingTime(PVM_Fov[1], PVM_GradCalConst)-EncGradDur :20;

  DB_MSG(("ext possible = %f, allowed = %f", extensionPossible, extensionAllowed));

  extension = MIN_OF(extensionPossible, extensionAllowed);
  extension = MAX_OF(extension, 0);

  DB_MSG(("extension = %f",extension));

  EncGradDur += extension;
  TeFillDelay = PVM_EchoTime - PVM_MinEchoTime - extension;

  

  /* Other sequence elements, not involved in TE, e.g. spoilers  */
  double mindurRead =  MAX_OF(RewGradDur+CFG_GradientRiseTime(),PVM_DigEndDelOpt);
  MRT_UpdateSpoiler("ReadSpoiler",2.0,Phase2DGradLim,mindurRead,PVM_GradCalConst,PVM_SpatResol[0]*PVM_EncZf[0]);

  /* Update modules dependent on TE, here: inversion recovery: */
  SliceSegDur = minLoopRepetitionTime(); /* depends on TE */
  nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices);
  double fixedTime = SliceSpoiler.dur + CFG_AmplifierEnable() 
      + ExcPulse1.Length/2.0 + PVM_TaggingModuleTime;
  STB_UpdateSelIrModule(PVM_SliceThick,PVM_SliceOffset,nSlices,&SliceSegDur,0,fixedTime,PVM_DeriveGains);
  if(PVM_SelIrOnOff==On)
    ParxRelsCopyPar("PVM_InversionTime","PVM_SelIrInvTime");
  if(PVM_BlBloodOnOff==On)
    ParxRelsCopyPar("PVM_InversionTime","PVM_BlBloodInvTime");
  if(PVM_BlBloodOnOff==Off&&PVM_SelIrOnOff==Off)
  {
    PVM_InversionTime = 0.0;
    ParxRelsHideInEditor("PVM_InversionTime");
  }

  /* Find min TR and update TR */
  UpdateRepetitionTime();
 
  /* delay after the slice loop, used only in IR mode to cotrol TR: */
  SliceSegEndDelay = PVM_SelIrOnOff==On? PVM_RepetitionTime - PVM_MinRepetitionTime : 0;

  /* Calculate total experiment time */

  UpdateTotalTime();
}




void UpdateRepetitionTime(void)
{
  int nSlices;

  DB_MSG(("-->UpdateRepetitionTime"));


  nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );

  if(AngioMode == No)
  {   
    if(PVM_SelIrOnOff == On)
    {
      PVM_MinRepetitionTime =  
	PVM_SelIrModuleTime +
	PVM_TaggingModuleTime +
	nSlices * SliceSegDur;
    }
    else
    {
      /* min TR in a movie: */
      PVM_MinRepetitionTime = nSlices * minLoopRepetitionTime();
      
      /* if there is no movie, TR also includes some modules: */
      if(PVM_NMovieFrames == 1)
      {
	PVM_MinRepetitionTime += 
	  PVM_BlBloodModuleTime +
	  PVM_SelIrModuleTime +
	  PVM_TaggingModuleTime;
      } 
    }  
  }
  else
    PVM_MinRepetitionTime = minLoopRepetitionTime();  

  PVM_RepetitionTime=MAX_OF(PVM_MinRepetitionTime,PVM_RepetitionTime);

  /*** adapt RewGradDur to desired TR ***/
  double riseT = CFG_GradientRiseTime();
  double extensionAllowed = EncGradDur - RewGradDur;
  double extensionPossible = ReadSpoiler.dur-riseT - RewGradDur;
  double extension = MAX_OF(MIN_OF(extensionPossible, extensionAllowed),0);
  /* 1.) if possible, extend RewGradDur to duration of read spoiler */
  if(extension > 0) 
  {
    RewGradDur += extension;
    extensionAllowed = EncGradDur - RewGradDur;
  }
  int slices = AngioMode==Yes? 1:nSlices;
  extensionPossible = (PVM_RepetitionTime - PVM_MinRepetitionTime)/slices;
  extension = MAX_OF(MIN_OF(extensionPossible, extensionAllowed),0);
  /* 2.) if possible, extend RewGradDur to EncGradDur  */
  if(extension > 0)
  {
    RewGradDur += extension;
    MRT_UpdateSpoiler("ReadSpoiler",2.0,Phase2DGradLim,RewGradDur+riseT,PVM_GradCalConst,PVM_SpatResol[0]*PVM_EncZf[0]);
    PVM_MinRepetitionTime += extension*slices;
  }
  
  DB_MSG(("<--UpdateRepetitionTime"));
  return;
}



/* calculates PVM_ScanTimeStr and TimeForMovieFrames */

void UpdateTotalTime(void)
{
  int dim = PTB_GetSpatDim();
  double TotalTime=0;

  if( dim >1 )
  {
    if(PVM_NMovieFrames > 1)
    {    
      /* TR is one movie frame, without prep modules: */
      TimeForMovieFrames = PVM_RepetitionTime * PVM_NMovieFrames + PVM_TaggingModuleTime;
      TotalTime = (PVM_BlBloodModuleTime + TimeForMovieFrames)  
	          * PVM_EncMatrix[1] * PVM_NAverages; 
    }
    else
    {
      if(AngioMode==No)
      {
	/* TR includes prep modules */
	TimeForMovieFrames = PVM_RepetitionTime - PVM_BlBloodModuleTime - PVM_TaggingModuleTime;
	TotalTime = PVM_RepetitionTime * PVM_EncMatrix[1] * PVM_NAverages;  
      }
      else
      {
	int nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
	TotalTime = (PVM_RepetitionTime * PVM_EncMatrix[1] +
                     PVM_BlBloodModuleTime+PVM_SelIrModuleTime+PVM_TaggingModuleTime)*nSlices*PVM_NAverages;	
      } 
    } 

  }                     

  if( dim >2 )
    TotalTime = TotalTime * PVM_EncMatrix[2];

  /* time for one repetition */
  OneRepTime = TotalTime/1000.0;

  TotalTime = TotalTime * PVM_EvolutionCycles + PVM_EvolutionModuleTime;
  TotalTime = TotalTime * PVM_NRepetitions;

  PVM_ScanTime = TotalTime;
  UT_ScanTimeStr(PVM_ScanTimeStr,TotalTime);
  ParxRelsShowInEditor("PVM_ScanTimeStr");
  ParxRelsMakeNonEditable("PVM_ScanTimeStr");

}

void UpdateGeometryMinima( double *minFov,
                           double *minSliceThick)
{
  int dim;
  

  DB_MSG(("-->UpdateGeometryMinima"));

  
  dim=PTB_GetSpatDim();
  
  minFov[0]     = PVM_EffSWh / 
                  (1e-2*ReadDephGradLim * PVM_GradCalConst);
  *minSliceThick = ExcPulse1.Bandwidth /
                  (1e-2*ExcSliceGradLim * PVM_GradCalConst);

  if(dim >= 2)
  {
    minFov[1] = minFov[0]/8;
  }

  if(dim >= 3)
  {
    
    minFov[2] = *minSliceThick;
  }

  DB_MSG(("<--UpdateGeometryMinima"));
}


void UpdateReadSliceGradients(void)
{
  DB_MSG(("-->UpdateReadSliceGradients"));

  ReadGrad = MRT_ReadGrad(PVM_EffSWh,
                          PVM_Fov[0],
                          PVM_GradCalConst);

  ExcSliceGrad = MRT_SliceGrad(ExcPulse1.Bandwidth,
                               PVM_SliceThick,
                               PVM_GradCalConst);

  DB_MSG(("<--UpdateReadSliceGradients"));
}

void UpdatePhaseGradients()
{
  
  DB_MSG(("-->UpdatePhaseGradients"));

  /* Calculation of phase-encoding, 
     dephasing and rephasing gradients.
     
     (ReadGrad, ExcSliceGrad, EchoDelay, EffPulseDur,
      and EncGradDur must be calculated before)       */
   
  double rise = CFG_GradientRiseTime();

  ReadDephGrad =     MRT_DephaseGrad(EncGradDur, EchoDelay,   rise, ReadGrad);
  
  ExcSliceRephGrad = MRT_DephaseGrad(EncGradDur, EffPulseDur, rise, ExcSliceGrad);

  Phase2DGrad = PTB_GetSpatDim() > 1 ? 
                MRT_PhaseGrad(EncGradDur, PVM_Matrix[1], PVM_Fov[1], PVM_GradCalConst) : 0.0;

  Phase3DGrad = PTB_GetSpatDim() == 3 ? 
                MRT_PhaseGrad(EncGradDur, PVM_Matrix[2], PVM_Fov[2], PVM_GradCalConst) : 0.0;

  Rew2DGrad = PTB_GetSpatDim() > 1 ? 
                MRT_PhaseGrad(RewGradDur, PVM_Matrix[1], PVM_Fov[1], PVM_GradCalConst) : 0.0;

  Rew3DGrad = PTB_GetSpatDim() == 3 ? 
                MRT_PhaseGrad(RewGradDur, PVM_Matrix[2], PVM_Fov[2], PVM_GradCalConst) : 0.0;

  DB_MSG(("<--UpdatePhaseGradients"));
  return;
}

void UpdateFrequencyOffsets( void )
{
  int spatDim;
  int i,nslices;

  spatDim = PTB_GetSpatDim();
  nslices = GTB_NumberOfSlices(PVM_NSPacks,PVM_SPackArrNSlices);

  MRT_FrequencyOffsetList(nslices,
                          PVM_EffReadOffset,
                          ReadGrad,
                          PVM_GradCalConst,
                          PVM_ReadOffsetHz );

  MRT_FrequencyOffsetList(nslices,
                          PVM_EffSliceOffset,
                          ExcSliceGrad,
                          PVM_GradCalConst,
                          PVM_SliceOffsetHz );

  if(spatDim == 3)
  {
    for(i=0;i<nslices;i++)
      PVM_EffPhase2Offset[i] = -PVM_EffSliceOffset[i];
  }


}


/*--------------------------------------------------------
 * Routine to update RF pulse parameters
 *-------------------------------------------------------*/

void UpdateRFPulses(void)
{

  /* Updates all parameters that belong to ExcPulse1 pulse structure
     (as initialized by STB_InitRFPulse see initMeth.c)
  */

  STB_UpdateRFPulse("ExcPulse1",1,PVM_DeriveGains,Conventional);


  if(PVM_DeriveGains==Yes)
  {
    ParxRelsHideInEditor("ExcPulse1Ampl");
  }
  else
  {
    ParxRelsShowInEditor("ExcPulse1Ampl");
  }

  ParxRelsShowInFile("ExcPulse1Ampl");

  DB_MSG(("<--UpdateRFPulses"));

  return;
}

/*--------------------------------------------------------
 * Routine to control the visibility of parameters
 *-------------------------------------------------------*/


void ControlGradientLimits(YesNo NotOblique)
{
  DB_MSG(("-->ControlGradientLimits: Obliqueness forbidden: %s",NotOblique==Yes ? "Yes":"No"));


  if(NotOblique==Yes)
  {
    ReadDephGradLim     = 
    Phase2DGradLim      = 
    Phase3DGradLim      =
    ExcSliceRephGradLim = 100.0;
  }
  else
  {
    /* Gradient limits in % of max. Value 57 (1/sqrt(3))
       is needed for arbitrary oblique slices. */
    ReadDephGradLim     = 
    Phase2DGradLim      = 
    Phase3DGradLim      =
    ExcSliceRephGradLim = 57.0;
  }

  ReadGradLim        = 100.0;
  ExcSliceGradLim    = 100.0;

  DB_MSG(("-->ControlGradientLimits"));
}

void UpdateMovie(void)
{
  if(AngioMode==Yes)
    PVM_NMovieFrames=1;

  if(PVM_NMovieFrames == 1)
  {
    ParxRelsHideInEditor("TimeForMovieFrames");
  }
  else
  {
    ParxRelsShowInEditor("TimeForMovieFrames");
  }
}




/* Calculates PVM_MinEchoTime and restrict PVM_EchoTIme.
   EffPulseDur, EncGradDur must be set before */
void UpdateEchoTime( void )
{

  double riseTime = CFG_GradientRiseTime(),
    rampTime = CFG_GradientRampTime()+CFG_InterGradientWaitTime();

  DB_MSG(("-->UpdateEchoTime\n"));
  
  PVM_MinEchoTime = 
    EffPulseDur    +
    rampTime       + //falling ramp of slice grad
    EncGradDur     + //enc. time (ramp+plateau
    rampTime       + //min te-filling (end ramp of encoding)             
    riseTime       + //read-on ramp          +
    EchoDelay;

  
  PVM_EchoTime = MAX_OF(PVM_EchoTime, PVM_MinEchoTime);

  DB_MSG(("<--echoTimeRels\n"));
}



double minLoopRepetitionTime(void)
/* ---------------------------------------------------------
this function returns the minimum duration of the innermost
pulse program loop
----------------------------------------------------------*/
{
  double minTr, minD0,
    riseTime = CFG_GradientRiseTime(),
    igwt = CFG_InterGradientWaitTime();
  
  minD0 = 0.01  /* ADC_END */ + igwt;

  minTr = 
    0.02                           + /*reload B0*/
    PVM_FatSupModuleTime           +
    PVM_MagTransModuleTime         +
    PVM_FovSatModuleTime           +
    PVM_InFlowSatModuleTime        +
    SliceSpoiler.dur               +
    riseTime                       +
    CFG_AmplifierEnable()          +
    ExcPulse1.Length - EffPulseDur +
    PVM_EchoTime - EchoDelay       +
    PVM_AcquisitionTime            +
    ReadSpoiler.dur                +
    riseTime                       +
    0.02                           +
    minD0;

  return minTr;
}

void UpdateRFSpoiling(void)
{
  DB_MSG(("-->UpdateRFSpoiling"));

  if(RFSpoiling==No)
  {
    PARX_change_dims("RFPhaseList",1);
    RFPhaseList[0] = 0;
  }
  else
  { 
    int max = PVM_EncMatrix[1]+PVM_DummyScans;
    int size = MAX_OF(256,max);
    PARX_change_dims("RFPhaseList",size);
    MRT_RFSpoilPhaseList(117,size,RFPhaseList,Yes);
  }

  DB_MSG(("<--UpdateRFSpoiling"));
}
