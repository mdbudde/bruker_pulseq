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
  PVM_AcquisitionTime;
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
  PVM_TriggerModule;
  Trigger_Parameters;

} Preparation;


parclass
{
  Method;
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

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/



