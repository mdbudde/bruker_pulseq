/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/parsLayout.h,v $
 *
 * Copyright (c) 1999-2007
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsLayout.h,v 1.42.2.1 2015/03/23 07:47:39 mawi Exp $
 *
 ****************************************************************/

/****************************************************************/
/*	PARAMETER CLASSES				       	*/
/****************************************************************/



/*--------------------------------------------------------------*
 * Definition of the PV class...
 *--------------------------------------------------------------*/

parclass
{
  PVM_EffSWh;
  PVM_EchoPosition;
  EncGradDur;
  PVM_AcquisitionTime;
  ReadSpoiler;
  SliceSpoiler;
  DigitizerPars;
}
attributes
{
  display_name "Sequence Details";
} Sequence_Details;

parclass
{
  ExcPulse1Enum;
  ExcPulse1;
  ExcPulse1Ampl;
} 
attributes
{
  display_name "RF Pulses";
} RF_Pulses;

parclass
{
  DummyScans_Parameters;
  PVM_FreqDriftYN;
  
  PVM_NMovieFrames;
  TimeForMovieFrames;

  PVM_EvolutionOnOff;
  Evolution_Parameters;

  PVM_TriggerModule;
  Trigger_Parameters;

  PVM_TaggingOnOff;
  Tagging_Parameters;

  PVM_SelIrOnOff;
  Selective_IR_Parameters;

  PVM_BlBloodOnOff;
  BlackBlood_Parameters;

  PVM_FatSupOnOff;
  Fat_Sup_Parameters;

  PVM_MagTransOnOff;
  Magn_Transfer_Parameters;

  PVM_FovSatOnOff;
  Fov_Sat_Parameters;

  PVM_InFlowSatOnOff;
  Flow_Sat_Parameters;

  PVM_MotionSupOnOff;

  RFSpoiling;
  AngioMode;

} Preparation;


parclass
{
  Method;
  PVM_EchoTime;
  PVM_RepetitionTime;
  PVM_NEchoImages;
  PVM_NAverages;
  PVM_NRepetitions;
  PVM_ScanTimeStr;
  PVM_ScanTime;
  PVM_DeriveGains;
  RF_Pulses;
  Nuclei;
  Encoding;
  Sequence_Details;
  ImageGeometry;
  Preparation;
  MapShim;  
  StartupShims;

} MethodClass;

// parameters that should be tested after any editing
conflicts
{
  PVM_EchoTime;
  PVM_RepetitionTime;
  PVM_Fov;
  PVM_SliceThick;
};

// parameters for reconstruction 
parclass
{
  RecoMethMode;
  WeightingMode;
  MaskWeighting;
  GaussBroadening;
}attributes
{
  display_name "Reconstruction Options";
}MethodRecoGroup;

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/



