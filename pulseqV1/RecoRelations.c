/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/RecoRelations.c,v $
 *
 * Copyright (c) 2002
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: RecoRelations.c,v 1.46.2.1 2014/08/19 14:12:13 sako Exp $
 *
 ****************************************************************/


static const char resid[] = "$Id: RecoRelations.c,v 1.46.2.1 2014/08/19 14:12:13 sako Exp $ (C) 2002 Bruker BioSpin MRI GmbH";

#define DEBUG           0
#define DB_MODULE       1
#define DB_LINE_NR      1



#include "method.h"

void SetRecoParam( void )
{
  DB_MSG(("-->SetRecoParam\n"));

  /* set baselevel reconstruction parameter */

  int dim = PTB_GetSpatDim();
  int echoImages = PVM_NEchoImages * PVM_NMovieFrames;

  ATB_InitUserModeReco(
    dim,
    0,
    PVM_EncMatrix,
    PVM_Matrix,
    PVM_AntiAlias,
    PVM_EncPftOverscans,
    NI,
    ACQ_obj_order,
    ACQ_phase_factor,
    PVM_EncSteps1,
    PVM_EncSteps2,
    NULL,
    PVM_EncNReceivers,
    PVM_EncChanScaling,
    dim>1? PVM_EncPpiRefLines[1]:0,
    dim>1? PVM_EncPpi[1]:0);

  ATB_SetRecoRotate(
    NULL,
    PVM_Fov[0] * PVM_AntiAlias[0],
    NSLICES,
    echoImages,
    0);

  if(dim>1)
  {
    ATB_SetRecoRotate(
      PVM_EffPhase1Offset,
      PVM_Fov[1] * PVM_AntiAlias[1],
      NSLICES,
      echoImages,
      1);
  }

  if (dim == 3)
  {
    ATB_SetRecoRotate(
      PVM_EffPhase2Offset,
      PVM_Fov[2] * PVM_AntiAlias[2],
      NSLICES,
      echoImages,
      2);
  }


  if(RecoMethMode != SWI)
  {
    for (int i = 0; i < dim; i++)
    {
      ATB_SetRecoPhaseCorr(50.0, 0.0, i);
    }
  }

  ATB_SetRecoTranspositionFromLoops(
    PtrType3x3 ACQ_grad_matrix[0],
    NSLICES,
    1,
    NI,
    ACQ_obj_order);

  /* special settings */

  RecoMethModeVisPar();
  
  if (RecoMethMode == SWI && WeightingMode == phase_image)
  {
    RecoCombineMode = AddImages;
    RECO_image_type = PHASE_IMAGE;
    ParxRelsParRelations("RECO_image_type", Yes);
  }

  DB_MSG(("<--SetRecoParam\n"));
}

void RecoDerive (void)
{
  DB_MSG(("-->RecoDerive\n"));

  if (RecoUserUpdate == No)
  {
    DB_MSG(("<--RecoDerive: no update\n"));
    return;
  }

  /* standard settings for reconstruction */  
  if(RecoPrototype == No)
    SetRecoParam();
  
  /* create standard reconstruction network */
  ParxRelsParRelations("RecoUserUpdate", Yes);

  /* modify for SWI */
  if (RecoMethMode == SWI && ACQ_scan_type != Setup_Experiment)
  {
    SWIRecoRel();
  }

  DB_MSG(("<--RecoDerive\n"));
}

