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


  ATB_SetRecoTranspositionFromLoops(
    PtrType3x3 ACQ_grad_matrix[0],
    NSLICES,
    1,
    NI,
    ACQ_obj_order);

  /* special settings */

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

  DB_MSG(("<--RecoDerive\n"));
}

