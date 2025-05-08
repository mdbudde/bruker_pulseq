/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/FLASH.c,v $
 *
 * Copyright (c) 1999-2005
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: FLASH.c,v 1.9 2009/04/28 13:13:56 fhen Exp $
 *
 ****************************************************************/

method pulseqV1
{

/****************************************************************/
/*	TYPE DEFINITIONS					*/
/****************************************************************/


#include "bruktyp.h"
#include "acqutyp.h"
#include "acqumtyp.h"
#include "recotyp.h" 
#include "subjtyp.h" 
#include "ta_config.h" 
#include "methodTypes.h"
#include "Visu/VisuTypes.h"




/****************************************************************/
/*	PARAMETER DEFINITIONS					*/
/****************************************************************/


/*--------------------------------------------------------------*
 * Include external definitions for parameters in the classes
 * ACQU ACQP GO GS RECO RECI PREEMP CONFIG
 *--------------------------------------------------------------*/
#include "proto/acq_extern.h"
#include "proto/subj_extern.h"

/*--------------------------------------------------------------*
 * Include references to the standard method parameters
 *--------------------------------------------------------------*/
#include "proto/pvm_extern.h"
#include "proto/visu_extern.h"

/*--------------------------------------------------------------*
 * Include references to any method specific parameters
 *--------------------------------------------------------------*/

#include "methodFormat.h"
#include "parsTypes.h"
#include "parsDefinition.h"

/****************************************************************/
/*	RE-DEFINITION OF RELATIONS				*/
/****************************************************************/

#include "callbackDefs.h"

/****************************************************************/
/*	PARAMETER CLASSES					*/
/****************************************************************/
#include "methodClassDefs.h"

#include "modulesClassDefs.h"
#include "parsLayout.h"

};

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/