void SWIRecoRel (void)
{
  DB_MSG(("-->SWIRecoRel"));

  char arg0[RECOSTAGENODESIZE], arg1[RECOSTAGENODESIZE], arg2[RECOSTAGENODESIZE], argSWI[RECOSTAGENODESIZE];
  double delta[3]={0.0,0.0,0.0}, tau[3]={0.0,0.0,0.0}, gamma[3]={0.0,0.0,0.0};
  int dim = PTB_GetSpatDim();

  /* parameters for RecoGaussWinMultFilter: exp(-delta*t - tau*t^2 -gamma)
     tau = (N*pi*broadening/(2*FOV))^2
     delta = -2*tau*t0
     gamma = tau * t0^2 */

  tau[0] = pow((PVM_Matrix[0]*M_PI*GaussBroadening/(2*PVM_Fov[0])),2);  
  delta[0] = -2.0*tau[0]*0.5;
  gamma[0] = tau[0]*pow(0.5, 2);

  for(int i=1;i<dim;i++)
  {
    tau[i] = pow((PVM_Matrix[i]*M_PI*GaussBroadening/(2*PVM_Fov[i])),2);
    delta[i] = -tau[i]; 
    gamma[i] = 0.25*tau[i];
  }
 
  snprintf(arg0,RECOSTAGENODESIZE,"winDirection=0;delta=%f;tau=%f;gamma=%f",delta[0],tau[0],gamma[0]);
  snprintf(arg1,RECOSTAGENODESIZE,"winDirection=1;delta=%f;tau=%f;gamma=%f",delta[1],tau[1],gamma[1]);
  snprintf(arg2,RECOSTAGENODESIZE,"winDirection=2;delta=%f;tau=%f;gamma=%f",delta[2],tau[2],gamma[2]);

  switch (WeightingMode)
  {
    case positive_mask:  snprintf(argSWI,RECOSTAGENODESIZE,"mask=1;weighting=%f",MaskWeighting); break;
    case negative_mask:  snprintf(argSWI,RECOSTAGENODESIZE,"mask=2;weighting=%f",MaskWeighting); break;
    case magnitude_mask: snprintf(argSWI,RECOSTAGENODESIZE,"mask=3;weighting=%f",MaskWeighting); break;
    case phase_image:    snprintf(argSWI,RECOSTAGENODESIZE,"mask=4;weighting=%f",MaskWeighting); break;
  }

  /* apply gauss filtering and phase weighting to data */

  const int nrReceivers = RecoNrActiveReceivers();

  for (int n = 0; n < nrReceivers; n++)
  {
    if (nrReceivers > 1)
    {
      char position[RECOSTAGENODESIZE], stage[RECOSTAGENODESIZE];
      snprintf(position,RECOSTAGENODESIZE, "SOS0.%d", n);
      snprintf(stage,RECOSTAGENODESIZE, "TEE%d", n);
      RecoComputeInsertStage(RECOPREPPASS,-1,position,"RecoTeeFilter",stage,"");
    }
    else
    {
      RecoComputeInsertStage(RECOPREPPASS,n,DEFAULTIMAGETYPEFILTERNAME,"RecoTeeFilter","TEE","");
    }
    RecoComputeAppendStage(RECOPREPPASS,n,"TEE","RecoPhaseWeightingFilter","SWI",argSWI);
    RecoComputeConnectStages(RECOPREPPASS,n,"TEE","SWI.mask");
    RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOFTFILTER,"IFT0","direction=0;exponent=-1");
    RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOFTFILTER,"IFT1","direction=1;exponent=-1");
    if (dim == 3)
    {
      RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOFTFILTER,"IFT2","direction=2;exponent=-1");
    }
    RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOGAUSSWINMULTFILTER,"GAUSS0",arg0);
    RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOGAUSSWINMULTFILTER,"GAUSS1",arg1);
    if (dim == 3)
    {
      RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOGAUSSWINMULTFILTER,"GAUSS2",arg2);
    }
    RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOFTFILTER,"FT0","direction=0;exponent=1");
    RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOFTFILTER,"FT1","direction=1;exponent=1");
    if (dim == 3)
    {
      RecoComputeInsertStage(RECOPREPPASS,n,"SWI.mask",RECOFTFILTER,"FT2","direction=2;exponent=1");
    }

  }

  DB_MSG(("<--SWIRecoRel"));
}

