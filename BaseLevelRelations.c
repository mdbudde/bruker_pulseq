/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/BaseLevelRelations.c,v $
 *
 * Copyright (c) 2001-2009
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: BaseLevelRelations.c,v 1.62 2013/04/11 13:09:13 cmei Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: BaseLevelRelations.c,v 1.62 2013/04/11 13:09:13 cmei Exp $ (C) 2001-2009 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	0
#define DB_LINE_NR	0


#include "method.h"



void SetBaseLevelParam( void )
{

  DB_MSG(("-->SetBaseLevelParam\n"));


  SetBasicParameters();
 
  SetFrequencyParameters();
    
  SetPpgParameters();
    
  SetGradientParameters();
    
  SetMachineParameters();
   
  DB_MSG(("<--SetBaseLevelParam\n"));
  
}


/* Toolboxes referenced in this file: ATB, GTB, PTB, STB, UT */


void SetBasicParameters( void )
{
  int spatDim, specDim;
  int nSlices;
  int dim;

  DB_MSG(("-->SetBasicParameters\n"));
    
  /* ACQ_dim */

  spatDim = PTB_GetSpatDim();
  
 
  specDim = PTB_GetSpecDim();
  
  ACQ_dim = spatDim + specDim;
  ParxRelsParRelations("ACQ_dim",Yes);
  
  /* ACQ_dim_desc */
  
  ATB_SetAcqDimDesc( specDim, spatDim, NULL );
  
  /* ACQ_size */
 
  ATB_SetAcqSize( Spatial, spatDim, PVM_EncMatrix, NULL, No );
  
  /* NSLICES */
  
  nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );

  
  ATB_SetNSlices( nSlices );
 
  /* NR */
  
  ATB_SetNR( 1 );

 
  /* NI */
 
  ATB_SetNI( nSlices );
 

  /* AVERAGING */


  ATB_SetNA( 1 );
  ATB_SetNAE( 1 );

   
  /* ACQ_ns */
  
  ACQ_ns_list_size = 1;
  
  dim = PARX_get_dim("ACQ_ns_list",1);

  if( dim != 1 )
  {
    PARX_change_dims( "ACQ_ns_list",1 );
  }
  
  NS = 1;
  ACQ_ns = NS;
  ACQ_ns_list[0] = ACQ_ns;
  
  ParxRelsParRelations("ACQ_ns",Yes);
  
  
  /* NECHOES */
  
  NECHOES = 1;
  
  
  
  /* ACQ_obj_order */
  
  PARX_change_dims("ACQ_obj_order",NI);
 
  ATB_SetAcqObjOrder( nSlices, PVM_ObjOrderList, 1, 1 );
  
  /* DS */
  DS = PVM_DummyScans;
  ACQ_DS_enabled = Yes;
  
  
  /* ACQ_user_filter for Frequency Drift Correction*/
  ATB_DisableAcqUserFilter();

  ATB_SetAcqScanSize( One_scan );
 
  
  DB_MSG(("<--SetBasicParameters\n"));
}

void SetFrequencyParameters( void )
{
  int nslices;

  DB_MSG(("-->SetFrequencyParameters\n"));
  
  ATB_SetNuc1(PVM_Nucleus1);
  
  sprintf(NUC2,"off");
  sprintf(NUC3,"off");
  sprintf(NUC4,"off");
  sprintf(NUC5,"off");
  sprintf(NUC6,"off");
  sprintf(NUC7,"off");
  sprintf(NUC8,"off");
  
  ATB_SetNucleus(PVM_Nucleus1);
    
  
  
  /* setting of SW_h DIGMOD, DSPFIRM and AQ_mod */

  ATB_SetDigPars(); 
  
  ACQ_O1_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O1_mode",Yes);
  
  ACQ_O2_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O2_mode",Yes);
  
  ACQ_O3_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O3_mode",Yes);
  
  O1 = 0.0;
  O2 = 0.0;
  O3 = 0.0;
  O4 = 0.0;
  O5 = 0.0;
  O6 = 0.0;
  O7 = 0.0;
  O8 = 0.0;

  /* Set BF's to working freuncies on used channels */
  ACQ_BF_enable = No;
  BF1 = PVM_FrqWork[0];
  BF2 = PVM_FrqWork[1];
  /* call relations of BF1 (no need for other BF's) */
  ParxRelsParRelations("BF1", Yes); 

  
  nslices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  
  ATB_SetAcqO1List( nslices,
                    PVM_ObjOrderList,
                    PVM_SliceOffsetHz );

  
  ATB_SetAcqO1BList( nslices,
                     PVM_ObjOrderList,
                     PVM_ReadOffsetHz); 
    
  DB_MSG(("<--SetFrequencyParameters\n"));
}

