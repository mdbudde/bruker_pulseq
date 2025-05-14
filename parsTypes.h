/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/parsTypes.h,v $
 *
 * Copyright (c) 1999 - 2003
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Locker:  $
 * $State: Exp $
 * $Revision: 1.3 $
 *
 *
 ****************************************************************/

/****************************************************************/
/*	TYPEDEF's						*/
/****************************************************************/

typedef enum
  {
    Long_TE,
    Short_TE
  } TE_MODE;

typedef enum
  {
    Default,
    SWI
  } RecoMeth_MODE;

typedef enum
  {
    positive_mask,
    negative_mask,
    magnitude_mask,
    phase_image
  } MASK_MODE;

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/
