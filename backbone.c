
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
    

  /* set limits for read, phase and slice gradients            */

  //ControlGradientLimits(PVM_MajSliceOri);
  

  /* calculate minima for FOV and slice thickness             */

  minFov[0] = 10;
  minFov[1] = 10;
  //UpdateGeometryMinima(minFov,
  //                     &minSliceThick);

 
  UpdatePulseq();
  
  /* update geometry parameters                               */
  
  int dim=PTB_GetSpatDim();

  // only one package if black-blood module on
  int maxPackages = PVM_BlBloodOnOff == On? 1:0;

  // only one slice per package if 3D
  int maxPerPackage = dim>2? 1:0;
  
  minSliceThick = 1;

  STB_UpdateImageGeometry(dim, 
                          PVM_Matrix,
                          minFov,
                          0, // total slices (no restr)
                          maxPackages,
                          maxPerPackage,
                          minSliceThick,
                          1.0); // sliceFovRatio in 3D

  STB_UpdateTriggerModule();
 
  UpdateTotalTime();

  /* calculate frequency offsets                              */
  //UpdateFrequencyOffsets();

  /* update mapshim parameter class */
  STB_UpdateMapShim(PVM_Nucleus1,"PVM_SliceGeoObj");
  STB_UpdateStartupShims();

  /* Set ACQP parameters */
  SetBaseLevelParam();

  DB_MSG(("<--backbone"));
  return;
}

/*-------------------------------------------------------
 * local utility routines to simplify the backbone 
 *------------------------------------------------------*/



/* calculates PVM_ScanTimeStr and TimeForMovieFrames */

void UpdateTotalTime(void)
{
  int dim = PTB_GetSpatDim();
  double TotalTime=0;

  TotalTime = 12345.;
  
  PVM_ScanTime = TotalTime;
  UT_ScanTimeStr(PVM_ScanTimeStr,TotalTime);
  ParxRelsShowInEditor("PVM_ScanTimeStr");
  ParxRelsMakeNonEditable("PVM_ScanTimeStr");
}

/* 
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
*/

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

/* 
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
    * Gradient limits in % of max. Value 57 (1/sqrt(3))
       is needed for arbitrary oblique slices. *
    ReadDephGradLim     = 
    Phase2DGradLim      = 
    Phase3DGradLim      =
    ExcSliceRephGradLim = 57.0;
  }

  ReadGradLim        = 100.0;
  ExcSliceGradLim    = 100.0;

  DB_MSG(("-->ControlGradientLimits"));
}
*/