void SetGradientParameters( void )
{
  int spatDim;
  
  DB_MSG(("-->SetGradientParameters\n"));
  
  
  ATB_SetAcqPhaseFactor( 1 );

 
  spatDim = PTB_GetSpatDim();
  
  PARX_change_dims("ACQ_phase_encoding_mode", spatDim );
  PARX_change_dims("ACQ_phase_enc_start", spatDim );
  switch(spatDim)
  {
    case 3:
      ACQ_phase_encoding_mode[2] = User_Defined_Encoding;
      ACQ_phase_enc_start[2] = -1; /* set, but no used */
      ACQ_spatial_size_2 = PVM_EncMatrix[2];
      ParxRelsCopyPar("ACQ_spatial_phase_2","PVM_EncValues2");
      /* no break */
    case 2:
      ACQ_phase_encoding_mode[1] = User_Defined_Encoding;;
      ACQ_phase_enc_start[1] = -1.0; /* set, but no used */
      ACQ_spatial_size_1 = PVM_EncMatrix[1];
      ParxRelsCopyPar("ACQ_spatial_phase_1","PVM_EncValues1");
      /* no break */
    default:
      ACQ_phase_encoding_mode[0] = Read;
      ACQ_phase_enc_start[0] = -1;
  }
  ParxRelsParRelations("ACQ_phase_encoding_mode",Yes);

  ATB_SetAcqGradMatrix( PVM_NSPacks, PVM_SPackArrNSlices,
			PtrType3x3 PVM_SPackArrGradOrient[0],
			PVM_ObjOrderList );
    
  
  ACQ_scaling_read  = 1.0;
  ACQ_scaling_phase = 1.0;
  ACQ_scaling_slice = 1.0;
  
  ACQ_rare_factor = 1;
  ACQ_phase_factor =1;

  ACQ_grad_str_X = 0.0;
  ACQ_grad_str_Y = 0.0;
  ACQ_grad_str_Z = 0.0;
  
  
  strcpy(GRDPROG, "");
  

  /* gradient amplitudes */
  /* ACQ_gradient_amplitude[0] =  ExcSliceGrad;
  ACQ_gradient_amplitude[1] = -ExcSliceRephGrad;
  ACQ_gradient_amplitude[2] = -ReadDephGrad;
  ACQ_gradient_amplitude[3] =  Phase2DGrad;
  ACQ_gradient_amplitude[4] = -Phase3DGrad;
  ACQ_gradient_amplitude[5] =  ReadGrad;
  ACQ_gradient_amplitude[6] =  ReadSpoiler.ampl;
  ACQ_gradient_amplitude[7] = -Rew2DGrad;
  ACQ_gradient_amplitude[8] =  Rew3DGrad;
  ACQ_gradient_amplitude[9] =  SliceSpoiler.ampl;
   * */
    
  
  
  DB_MSG(("<--SetGradientParameters\n"));
}


void SetMachineParameters( void )
{
  DB_MSG(("-->SetMachineParameters\n"));
 
  if( ParxRelsParHasValue("ACQ_word_size") == No )
  {
    ACQ_word_size = _32_BIT;
  }
  

  /* DEOSC = (PVM_AcquisitionTime + ReadSpoiler.dur)*1000.0; */
  DEOSC = (PVM_AcquisitionTime)*1000.0;

  ACQ_scan_shift = -1;
  ParxRelsParRelations("ACQ_scan_shift",Yes);
  
  DE = DE < 6.0 ? 6.0: DE;
  
  
  PAPS = QP;
  

  /* ACQ_experiment _mode and ACQ_ReceiverSelect: */

  ATB_SetMultiRec();
 
  DB_MSG(("<--SetMachineParameters\n"));
}

void SetPpgParameters( void )
{
  double rampTime, riseTime;

  DB_MSG(("-->SetPpgParameters\n"));

  ACQ_vd_list_size=1;
  PARX_change_dims("ACQ_vd_list",1);
  ACQ_vd_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vd_list",Yes);
  
  ACQ_vp_list_size=1;
  PARX_change_dims("ACQ_vp_list",1);
  ACQ_vp_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vp_list",Yes);

  ATB_SetPulprog("pulseq_scan.ppg");

  double igwt = CFG_InterGradientWaitTime();
  riseTime = CFG_GradientRiseTime();
  rampTime = CFG_GradientRampTime() + igwt;

  /* int slices = NSLICES; */
  /* D[0]  = (PVM_RepetitionTime - PVM_MinRepetitionTime)/(slices * 1000.0)
             + igwt / 1000.0 + 0.01 / 1000.0;
  D[20] = 0.00001;
  
  D[2]  = (TeFillDelay + rampTime) / 1000.0;
  D[4]  = rampTime / 1000.0;
  D[3]  = riseTime / 1000.0;
  D[10] = EncGradDur / 1000.0;
  D[11] = RewGradDur / 1000.0;
  D[12] = (ReadSpoiler.dur - RewGradDur)/1000.0;
  D[6]  = SliceSpoiler.dur/1000.0;
  D[8]  = CFG_AmplifierEnable()/1000.0; 
   * */
 
  /* set shaped pulses, in this method ACQ_RfShapes[0] is used           
     the pulse duration is stored in baselevel parameter P[0]
  */
  ATB_SetRFPulse("ExcPulse1","ACQ_RfShapes[0]","P[0]");

 
  L[1] = ACQ_dim>1 ? ACQ_size[1]:1;
  L[2] = ACQ_dim>2 ? ACQ_size[2]:1;
  L[5] = 0; 

  ParxRelsParRelations("L",Yes);
 
  DB_MSG(("<--SetPpgParameters\n"));
}


