/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/FLASH/loadMeth.c,v $
 *
 * Copyright (c) 2002-2010
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: loadMeth.c,v 1.10 2011/05/04 10:54:35 wemch Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: loadMeth.c,v 1.10 2011/05/04 10:54:35 wemch Exp $ (C) 2002-2010 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	0
#define DB_LINE_NR	0


#include "method.h"

/*:=MPB=:=======================================================*
 *
 * Global Function: loadMeth
 *
 * Description: This procedure is automatically called in
 *	response to a method file for this method being read.
 *
 * Error History: 
 *
 * Interface:							*/

void loadMeth(const char *	className)
/*:=MPE=:=======================================================*/
{
  DB_MSG(( "-->FLASH:loadMeth( %s )\n", className ));



  if (0 != className)
  {
      if (0 == strcmp( className, "MethodClass"))
      {
          initMeth();
      }
      else if (0 == strcmp(className, "MethodRecoGroup"))
      {
          DB_MSG(("...responding to loadMeth call for MethodRecoGroup."));
          SetRecoParam();
      }
  }
  else
  {
    DB_MSG(( "...ignoring loadMeth call - I don't know this class" ));
  }

  DB_MSG(( "<--FLASH:loadMeth( %s )\n", className ));

}

/****************************************************************/
/*		E N D   O F   F I L E				*/
/****************************************************************/


