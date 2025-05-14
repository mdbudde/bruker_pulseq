/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/callbackDefs.h,v $
 *
 * Copyright (c) 1999-2002
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: callbackDefs.h,v 1.37.2.1 2015/03/23 07:44:52 mawi Exp $
 *
 ****************************************************************/

/* react on changes of system configuration                  */
relations PVM_SysConfigHandler backbone;

/* Encoding */
relations PVM_EncodingHandler backbone;

/* geometry */
relations PVM_ImageGeometryHandler  backbone;

/* digitizer parameters and bandwidth */
relations PVM_DigHandler       backbone;
relations PVM_EffSWh           EffSWhRel;

/* modules */
relations PVM_TriggerHandler    backbone;

/* other parameters */
relations PVM_NucleiHandler     backbone;
relations PVM_DeriveGains       backbone;
relations PVM_AutoRgInitHandler MyRgInitRel;

/* react on parameter adjustments */
relations PVM_AdjResultHandler backbone;

/* changes before acquisition */
relations PVM_AcqScanHandler    SetBeforeAcquisition;

/* Redirect relation for visu creation */
relations VisuDerivePars        deriveVisu;

/* redirection of method specific reconstruction method */
relations RecoUserUpdate        RecoDerive;

/* relations for mapshim parameter group*/
relations PVM_MapShimHandler backbone;
relations  PVM_StartupShimHandler backbone;

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/







