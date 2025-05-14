/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/parsDefinition.h,v $
 *
 * Copyright (c) 1999-2003
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsDefinition.h,v 1.30 2012/11/27 12:48:01 anba Exp $
 *
 ****************************************************************/



/****************************************************************/
/* INCLUDE FILES						*/
/****************************************************************/
#include "pulseqPars.h"


double parameter OneRepTime;


PV_PULSE_LIST parameter
{
  display_name "Excitation Pulse Shape";
  relations    ExcPulse1EnumRelation;
}ExcPulse1Enum;


PVM_RF_PULSE parameter
{
  display_name "Excitation Pulse";
  relations    ExcPulse1Relation;
}ExcPulse1;

PVM_RF_PULSE_AMP_TYPE parameter
{
  display_name "RF Pulse Amplitude";
  relations ExcPulse1AmplRel;
}ExcPulse1Ampl;

double parameter
{
  relations backbone;
}ExcPulse1Shape[];



/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/

