/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/h/PvPvmTools.h,v $
 *
 * Copyright (c) 1995-2012
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: PvPvmTools.h,v 1.43 2013/01/11 15:17:47 mawi Exp $
 *
 ****************************************************************/

#ifndef PVPVMTOOLS_H
#define PVPVMTOOLS_H

#ifndef CPROTO

#include "PvCfg/PvCfg.h"
#include "adjManagerTypes.h"
/* gen/src/prg/pvm_toolboxes/PvPvmTools/dimensions.c */

/** Initializes or reinitializes @c PVM_SpatDimEnum. 

  This is according to the recipe described for @ref PTB_InitSpatDim. 

  @PVM_PARS
  The following arrays are redimensioned to current number of dimensions:
  - @c PVM_Fov
  - @c PVM_FovCm
  - @c PVM_MinFov
  - @c PVM_AntiAlias
  - @c PVM_MaxAntiAlias
  - @c PVM_SpatResol
  - @c PVM_Matrix
  - @c PVM_MinMatrix
  - @c PVM_MaxMatrix
 
  @PVM_TBCALL
  - @ref PTB_InitSpatDim

  @PVM_RELCALL
  NONE
  
  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_SetImagingDims(2, 3);
  @endcode

  @param lowestDim     Lowest dimension to which a dimension can be set
  @param highestDim    Highest dimension to which a dimension can be set

  @return Current number of dimensions

  @see @ref PTB_InitSpatDim, @ref PTB_SetSpatDim, @ref PTB_GetSpatDim,
       @ref PTB_SetSpectrocopyDims, @ref PTB_InitSpecDim, @ref PTB_SetSpecDim, @ref PTB_GetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE @n
        Check which of the related Set/Init functions are actually required.

  @ingroup PVM_PTB
*/
int PTB_SetImagingDims(int lowestDim,
                       int highestDim);

/** Initializes or reinitializes @c PVM_SpecDimEnum according to the recipe described for
    @ref PTB_InitSpecDim.

  @PVM_PARS
  - @c PVM_SpecDimEnum
  
  @PVM_TBCALL
  - @ref PTB_InitSpecDim

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_SetSpectrocopyDims(1, 2);
  @endcode

  @param lowestDim     Lowest dimension to which a dimension can be set
  @param highestDim    Highest dimension to which a dimension can be set

  @return Current number of dimensions

  @see @ref PTB_SetImagingDims, @ref PTB_InitSpatDim, @ref PTB_SetSpatDim, @ref PTB_GetSpatDim,
        @ref PTB_InitSpecDim, @ref PTB_SetSpecDim, @ref PTB_GetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE @n
        Check which of the related Set/Init functions are actually required.	
    
  @ingroup PVM_PTB
*/
int PTB_SetSpectrocopyDims(int lowestDim,
                           int highestDim);

/** Initializes or reinitializes @c PVM_SpatDimEnum for dimensions lying between @a lowestDim
    and @a highestDim. 

  If @a lowestDim is equal to @a highestDim @c PVM_SpatDimEnum is made non-editable. If
  @c PVM_SpatDimEnum has the state <c> NO VALUE </c> it is set to the lowest applicable
  dimension, otherwise its value is confined to lie within the initialized range.
    
  Note that @a lowestDim and @a highestDim are constrained to lie within the range @c 0 to @c 3.
 
  @PVM_PARS
  - @c PVM_SpatDimEnum
  
  @PVM_TBCALL
  - @ref PTB_GetSpatDim
  - @ref PTB_SetSpatDim

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_InitSpatDim(2, 3);
  @endcode

  @param lowestDim     Lowest dimension to which a dimension can be set
  @param highestDim    Highest dimension to which a dimension can be set

  @return Current number of dimensions

  @see @ref PTB_SetImagingDims, @ref PTB_SetSpatDim, @ref PTB_GetSpatDim,
       @ref PTB_SetSpectrocopyDims, @ref PTB_InitSpecDim, @ref PTB_SetSpecDim, @ref PTB_GetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE 
       
  @ingroup PVM_PTB 
*/
int PTB_InitSpatDim(int lowestDim,
                    int highestDim);

/** Sets the parameter @c PVM_SpatDimEnum to @c dimValue. 

  If @c dimValue lies outside the legal range it will be set according to the recipe described
  for the function @ref UT_SetInLimits.

  @PVM_PARS
  - @c PVM_SpatDimEnum
  
  @PVM_TBCALL
  - @ref PTB_GetSpatDim

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  Legal dimension range must have been set with @ref PTB_InitSpatDim.
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_SetSpatDim(2);
  @endcode

  @param dimensions    Number of dimensions

  @return Dimension number that was set

  @see @ref PTB_SetImagingDims, @ref PTB_InitSpatDim, @ref PTB_GetSpatDim,
       @ref PTB_SetSpectrocopyDims, @ref PTB_InitSpecDim, @ref PTB_SetSpecDim, @ref PTB_GetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE 
       
  @ingroup PVM_PTB 
*/
int PTB_SetSpatDim(int dimensions);

/** Retrieves the current value of @c PVM_SpatDimEnum as an int.

  @PVM_PARS
  NONE 
  
  @PVM_RELCALL
  NONE 
  
  @PVM_TBCALL
  NONE 

  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  int dim = PTB_GetSpatDim();
  @endcode
  
  @return Number of dimensions

  @see @ref PTB_SetImagingDims, @ref PTB_InitSpatDim, @ref PTB_SetSpatDim,
       @ref PTB_SetSpectrocopyDims, @ref PTB_InitSpecDim, @ref PTB_SetSpecDim, @ref PTB_GetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE
       
  @ingroup PVM_PTB 
*/
int PTB_GetSpatDim(void);

/** Initializes or reinitializes @c PVM_SpecDimEnum for dimensions lying between @a lowestDim
    and @a highestDim. 

  If @a lowestDim is equal to @a highestDim @c PVM_SpecDimEnum is made non-editable. If
  @c PVM_SpecDimEnum has the state <c> NO VALUE </c> it is set to the lowest applicable
  dimension, otherwise its value is confined to lie within the initialized range.
    
  Note that @a lowestDim and @a highestDim are constrained to lie within the range @c 0 to @c 9.

  @PVM_PARS
  - @c PVM_SpecDimEnum
  
  @PVM_RELCALL
  NONE

  @PVM_TBCALL
  - @ref PTB_GetSpecDim
  - @ref PTB_SetSpecDim

  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_InitSpecDim(1, 2);
  @endcode
  
  @param lowestDim     Lowest dimension to which a dimension can be set
  @param highestDim    Highest dimension to which a dimension can be set

  @return Current number of dimensions

  @see @ref PTB_SetImagingDims, @ref PTB_InitSpatDim, @ref PTB_SetSpatDim, @ref PTB_GetSpatDim,
       @ref PTB_SetSpectrocopyDims, @ref PTB_SetSpecDim, @ref PTB_GetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE
       
  @ingroup PVM_PTB   
*/
int PTB_InitSpecDim(int lowestDim,
                    int highestDim);

/** Sets the parameter @c PVM_SpecDimEnum to @c dimValue.

  If @c dimValue lies outside the legal range it will be set according to the recipe described
  for the function @ref UT_SetInLimits.

  @PVM_PARS
  - @c PVM_SpecDimEnum
  
  @PVM_RELCALL
  NONE 
  
  @PVM_TBCALL
  - @ref PTB_GetSpecDim

  @PVM_PRECOND
  Legal dimension range must have been set with @ref PTB_InitSpecDim.
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_SetSpecDim(2);
  @endcode
  
  @param dimensions    Number of dimensions

  @return Dimension number that was set

  @see @ref PTB_SetImagingDims, @ref PTB_InitSpatDim, @ref PTB_SetSpatDim, @ref PTB_GetSpatDim,
       @ref PTB_SetSpectrocopyDims, @ref PTB_InitSpecDim, @ref PTB_GetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE
       
  @ingroup PVM_PTB
*/
int PTB_SetSpecDim(int dimensions);

/** Retrieves the current value of @c PVM_SpecDimEnum as an int.

  @PVM_PARS
  NONE 
  
  @PVM_RELCALL
  NONE 
  
  @PVM_TBCALL
  NONE 

  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  int dim = PTB_GetSpecDim();
  @endcode
  
  @return Number of dimensions

  @see @ref PTB_SetImagingDims, @ref PTB_InitSpatDim, @ref PTB_SetSpatDim, @ref PTB_GetSpatDim,
       @ref PTB_SetSpectrocopyDims, @ref PTB_InitSpecDim, @ref PTB_SetSpecDim
       
  @todo Incomplete documentation: PVM_AVAILABLE
       
  @ingroup PVM_PTB
 */
int PTB_GetSpecDim(void);

/** Sets @c PVM_FovCm (cm).

  @PVM_AVAILABLE
  20031030

  @PVM_PARS
  - @c PVM_FovCm

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  Legal value of argument @a fov

  @PVM_ERROR
  - @c NULL pointer for argument @a fov
  - Illegal value for argument @a spatdim
  
  @PVM_EXAMPLE
  @code
  PTB_SetFovCm(PVM_Fov, PTB_GetSpatDim());
  @endcode

  @param[in] fov        Array of size @a spatDim, containing @a fov (mm)
  @param     spatDim    Number of spatial dimensions

  @ingroup PVM_PTB
*/
void PTB_SetFovCm(double *fov,
                  int    spatDim);

/** Set the spatial resolution.

  @PVM_PARS
  - @c PVM_SpatResol

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  - @a fov is a null pointer
  - @a matrix is a null pointer
  - @a spatDim is out of range [1, 3]
  
  @PVM_EXAMPLE
  @code
  
  @endcode

  @param[in] fov        Array of size @a spatDim containing FOV [mm]
  @param[in] matrix     rray of size @a spatDim containing matrix size
  @param     spatDim    Number of spatial dimensions
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB_INT
*/
void PTB_SetSpatResol(double *fov,
                      int    *matrix,
                      int    spatDim);

/* gen/src/prg/pvm_toolboxes/PvPvmTools/rfpulses.c */

/* gen/src/prg/pvm_toolboxes/PvPvmTools/utilities.c */

/** Returns methods manager version.

  @ingroup PVM_PTB_INT
*/
int PTB_Version(void);

/** Sets the parameter classes for @c PVM_UserType.

  This tools is used to set a list of parameter classes that will be hidden if @c PVM_UserType
  is set to @c Routine_User and shown if it is set to @c Expert_User.

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_ERROR
  NONE

  @param classNameList    Comma separated list of names of parameter classes

  @see @ref PTB_SetUserTypePars

  @ingroup PVM_DEPRECATED
*/
void PTB_SetUserTypeClasses(const char* classNameList);

/** Sets the parameter classes for @c PVM_UserType.

  This tools is used to set a list of parameter classes that will be hidden if @c PVM_UserType
  is set to @c Routine_User and shown if it is set to @c Expert_User.

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_ERROR
  NONE

  @param parNameList    Comma separated list of names of parameter names

  @see @ref PTB_SetUserTypePars

  @ingroup PVM_DEPRECATED
*/
void PTB_SetUserTypePars(const char* parNameList);

/** Initializes @c PVM_EffSWh.

  @PVM_H2{Note}   
  This toolbox function should be replaced by the digitizer parameter group. The handling of
  bandwidth and digital filters should than be implemented with the following set of toolboxes:
  @ref STB_InitDigPars, @ref STB_UpdateDigPars (@ref STB_SpecUpdateDigPars), and
  @ref ATB_SetDigPars
   
  @PVM_TBCALL
  - @ref ATB_MinSWh
  - @ref ATB_MaxSWh
  - @ref MRT_EffSWh

  @PVM_RELCALL
  - NONE DIRECTLY but this secondary relation calls @ref ATB_MaxSWh and @ref ATB_SetSWh both of
    which call parameter relations.

  @PVM_ERROR
  NONE

  @param antiAliasFactor    Oversampling factor

  @return  Effective sweep (Hz)

  @see @ref STB_InitDigPars, @ref STB_SpecUpdateDigPars, @ref STB_UpdateDigPars,
       @ref ATB_SetDigPars

  @ingroup PVM_DEPRECATED
*/
double PTB_InitEffSWh(double antiAliasFactor);

/** Use digitizer parameter group.

  Sets @c PVM_EffSWh to a legal value.

  @PVM_H2{Note}   
  This toolbox function should be replaced by the digitizer parameter group. The handling of
  bandwidth and digital filters should than be implemented with the following set of toolboxes:
  @ref STB_InitDigPars, @ref STB_UpdateDigPars (@ref STB_SpecUpdateDigPars), and
  @ref ATB_SetDigPars

  @PVM_TBCALL
  - @ref ATB_TestSWh
  - @ref MRT_SWh
  - @ref MRT_EffSWh

  @PVM_RELCALL
  - NONE DIRECTLY but this secondary relation calls @ref ATB_TestSWh which calls parameter
    relations.

  @PVM_ERROR
  NONE

  @param effSWh             Effective sweep (Hz)
  @param antiAliasFactor    Oversampling factor

  @return  Effective sweep (Hz)

  @see @ref STB_InitDigPars, @ref STB_SpecUpdateDigPars, @ref STB_UpdateDigPars,
       @ref ATB_SetDigPars

  @ingroup PVM_DEPRECATED
*/
double PTB_SetEffSWh(double effSWh,
                     double antiAliasFactor);

/** Contrains antialiasing within its limits. 

  This routine also initializes @a antiAlias and @a maxAntiAlias.

  @PVM_H2{Note}   
  This toolbox function should be replaced by the digitizer parameter group. The handling of
  bandwidth and digital filters should than be implemented with the following set of toolboxes:
  @ref STB_InitDigPars, @ref STB_UpdateDigPars (@ref STB_SpecUpdateDigPars), and
  @ref ATB_SetDigPars

  @PVM_TBCALL
  - @ref ATB_MaxAntiAlias

  @PVM_RELCALL
  - NONE DIRECTLY but this secondary relation indirectly calls @ref ATB_TestSWh via
    @ref ATB_MaxAntiAlias and @ref ATB_MaxSWh.

  @PVM_ERROR
  NONE

  @param numDims
  @param effSweepWidthHz
  @param antiAlias
  @param maxAntiAlias

  @see @ref STB_InitDigPars, @ref STB_SpecUpdateDigPars, @ref STB_UpdateDigPars,
       @ref ATB_SetDigPars

  @ingroup PVM_DEPRECATED   
*/ 
void PTB_ConstrainAntiAlias(int     numDims,
                            double *effSweepWidthHz,
                            double *antiAlias,
                            double *maxAntiAlias);

/** Set slice order.

  @PVM_PARS
  - @c PVM_ObjOrderList

  @PVM_TBCALL
  - @ref GTB_SliceOrder

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_SetSliceOrder(GTB_NumberOfSlices(PVM_NSPacks, PVM_SPackArrNSlices), PVM_ObjOrderScheme);
  @endcode
  
  @param nSlices     Number of slices
  @param sliceScheme Slice ordering scheme
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB_INT
*/
void PTB_SetSliceOrder(int                  nSlices,
                       PV_SLICE_SCHEME_TYPE sliceScheme);

/** Maximum possible size of a PVM array parameter per dimension.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Maximum number of elements per dimension
       
  @ingroup PVM_PTB
*/ 
int PTB_MaxArraySize(void);

/** Retrieves entry of @c PVM_ShapeHandler that belongs to RF pulse.

  This function is used to access information stored in parameter @c PVM_ShapeHandler.
  
  @PVM_AVAILABLE
  20100101
  
  @PVM_PARS
  - @c PVM_ShapeHandler (only referenced)
  
  @PVM_TBCALL
  - @ref UT_GetParType
  
  @PVM_RELCALL
  NONE
  
  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  int shidx=-1;
  int errstate=0;
  char errmsg[1024];


  PVM_RF_SHAPE_HANDLER_TYPE *shndlr=0;
  shidx=PTB_GetShapeHandlerIndex(parn,&errstate);
  switch(errstate)
  {
    case 0:
      break;
    case 1: // no entry available
      snprintf(errmsg,1023,"parameter \"%s\" has not been initialized",parn);
      UT_ReportError(errmsg);
      break;
    case 2: // parn not found
      snprintf(errmsg,1023,"parameter \"%s\" has not been initialized",parn);
      UT_ReportError(errmsg);
      break;

    case -3: // parameter type not supported
      snprintf(errmsg,1023,"parameter \"%s\" has wrong parameter type",parn);
      UT_ReportError(errmsg);
      break;
    case -1:
      snprintf(errmsg,1023,"parameter \"%s\" does not exist",parn);
      UT_ReportError(errmsg);
      break;        
  }

  shndlr = PVM_ShapeHandler +shidx;

  @endcode
  
  @param[in] parname name of parameter: following types are supported:
      - @c PVM_RF_PULSE (shape struct)
      - @c PV_PULSE_LIST (shape list enum)
      - @c PVM_RF_PULSE_AMP_TYPE (pulse amplitude struct)
      - double array parameter (waveform array)
  @param[out] errstate pointer to int variable (0 pointer allowed) indicating following
            error conditions:
      - @c  0 = ok
      - @c  1 = no entry available
      - @c -2 = not found
      - @c -1 = wrong parameter name
      - @c -2 = qualified parameter name
      - @c -3 = wrong parameter type

  @return -1 in case of errors, otherwise index in shape handler array

  @ingroup PVM_PTB_INT
*/
int PTB_GetShapeHandlerIndex(const char *const parname, int *const errstate);

/* gen/src/prg/pvm_toolboxes/PvPvmTools/versions.c */

/** PVM is consistent.

  @ingroup PVM_DEPRECATED
*/
YesNo PTB_PvmIsConsistent(void);

/** Determines if method conforms to sequence model.

  @PVM_PARS
  - @c PVM_ConformsToSeqModel may be initalised

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return @c Yes = method conforms to sequence model, else @c No
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB_INT
*/
YesNo PTB_MethodConformsToSeqModel(void);

/** Determines if method conforms to PVM version.

  @PVM_PARS
  - @c PVM_RequiresPvmVersion may be initalised

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return @c Yes = method conforms to PVM version, else @c No
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB_INT
*/
YesNo PTB_MethodConformsToPvmVersion(void);

/** 
  @ingroup PVM_DEPRECATED
  
  @param fromMethodVersion
*/
YesNo PTB_ConformsToMethod(int fromMethodVersion);

/** Checks PVM version required by method.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  - @ref PTB_MethodConformsToPvmVersion

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  if (PTB_MethodRequiresPvmVersion(20010501) == Yes)
  {
    B_Isotropic();
  }
  else
  {
    //  the further version requirements are handled here    
    STB_Isotropic();     
  }
  @endcode

  @param versionRequest Version required by method

  @return @c Yes = PVM version required by method is avaliable, else @c No
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB_INT
*/
YesNo PTB_MethodRequiresPvmVersion(int versionRequest);

/** Makes sure a certain version of PVM toolboxes is used.

  @PVM_PARS
  - @c PVM_ConformsToSeqModel
  - @c PVM_RequiresPvmVersion
  
  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  - Unknown PVM version requested.
  
  @PVM_EXAMPLE
  @code
  PTB_VersionRequirement(Yes, 20100101, "");
  @endcode

  @param     seqModelCompliant @c Yes = Method must conform to sequence model
  @param     fromPvmVersion    Required PVM version
  @param[in] feature_list      List of required features (may be empty)

  @return @c Yes = PVM version required by method is avaliable, else @c No
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
YesNo PTB_VersionRequirement(YesNo      seqModelCompliant,
                             int        fromPvmVersion,
                             const char *feature_list);

/* gen/src/prg/pvm_toolboxes/PvPvmTools/DynFileEnum.c */

/** Initialise dynamic enum with sub-directory names.
    
  @PVM_PARS
  - Parameter given by @a enumParName
  
  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  int size = PTB_InitDynEnumWithSubdirNames("SystemStatusEnum", 
                                            "/opt/PV6/conf/instr/Datastation/preemp");
  @endcode

  @param[in] enumParName   Parameter name of enum  
  @param[in] pathBaseName  Path where subdirectories are located

  @return Number of entries found
  
  @see @ref PTB_InitDynEnumWithRegFileNames
  
  @todo Incomplete documentation: PVM_AVAILABLE
 
  @ingroup PVM_PTB_INT
*/
int PTB_InitDynEnumWithSubdirNames(const char *const enumParName,
                                   const char *const pathBaseName);

/** Initialise dynamic enum with file names.
    
  @PVM_PARS
  - Parameter given by @a enumParName
  
  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  int size = PTB_InitDynEnumWithRegFileNames("PVM_PreemphasisFileEnum", 
                                             "/opt/PV6/conf/instr/Datastation/preemp/S116");
  @endcode

  @param[in] enumParName   Parameter name of enum  
  @param[in] pathBaseName  Path where files are located

  @return Number of entries found
  
  @see @ref PTB_InitDynEnumWithSubdirNames
  
  @todo Incomplete documentation: PVM_AVAILABLE
 
  @ingroup PVM_PTB_INT
*/
int PTB_InitDynEnumWithRegFileNames(const char *const enumParName,
                                    const char *const pathBaseName);

/* gen/src/prg/pvm_toolboxes/PvPvmTools/PtbAdj.c */

/** Appends adjustment.

  This function should be called in methods that support additional adjustment procedures that
  should be executed automatically (@a type = @c per_scan) or on demand 
  (@a type = @c on_demand). A call of this function makes the adjustment available in the
  adjustment platform. Subsequent calls of this function define the order of @c per_scan
  adjustments as specified by argument @a type. Any other type will have no effect on the
  adjustment lists.

  @PVM_H1{Implementation}
  If the order and amount of @c per_scan adjustments should be controlled on method level,
  follow these steps:
  - Call @ref PTB_ClearAdjustments
  - Call @ref PTB_AppendAdjustment with arguments dependent on available method specific
    adjustments
  - Use @ref PTB_AppendConfiguredAdjustment if adjustments that have been configured should be
    used

  @PVM_AVAILABLE
  20100101

  @PVM_PARS
  - Internal parameters of the adjustment manager

  @PVM_TBCALL
  NONE 

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  // clears the per_scan adjustment list
  PTB_ClearAdjustments();
  
  // appends trajectory adjustment at end of list
  ADJ_TYPE_ENUM type=on_demand;
  if( (PVM_TrajAdjMode == Traj_Per_Scan ||  
      (PVM_TrajAdjMode == Traj_If_Required && PVM_TrajUpToDate == No))
  {
     type=per_scan;
  }

  PTB_AppendAdjustment("Trajectory",
                       "Trajectory Measurement",
                       "Measurement of the k-space trajectory",
                       type);

  // appends receiver gain adjustment at end of list
  PTB_AppendConfiguredAdjustment(per_scan,RCVR);
  @endcode

  @param name             Adjustment name specified as string used to identify the adjustment
                          during execution
  @param displayName      Name that is shown inside the adjustment platform
  @param tooltip          Short description of the adjustment
  @param type             Must be either @c per_scan or @c on_demand 
  @param categ            Optional argument (default is @c OTHER) specifying the adjustment
                          category
  @param protocol         Optional argument specifying the adjustment protocol name 
                          (an empty string will be treated as method specific adjustment)
  @param methodContext    Optional argument specifying a special context that may be used as
                          key to restore adjusted parameters or to control the behavior of the
                          adjustment at execution time.

  @return Possible return values are
          - @c 0 on success
          - Non-zero for types other than @c per_scan or @c on_demand

  @see @ref PTB_AppendConfiguredAdjustment, @ref PTB_ClearAdjustments
  
  @ingroup PVM_PTB
*/
int PTB_AppendAdjustment(const char *const name,
                         const char *const displayName,
                         const char *const tooltip,
                         ADJ_TYPE_ENUM     type,
                         AdjCategoryEnum   categ=OTHERADJ,
                         const char *const protocol=0,
                         const char*const  methodContext=0);

/** Appends configured adjustment.

  This function should be called if adjustments that belong to the adjustment configuration
  should be executed @c per_scan or @c on_demand. Subsequent calls of this function define the
  order of @c per_scan adjustments as specified by argument @a type. Any other type will have
  no effect on the adjustment lists.

  @PVM_H1{Implementation}
  If the order and amount of @c per_scan adjustments should be controlled on method level,
  follow these steps:
  - Call @ref PTB_ClearAdjustments
  - Call @ref PTB_AppendConfiguredAdjustment
  - Use @ref PTB_AppendAdjustment to append method specific adjustments

  @PVM_AVAILABLE
  20100101

  @PVM_PARS
  - Internal parameters of the adjustment manager

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  // clears the per_scan adjustment list
  PTB_ClearAdjustments();
  
  // appends trajectory adjustment at end of list
  ADJ_TYPE_ENUM type=on_demand;
  if( (PVM_TrajAdjMode == Traj_Per_Scan ||  
      (PVM_TrajAdjMode == Traj_If_Required && PVM_TrajUpToDate == No))
  {
     type=per_scan;
  }

  PTB_AppendAdjustment("Trajectory",
                      "Trajectory Measurement",
                      "Measurement of the k-space trajectory",
                      type);

  // appends receiver gain adjustment at end of list
  PTB_AppendConfiguredAdjustment(per_scan,RCVR);
  @endcode

  @param type             Must be either @c per_scan or @c on_demand 
  @param categ            Optional argument (default is @c OTHER) specifying the adjustment
                          category
  @param name             Optional argument specifying the adjustment protocol name 
                          (an empty string will be treated as method specific adjustment)
  @param methodContext    Optional argument specifying a special context that may be used as
                          key to restore adjusted parameters or to control the behavior of the
                          adjustment at execution time.

  @return Possible return values are
         - @c 0 on success
         - < @c 0 for types other than @c per_scan or @c on_demand 
         - > @c 0 if adjustment was not found in list of configured adjustments

  @see @ref PTB_AppendAdjustment, @ref PTB_ClearAdjustments

  @ingroup PVM_PTB
*/
int PTB_AppendConfiguredAdjustment(ADJ_TYPE_ENUM     type,
                                   AdjCategoryEnum   categ,
                                   const char *const name=0,
                                   const char *const methodContext=0);

/** Clears adjustment list.

  This function should be called if the list of @c on_demand or @c per_scan adjustments should
  be cleared to be build up specifically in the method. Dependent on (optional) argument 
  @c clearall (default: No) the list of @c per_scan adjustments is cleared completely 
  (clearall = Yes) or it is cleared and configured mandatory per_scan adjustments are prepended. 
  



  @PVM_H1{Implementation}
  If the order and amount of @c per_scan adjustments should be controlled on method level,
  follow these steps:
  - Call @ref PTB_ClearAdjustments
  - Call @ref PTB_AppendConfiguredAdjustment
  - Use @ref PTB_AppendAdjustment to append method specific adjustments

  @PVM_AVAILABLE
  20100101

  @PVM_PARS
  - Internal parameters of the adjustment manager

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  // clears the per_scan adjustment list
  PTB_ClearAdjustments();
  
  // appends trajectory adjustment at end of list
  ADJ_TYPE_ENUM type=on_demand;
  if( (PVM_TrajAdjMode == Traj_Per_Scan ||  
      (PVM_TrajAdjMode == Traj_If_Required && PVM_TrajUpToDate == No))
  {
     type=per_scan;
  }

  PTB_AppendAdjustment("Trajectory",
                       "Trajectory Measurement",
                       "Measurement of the k-space trajectory",
                        type);

  // appends receiver gain adjustment at end of list
  PTB_AppendConfiguredAdjustment(per_scan,RCVR);
  @endcode

  @param clearall all adjustments are cleared if set to Yes (default = No, see above) 
  @see @ref PTB_AppendAdjustment, @ref PTB_AppendConfiguredAdjustment

  @ingroup PVM_PTB
*/
void PTB_ClearAdjustments(YesNo clearall=No);

/** Registers GOP adjustment results.

  This function should be called in the redirected relation of @c PVM_GopAdjResultHandler if
  the dataset that is acquired within a GOP adjustment should be loaded in the database of 
  @em ParaVision (e.g. to visualize it).  

  @PVM_AVAILABLE
  20100101

  @PVM_PARS
  - Internal parameters of the adjustment manager

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_RegisterGopAdj();
  @endcode

  @ingroup PVM_PTB
*/
void PTB_RegisterGopAdj(void);

/** Declares a method specific adjustment request.

  This function was intended to be called in the initMeth routine of a PVM method to activate a
  method specific adjustment. Now the list of method specific adjustments is controlled using
  @ref PTB_ClearAdjustments, @ref PTB_AppendAdjustment, and @ref PTB_AppendConfiguredAdjustment.

  @PVM_AVAILABLE
  20050101

  @PVM_DEACT
  20100101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @param categ         Specifies adjustment category @n
                       Allowed values: @c SHIM, @c FREQ, @c TRANSM, @c RCVR, @c USERADJ1,
                                       @c USERADJ2, @c USERADJ3
  @param type          Specifies the adjustment type @n
                       Allowed values: @c on_demand (default), @c per_study, @c per_scan

  @param name          Specifies the adjustment name

  @param adjustPars    Comma separated list of parameters that are adjusted (see above)
  @param contstr       Special context string

  @see @ref PTB_GetAdjCategory, @ref PTB_GetAdjName, @ref PTB_AdjMethSpec, 
       @ref PTB_GetAdjParList, @ref PTB_GetAdjContext

  @return @c No

  @ingroup PVM_DEPRECATED
*/
YesNo PTB_SetAdjContext(AdjCategoryEnum   categ,
                        ADJ_TYPE_ENUM     type,
                        const char *const name,
                        const char *const adjustPars,
                        const char *const contstr);


/** Sets the description of a method specific adjustment request.

  This function was intended to be called in the initMeth routine of a PVM method to specify
  the short and long description of a method specific adjustment. Now the list of method
  specific adjustments (including descriptions) is controlled using @ref PTB_ClearAdjustments,
  @ref PTB_AppendAdjustment, and @ref PTB_AppendConfiguredAdjustment.

  @PVM_AVAILABLE
  20050101

  @PVM_DEACT
  20100101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @param categ          Specifies adjustment category
                        Allowed values: @c SHIM, @c FREQ, @c TRANSM, @c RCVR, @c USERADJ1,
                                        @c USERADJ2, @c USERADJ3
  @param displayName    Short (16 character) display name of adjustment
  @param description    New current adjustment description

  @return @c Yes

  @ingroup PVM_DEPRECATED
*/
YesNo PTB_SetAdjDescription(AdjCategoryEnum categ,
                            const char      *displayName,
                            const char      *description);

/** Delivers the current adjustment category.

  This function delivers the current required adjustment category (SHIM, FREQ, TRANSM, RCVR,
  USERADJ1, USERADJ2, USERADJ3). It is intended to be called in a redirected parameter relation
  of @c PVM_AdjHandler. With help of this function the method is able to distinguish which
  adjustment has to be performed and to setup this adjustment specifically.

  If the method is not able to perform the desired adjustment it should call the relation of
  @c PVM_AdjHandler forcing the default behavior: <code>ParxRelsParRelations("PVM_AdjHandler", Yes)</code>.

  @PVM_AVAILABLE
  20050101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Currently required adjustment category 

  @see @ref PTB_GetAdjResultCategory, @ref PTB_AdjMethSpec, @ref PTB_GetAdjParList,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
AdjCategoryEnum PTB_GetAdjCategory(void);

/** Delivers the current adjustment result category.

  This function delivers the category of the adjustment for which the result handler relations
  are being called (@c SHIM, @c FREQ, @c TRANSM, @c RCVR, @c USERADJ1, @c USERADJ2, @c USERADJ3, @c OTHER).
  It is intended to be called in a redirected parameter relation of @c PVM_AdjResultHandler. With
  help of this function the method is able to distinguish which adjustment has been performed
  and to react to its result specifically.

  @PVM_AVAILABLE
  20050101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Currently required adjustment category 

  @see @ref PTB_GetAdjCategory, @ref PTB_AdjMethSpec, @ref PTB_GetAdjParList,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
AdjCategoryEnum PTB_GetAdjResultCategory(void);

/** Delivers the name of the current subadjustment.

  This function delivers the name of the subadjustment of the adjustment for which the result
  handler relations are being called (@c SHIM, @c FREQ, @c TRANSM, @c RCVR, @c USERADJ1, @c USERADJ2, @c USERADJ3).
  It is intended to be called in a redirected parameter relation of @c PVM_AdjResultHandler.
  With help of this function the method is able to distinguish which subadjustment has been
  performed and to react to its result specifically.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Currently required adjustment category 

  @see @ref PTB_GetAdjCategory, @ref PTB_AdjMethSpec, @ref PTB_GetAdjParList,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
const char *PTB_GetAdjResultSubProcess(void);

/** Delivers the name of the current adjustment.

  This function delivers the name of the subadjustment of the adjustment for which the result
  handler relations are being called (@c SHIM, @c FREQ, @c TRANSM, @c RCVR, @c OTHER, @c USERADJ1,
  @c USERADJ2, @c USERADJ3). It is intended to be called in a redirected parameter relation of
  @c PVM_AdjResultHandler. With help of this function the method is able to distinguish which
  subadjustment has been performed and to react to its result specifically.

  @PVM_AVAILABLE
  20100101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Currently required adjustment category 

  @see @ref PTB_GetAdjCategory, @ref PTB_AdjMethSpec, @ref PTB_GetAdjParList,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
const char *PTB_GetAdjResultName(void);

/** Delivers the current adjustment name.

  This function delivers the current required adjustment name. It is intended to be called in a
  redirected parameter relation of @c PVM_AdjHandler. With help of this function the method is
  able to test whether it is responsible to perform the adjustment or not.

  If the method is not able to perform the desired adjustment it should call the relation of
  @c PVM_AdjHandler forcing the default behavior: <code>ParxRelsParRelations("PVM_AdjHandler", Yes)</code>.

  @PVM_AVAILABLE
  20050101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Currently required adjustment name 

  @see @ref PTB_GetAdjCategory, @ref PTB_AdjMethSpec, @ref PTB_GetAdjParList,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
const char *PTB_GetAdjName(void);

/** Delivers information about method specific adjustments.

  This function returns @c Yes in case a method specific adjustment is required. It is intended
  to be called in a redirected parameter relation of @c PVM_AdjHandler. With help of this
  function the method is able to test whether it is responsible to perform the adjustment or
  not.

  If the method is not able to perform the desired adjustment it should call the relation of
  @c PVM_AdjHandler forcing the default behavior: <code>ParxRelsParRelations("PVM_AdjHandler", Yes)</code>.

  @PVM_AVAILABLE
  20050101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return  @c Yes if a method specific adjustment is required else @c No

  @see @ref PTB_GetAdjCategory, @ref PTB_GetAdjName, @ref PTB_GetAdjParList,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
YesNo PTB_AdjMethSpec(void);

/** Delivers information about the adjustment protocol used.

  This function returns the name of the adjustment protocol. It is intended to be called in a
  redirected parameter relation of @c PVM_AdjHandler. 

  @PVM_AVAILABLE
  20070101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return  @c Yes if a method specific adjustment is required else @c No

  @see @ref PTB_GetAdjCategory, @ref PTB_GetAdjName, @ref PTB_GetAdjParList,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
const char *PTB_GetAdjProtocol(void);

/** Delivers information which parameters have to be adjusted.

  This function returns a comma separated list of parameters that have to be adjusted. It is
  intended to be called in a redirected parameter relation of @c PVM_AdjHandler. With help of
  this function the method is able to test whether it is responsible to perform the adjustment
  or not.

  If the method is not able to perform the desired adjustment it should call the relation of
  @c PVM_AdjHandler forcing the default behavior: <code>ParxRelsParRelations("PVM_AdjHandler", Yes)</code>.

  @PVM_AVAILABLE
  20050101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return  Comma separated list of parameters (exception @c \#SHIM\#)

  @see @ref PTB_GetAdjCategory, @ref PTB_GetAdjName, @ref PTB_AdjMethSpec,
       @ref PTB_GetAdjContext

  @ingroup PVM_PTB
*/
const char *PTB_GetAdjParList(void);

/** Get method context of adjustment.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return  Method context of adjustment handler

  @see @ref PTB_GetAdjCategory, @ref PTB_GetAdjName, @ref PTB_AdjMethSpec,
       @ref PTB_GetAdjParList

  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
const char *PTB_GetAdjContext(void);

/** Deactivates a method specific adjustment request.

  This function was used to deactivate a method specific adjustment request. Now the list of
  method specific adjustments is controlled using @ref PTB_ClearAdjustments, 
  @ref PTB_AppendAdjustment, and @ref PTB_AppendConfiguredAdjustment.

  @PVM_AVAILABLE
  20050101

  @PVM_DEACT
  20100101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @param categ    AdjCategoryEnum (either @c EMPTY, @c SHIM, @c FREQ, @c TRANSM, @c RCVR or
                                   @c USERADJ1-3)

  @see  @ref PTB_SetAdjContext

  @ingroup PVM_DEPRECATED
*/
void PTB_DeactivateAdj(AdjCategoryEnum categ);

/** Writes special information about the adjustment.

  This function is used to write information about the adjustment result of an adjustment
  method. This information may be used to retrieve adjusted results in subsequent scans. The
  function is intended to be used during an adjustment in the redirected relation of
  @c PVM_AdjHandler.

  @PVM_AVAILABLE
  20070101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_SetRunAdjContext("GLOBAL SHIM");
  @endcode

  @param contx    String containing the information that should be passed

  @return @c Yes if the string could be passed, @c No in case it was too long

  @see  @ref PTB_SetAdjContext

  @ingroup PVM_PTB
*/
YesNo PTB_SetRunAdjContext(const char *const contx);

/** Checks if an adjustment subprocess is running.

  This function is used to retrieve information about an adjustment subprocess that might be
  executed during an adjustment. The subprocess name must be specified by argument. In case 
  @c 0 or an empty string is provided as subprocess argument the return value is @c Yes in case
  no subprocess is running.

  @PVM_AVAILABLE
  20070101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  if (PTB_CheckSubProcess(0) == Yes) 
  {
    // init subprocesses
    ...
  } 
  else if (PTB_CheckSubProcess("Traj") == Yes) 
  { 
    // adjust trajectory
    ...
  }
  else if (PTB_CheckSubProcess("Rg") == Yes)
  {
    // adjust RG only
    ...
  }       
  else
  { 
    // unknown sub-adjustment
  }
  @endcode

  @param procnam    Name of the subprocess that should be checked. A @c 0 or empty string is
                    allowed to check whether no subprocess is running.

  @return @c Yes (@c No) if the subprocess specified by argument is (not) running 

  @see  @ref PTB_InitSubProcess

  @ingroup PVM_PTB
*/
YesNo PTB_CheckSubProcess(const char *const procnam);

/** Initializes adjustment subprocesses.

  This function is used to initialize adjustment subprocesses within an adjustment. The
  adjustment results of consecutive subprocesses are available for all following subprocesses.
  The subprocesses are specified as names that are separated by a colon "," in string
  argument @a proclis. On success the number of subprocesses that are initialized are returned
  as int value. A value less than @c 1 indicates an error condition. Calling this function with 
  @c 0 argument or an empty string will deactivate subprocesses. Specifying only one subprocess
  will be allowed but useless.

  @PVM_H2{Note}
  Each subprocess will be done in a separate parameter space, within a subprocess the method
  may change the acquisition mode, the original mode will be restored at the end of the
  adjustment subprocess chain.

  This function is intended to be used in the redirected relation of @c PVM_AdjHandler.

  @PVM_AVAILABLE
  20070101

  @PVM_PARS
  - Internal parameters of the adjustment manager overlay

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  - Relation of internal parameters of the adjustment manager overlay

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  Extend the receiver adjustment to subprocesses

  @code
  const char *const sublis="subproc1,subproc2,subproc3";

  (..)

  switch(PTB_GetAdjCategory)
  {
  case RCVR:
  if(Yes==PTB_CheckSubProcess(0))
  {
  if(3 != PTB_InitSubProcess(sublis))
  {
  ( some error handling code )
  }
  else 
  {
   // initialization of subprocesses succeded, return to adjmanager
   return;
  }
  }

  if(Yes==PTB_CheckSubProcess("subproc1"))
  {
   // actions to do in first subprocess 
  }
  else if(Yes==PTB_CheckSubProcess("subproc2"))
  {
   // actions to do in second subprocess 
  }
  else if(Yes==PTB_CheckSubProcess("subproc3"))

   // actions to do in third subprocess 
  }
  break;
  // other adjustments
  }
  @endcode

  @param proclis    Colon separated list of adjustment subprocess names

  @return Number of successfully initialized subprocesses

  @see  @ref PTB_CheckSubProcess

  @ingroup PVM_PTB
*/
int PTB_InitSubProcess(const char *const proclis);

/** Delivers information whether adjustment is started.

  This function may be used within the redirected relation of @c PVM_AdjHandler to determine
  whether an adjustment should be prepared to be started. In case the method should react
  specifically to generate the data for the adjustment algorithm, these specific changes should
  be performed for a return value @c Yes. 

  @PVM_AVAILABLE
  20100101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return @c Yes = adjustment is started, else @c No

  @ingroup PVM_PTB
*/
YesNo PTB_AdjustmentStarting(void);


/** Delivers reason of relation call of PVM_AdjHandler.

  This function may be used within the redirected relation of @c PVM_AdjHandler to determine
  whether its relation has been called because the adjustment platform has been opened or because
  an adjustment that is started should be initialized. In the latter case the method may react
  specifically to generate the data for the adjustment algorithm.

  @PVM_AVAILABLE
  20100101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  @PVM_EXAMPLE

  @code
  // inside redirected relation of PVM_AdjHandler
  ADJ_HANDLER_CONTEXT mode;

  if(PTB_AdjHandlerCall(&mode))
  {
      switch(mode)
      {
        default:
        case HANDLE_ACQUISITION:
            // some code to prepare the method to the specific adjustment

            break;
        case HANDLE_PLATFORM:
           // code to prepare the result parameters visible in the result 
           // parameter card
           break;
      }
  }


  @endcode

  @param  mode in case of return value 1 it is set to @c HANDLE_ACQUISITION or 
          @c HANDLE_PLATFORM dependent on the reason of the @c PVM_AdjHandler relation
          call
  @return @c 1 if @c PVM_AdjHandler has a value else 0



  @ingroup PVM_PTB
*/
int PTB_AdjHandlerCall(ADJ_HANDLER_CONTEXT *mode);


/** Retrieves information about available configured adjustments.

  This functions may be used to make a specific method feature
  dependent on a dedicated adjustment configuration. 

  Its return value indicates whether an adjustment with name @em adjName
  is configured as adjustment with requirements specified by arguments. 
  As consequence a call of  @ref PTB_ClearAdjustments will not clear
  those registered adjustments and the adjustments are prepended (in the 
  configured order) into the on_demand or per_scan adjustment list.

  An adjustment is configured if the pool of known adjustment contains
  this adjustment (specified by name).


  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  - internal errors to be reported to hotline.

  @PVM_EXAMPLE
  This example shows how to make a method feature dependent on a valid
  adjustment configuration. Only if in the per_scan list of adjustments
  a shim procedure is configured mandatory the shim requirements may be 
  realized when starting a measurment with scan or continue:

  @code
  // ask for a SHIM adjustment in the per_scan adjustment list,require
  // a standard adjustment.

  YesNo available =
  PTB_AdjAvailable(SHIM,            // SHIM,FREQ,WOBBLE,TRANSM,RCVR,OTHERADJ 
                   "SHIM_Scan", // adjustment name
                   per_scan);        // per_study, per_scan or on_demand


  if(No==available) // study shim or mapshim not possible in this case
  {                 
     // deactivate shim handling
     PVM_ReqShimEnum=Current_Shim;
  }

  @endcode
  
  @param[in]  category category of required mandatory adjustment
  @param[in]  adjName  string (max. length ADJ_NAME_LENGTH)
  @param[in]  type     type of the required adjustment
  @return Yes in case the adjustment is configured else No.

  @ingroup PVM_PTB
*/
YesNo PTB_AdjAvailable(AdjCategoryEnum category,
                       const char *const adjName,
                       ADJ_TYPE_ENUM type);






/* gen/src/prg/pvm_toolboxes/PvPvmTools/VisuUtils.c */

/** Sets the Id of an existing frame group in post processing parameters.

  CAUTION: After setting the Id, the loop changes its identity. 

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuSetLoopId(PV_IDL_CONSTANT(visuid_framegroup_CYCLE), PV_IDL_CONSTANT(visuid_framegroup_CARDIAC_MOVIE));
  @endcode
  
  @param[in]  oldId    Existing Id of a Visu frame group
  @param[in]  newId    New identifier of the Visu frame group

  @return @c 0 if everything is ok else @c -1

@see @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetLoopName, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetMovieLoopName, @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuRemoveLoopDependentParameter, @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuSetLoopId(const char *oldId, 
                      const char *newId);

/** Sets the Id of the echo loop in post processing parameters.

  CAUTION: After setting the Id the loop is not an echo loop anymore.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuSetEchoLoopId(PV_IDL_CONSTANT(visuid_framegroup_MOVIE));
  @endcode
  
  @param[in] id    Id of the echo loop

  @return @c 0 if everything is ok else @c -1

@see @ref PTB_VisuSetLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetLoopName, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetMovieLoopName, @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuRemoveLoopDependentParameter, @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuSetEchoLoopId(const char *id);

/** Sets the Id of the movie loop in post processing parameters.

  CAUTION: After setting the Id the loop is not a movie loop anymore.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuSetMovieLoopId(PV_IDL_CONSTANT(visuid_framegroup_DIFFUSION));
  @endcode
  
  @param[in] id    Id of the movie loop

  @return @c 0 if everything is ok else @c -1

@see @ref PTB_VisuSetLoopId, @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetLoopName, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetMovieLoopName, @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuRemoveLoopDependentParameter, @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuSetMovieLoopId(const char *id);

/** Sets the name/comment of a frame group in post processing parameters.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuSetLoopName(PV_IDL_CONSTANT(visuid_framegroup_IRMODE), "Inversion Mode");
  @endcode
  
  @param[in] id      Identification of the frame group
  @param[in] name    New name/comment of the frame group

  @return @c 0 if everything is ok else @c -1

@see @ref PTB_VisuSetLoopId, @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetMovieLoopName, @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuRemoveLoopDependentParameter, @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuSetLoopName(const char *id, 
                        const char *name);

/** Sets the name/comment of the echo loop in post processing parameters.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuSetEchoLoopName("Inversion");
  @endcode
  
  @param[in] name    Name/comment of the echo loop

  @return @c 0 if everything is ok else @c -1

@see @ref PTB_VisuSetLoopId, @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetLoopName,
     @ref PTB_VisuSetMovieLoopName, @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuRemoveLoopDependentParameter, @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuSetEchoLoopName(const char *name);

/** Sets the name/comment of the movie loop in post processing parameters.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuSetMovieLoopName("Inversion");
  @endcode
  
  @param[in] name    Name/comment of the movie loop

  @return @c 0 if everything is ok else @c -1

@see @ref PTB_VisuSetLoopId, @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetLoopName, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuRemoveLoopDependentParameter, @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuSetMovieLoopName(const char *name);

/** Sets a dependent parameter for a given loop.

  @PVM_USEINSTEAD{PTB_VisuSetLoopDependentParameter}

  @param loopId      Identifier of loop to set dependent parameter
  @param parName     Name of dependent parameter
  @param startNdx    Start ndx of dependent values

  @return @c 0 if everything is ok else @c -1

  @todo Incomplete documentation: PVM_AVAILABLE, PVM_PARS, PVM_TBCALL, PVM_RELCALL,
                                  PVM_PRECOND, PVM_ERROR, PVM_EXAMPLE @n

  @ingroup PVM_DEPRECATED
*/
int PTB_VisuSetLoopDependantParameter(const char *loopId,
                                      const char * parName,
                                      int        startNdx);

/** Sets a dependent parameter for a given loop.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuSetLoopDependentParameter(PV_IDL_CONSTANT(visuid_framegroup_MOVIE), 
                                    "VisuAcqInversionTime",
                                    0);
  @endcode
  
  @param[in] loopId      Identifier of loop to set dependent parameter
  @param[in] parName     Name of dependent parameter
  @param     startNdx    Start ndx of dependent values

  @return @c 0 if everything is ok else @c -1

@see @ref PTB_VisuSetLoopId, @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetLoopName, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetMovieLoopName, 
     @ref PTB_VisuRemoveLoopDependentParameter, @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuSetLoopDependentParameter(const char *loopId,
                                      const char * parName,
                                      int        startNdx);

/** Removes a dependent parameter for a given loop.

  @PVM_USEINSTEAD{PTB_VisuRemoveLoopDependentParameter}
  
  @param loopId          Identifier of the loop
  @param parName         Name of dependent parameter to remove
  @param adaptDepVals    Adapt the dependent parameter

  @return Start ndx in @a parName array if everything is ok else @c -1

  @todo Incomplete documentation: PVM_AVAILABLE, PVM_PARS, PVM_TBCALL, PVM_RELCALL,
                                  PVM_PRECOND, PVM_ERROR, PVM_EXAMPLE @n

  @ingroup PVM_DEPRECATED
*/
int PTB_VisuRemoveLoopDependantParameter(const char * loopId,
                                         const char * parName,
                                         YesNo      adaptDepVals);

/** Removes a dependent parameter for a given loop.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuRemoveLoopDependentParameter(PV_IDL_CONSTANT(visuid_framegroup_MOVIE),
                                       "VisuFGElemComment",
                                       Yes);
  @endcode
  
  @param[in] loopId          Identifier of the loop
  @param[in] parName         Name of dependent parameter to remove
  @param     adaptDepVals    Adapt the dependent parameter

  @return Start ndx in @a parName array if everything is ok else @c -1

@see @ref PTB_VisuSetLoopId, @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetLoopName, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetMovieLoopName, @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuInsertLoop
     
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_VisuRemoveLoopDependentParameter(const char * loopId,
                                         const char * parName,
                                         YesNo      adaptDepVals);

/** Inserts a new frame group.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuInsertLoop(PV_IDL_CONSTANT(visuid_framegroup_IRMODE),
                     PV_IDL_CONSTANT(visuid_framegroup_MOVIE),
                     FairTIR_NExp,
                     "Inversion");
  @endcode
  
  @param[in] beforeId    Existing group identifier of frame group before the insertion @n
                         If empty new frame group is group @c 0
  @param[in] id          Group Id of inserted frame group
  @param     len         Number of frame group element
  @param[in] comment     Group comment of inserted frame group (maybe @c 0)

@see @ref PTB_VisuSetLoopId, @ref PTB_VisuSetEchoLoopId,
     @ref PTB_VisuSetMovieLoopId, @ref PTB_VisuSetLoopName, @ref PTB_VisuSetEchoLoopName,
     @ref PTB_VisuSetMovieLoopName, @ref PTB_VisuSetLoopDependentParameter, 
     @ref PTB_VisuRemoveLoopDependentParameter
     
  @todo Incomplete documentation: PVM_AVAILABLE
   
  @ingroup PVM_PTB
*/
void PTB_VisuInsertLoop(const char * beforeId,
                        const char * id,
                        int        len,
                        const char * comment);

/** Change number of elements of a given frame group.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuChageFGLen(PV_IDL_CONSTANT(visuid_framegroup_DIFFUSION), PVM_DwNDiffExp);
  @endcode
  
  @param[in] id     Frame group Id
  @param     newLen New number of frame group element, must be greater 0.

  @return @c 0 on success, @c -1 on error

  @see @ref PTB_VisuSetFGElementComment
  
  @todo Incomplete documentation: PVM_AVAILABLE
   
  @ingroup PVM_PTB
 */
int PTB_VisuChangeFGLen(const char * id, int  newLen);

/** Decrease number of elements of a given frame group.
  This function is deprecated. Use @ref PTB_VisuChangeFGLen instead.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @ingroup PVM_DEPRECATED
  @see @ref PTB_VisuChangeFGLen

  */

#define PTB_VisuDecreaseFGLen(id, newLen) PTB_VisuChangeFGLen((id), (newLen))

/** Sets comment for frame group elements

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  char comments[80];
  memset(comments, 0, 80);
  strcpy(comments, "Selective Inversion Mode");
  strcpy(&comments[40], "Non-selective Inversion Mode");
  PTB_VisuSetFGElementComment(PV_IDL_CONSTANT(visuid_framegroup_IRMODE),
                              comments,
                              2,
                              40);
  @endcode
  
  @param id            Frame group Id
  @param comment       Comment array (one dimensional)
  @param commentLen    Number of comments
  @param stringLen     Maximum length of one comment

  @see @ref PTB_VisuDecreaseFGLen
  
  @todo Incomplete documentation: PVM_AVAILABLE
   
  @ingroup PVM_PTB
*/
void PTB_VisuSetFGElementComment(const char * id, 
                                 const char * comment, 
                                 int        commentLen,
                                 int        stringLen);

/** Derive the VISU diffusion parameters for diffusion datasets.

  The VISU movie loop is divided into a a diffusion (@a ndiff elements) 
  and cycle (@a nrep element) loop. The parameter VISU element comments are 
  adapted for the diffusion loop. The parameter @c VisuAcqDiffusionBMatrix is
  set to the @c PVM_DwBMat diffusion b-matrix and made dependent to the 
  diffusion loop.
   
  @PVM_AVAILABLE
  20110101
  
  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  A diffusion method had to be acquired.

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_VisuDeriveDiffusionFrameGroup(PVM_DwNDiffExp, PVM_NRepetitions);
  @endcode
  
  @param ndiff  Number of diffusion scans.
  @param nrep   Number of repetitions.
  
  @return @c -1 on error, @c 0 for success.

  @ingroup PVM_PTB   
 */
int PTB_VisuDeriveDiffusionFrameGroup(int ndiff, int nrep);


/* gen/src/prg/pvm_toolboxes/PvPvmTools/geoObj.c */

/** Returns max length of a geometry object parameter name.

  This function returns the maximum length (including @c 0) of a parameter name used to handle
  a geometry object.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Length of parameter name represented as int

  @see @ref PTB_MaxGeoIdLength,
       @ref PTB_MaxGeoLabelLength
       
  @ingroup PVM_PTB
*/
int PTB_MaxGeoParnameLength(void);

/** Returns max length of a geometry object identifier.

  This function returns the maximum length (including @c 0) of a geometry object identifier.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Length geo object identifier string represented as int

  @see @ref PTB_MaxGeoParnameLength,
       @ref PTB_MaxGeoLabelLength
       
  @ingroup PVM_PTB
*/
int PTB_MaxGeoIdLength(void);

/** Returns max length of a geometry object axis lable length.

  This function returns the maximum length (including @c 0) of a geometry axis lable.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @return Length geo object lable represented as int

  @see @ref PTB_MaxGeoParnameLength, @ref PTB_MaxGeoIdLength,
       
       
  @ingroup PVM_PTB
*/
int PTB_MaxGeoLabelLength(void);


/** Registers a new geometry object.

  This function has to be used to register a geometry object that should be handled and
  displayed by the geometry editor.

  Legal values of arguments are expected and checked, possible error states are returned as
  nonzero return values. In case of illegal states, @c PVM_GeoObj remains unchanged and the
  geometry object is not handled by the geometry editor.

  For argument @a geo_order: @n
  In case of either an empty string, a @c NULL pointer, a string that does not specify a parameter
  name or that specifies a parameter that is not an @c int array, detailed information about the
  ordering of the subcuboids (i.e. slices in case of slice geometry) will not be displayed and
  changes of the order may not be done on geometry editor level.

  If the required geometry object is already registered with the same properties as specified
  by arguments the function returns @c 0 without any change. In case it is not registered, a new
  entry of @c PVM_GeoObj is created.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  - @c PVM_GeoObj
  - Parameter specified as argument @a obj_parname

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  - Illegal arguments (return values > @c 0):
    - Illegal string length of argument @a id or @c NULL pointer (return value @c 1)
    - Illegal string length of argument @a subid (return value @c 2)
    - Illegal @a obj_parname (No parameter name, wrong string length. This parameter has to be
      of type @c GEO_OBJECT and is mandatory (return value @c 4)
    - Illegal @a geo_parname (No parameter name, wrong string length. This parameter has to be
      of type @c GEO_CUBOID_PACK or @c GEO_PLANAR and is mandatory (return value @c 5)
    - Illegal @a upd_contr (No parameter name)  
  - Illegal state of @c PVM_GeoObj (return values < @c 0)
    - @c PVM_GeoObj has more than one entry of name @a obj_parname (return value @c -1)
    - @c PVM_GeoObj as an entry of name @a obj_parname, but the related parameter has no value
      (return value @c -3)
    - @c PVM_GeoObj as an entry of name @a obj_parname with different geometry object properties
      as specified by arguments (return value @c -4)
  
  @PVM_EXAMPLE
  @code
  const char *const label[3] = {"1;first pulse", "2;second pulse", "3;third pulse"};
  
  PTB_InsertGeoObject("VOXEL",
                      0,
                      GeoCuboidPackId,
                      Standard_GobjShape,
                      "PVM_VoxelGeoObj",
                      "PVM_VoxelGeoCub",
                      0,
                      label,
                      Yes);
  @endcode
  
  @param[in] id            String specifying the displayed geometry object (must not contain
                           prefix @c BRUKER_)
  @param     type          Enum specifying the object type (either @c GeoCuboidPackId or
                           @c GeoPlanarId)
  @param     shape         Enum specifying the object shape (either @c Standard_GobjShape,
                           @c Cylinder_In_GobjShape, @c Cylinder_Circ_GobjShape,
                           @c Ellipsoid_In_GobjShape, or @c Ellipsoid_Circ_GobjShape)
  @param[in] obj_parname   String specifying the parameter name that is used to store the geometry
                           object properties. The display name of this parameter appears in the
                           geometry editor.
  @param[in] geo_parname   String specifying the parameter name that is used to transfer the
                           geometry from geometry editor to methods and vice versa
  @param[in] geo_order     String specifying the parameter name that is used to specify the order
                           of subcuboids
  @param[in] labels        Labels used to identify each dimension in the geometry editor 
                           (@c NULL = use default labels). @n
                           Each label string consists of a short and a long description, separated by a semi-colon:
                           <c>\<s_desc\>;\<l_desc\></c>, where
                           - @c s_desc: short description (mandatory, max. two characters)
                           - @c l_desc: long description (optional)                       
  @param[in] show          Default visibility in geometry editor

  @return @c 0 in case of success; other error states see above

  @see @ref PTB_RemoveGeoObject, @ref PTB_SetGeoObjShape
  
  @todo Check whether the referenced parameters are unique

  @ingroup PVM_PTB
*/
int PTB_InsertGeoObject(const char *const id, 
                        GeoObjType type,
                        GeoObjShapeType   shape,
                        const char *const obj_parname,
                        const char *const geo_parname,
                        const char *const geo_order,
                        const char *const labels[3] = NULL,
                        YesNo             show = No);

/** Removes a geometry object.

  This function has to be used to unregister a geomety object that is handled and displayed by
  the geometry editor.

  Legal values of arguments are expected and checked. In case of illegal states, @c PVM_GeoObj
  remains unchanged and the geometry object is not handled by the geometry editor.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  - @c PVM_GeoObj
  - Parameter specified as argument @a obj_parname

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_RemoveGeoObject(""PVM_VoxelGeoCub");
  @endcode
  
  @param geo_parname    String specifying the parameter name that is used to transfer the
                        geometry from geometry editor to methods and vice versa
                        
  @see @ref PTB_InsertGeoObject, @ref PTB_SetGeoObjShape

  @ingroup PVM_PTB
*/
void PTB_RemoveGeoObject(const char *const geo_parname);

/** Changes the shape of a geometry object.

  This function has to be used to modify the way how a geometry object is displayed in the
  geometry editor. 

  Legal values of arguments are expected and checked. In case of illegal states, i.e. the
  specified parameter name is not a geometry object, nothing is changed and error codes are 
  returned (see below).

  For planar objects, the second argument is ignored and the shape is set to 
  @c Standard_GobjShape.

  @PVM_AVAILABLE
  20090101

  @PVM_PARS
  - The parameter name as specified by argument

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  For spiral imaging
  @code
  PTB_SetGeoObjShape("PVM_SliceGeoObj", Cylinder_In_GobjShape);
  @endcode
  For UTE
  @code
  PTB_SetGeoObjShape("PVM_SliceGeoObj", Ellipsoid_In_GobjShape);
  @endcode
 
  
  @param obj_parname    String specifying the parameter name that is used to store the geometry
                        object properties
  @param shape          Enum specifying the object shape with these possible values:
                        - @c Standard_GobjShape,
                        - @c Cylinder_In_GobjShape
                        - @c Cylinder_Circ_GobjShape
                        - @c Ellipsoid_In_GobjShape
                        - @c Ellipsoid_Circ_GobjShape

  @return 
  - Error code @c 1 is returned in case the string argument @a obj_parname is not a parameter
    name.
  - Error code @c 2 is returned in case the string argument @a obj_parname is not of type
    @c GEO_OBJECT.
  - Error code @c 0 is returned in case of no errors

  @see @ref PTB_InsertGeoObject, @ref PTB_RemoveGeoObject

  @ingroup PVM_PTB
*/
int PTB_SetGeoObjShape(const char *const obj_parname, 
                       GeoObjShapeType   shape);

/* gen/src/prg/pvm_toolboxes/PvPvmTools/PtbPpm.c */

/** Initialise ppm values of X-nuclei reference frequencies.

  @PVM_PARS
  - @c PVM_NucleiPpmRef

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @see @ref PTB_NucleiPpmWorkInit, @ref PTB_NucleiPpmRefSet,
       @ref PTB_NucleiPpmWorkSet, @ref PTB_NucleiPpmRefGet, @ref PTB_NucleiPpmWorkGet
         @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
void PTB_NucleiPpmRefInit(void);

/** Initialise ppm values of X-nuclei working frequencies.

  @PVM_PARS
  - @c PVM_NucleiPpmWork

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @see @ref PTB_NucleiPpmRefInit, @ref PTB_NucleiPpmRefSet,
       @ref PTB_NucleiPpmWorkSet, @ref PTB_NucleiPpmRefGet, @ref PTB_NucleiPpmWorkGet
       
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
void PTB_NucleiPpmWorkInit(void);

/** Set reference ppm value for a nucleus.

  Store @a ppmRef in the @c PVM_NucleiPpmRef array in the element
  corresponding to the nucleus; if it does not exist, store the 
  nucleus name and @a ppmRef at the first entry whose name is "none".

  @PVM_PARS
  - @c PVM_NucleiPpmRef

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE
  
  @PVM_EXAMPLE
  @code
  PTB_NucleiPpmRefSet(PVM_Nucleus1, PVM_FrqRefPpm[0]);
  @endcode
  
  @param[in] nucleusName Name of nucleus
  @param     ppmRef      Reference frequency [ppm]
  
  @return @c 0 = ok, else an error occurred (table is full or nucleus not found)
  
  @see @ref PTB_NucleiPpmRefInit, @ref PTB_NucleiPpmWorkInit,
       @ref PTB_NucleiPpmWorkSet, @ref PTB_NucleiPpmRefGet, @ref PTB_NucleiPpmWorkGet
       
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_NucleiPpmRefSet(const char *nucleusName,
                        double ppmRef);

/** Set working ppm value for a nucleus

  Store @a ppmWork in the @c PVM_NucleiPpmWork array in the element
  corresponding to the nucleus; if it does not exist, store the 
  nucleus name and @a ppmRef at the first entry whose name is "none".
  If all entries are used, set the last one.
   
  @PVM_PARS
  - @c PVM_NucleiPpmWork

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_NucleiPpmWorkSet(PVM_Nucleus1, PVM_FrqRefPpm[0] + PVM_FrqWorkOffsetPpm[0]);
  @endcode
  
  @param[in] nucleusName Name of nucleus
  @param     ppmWork     Working frequency [ppm]
  
  @return @c 0 = ok, else an error occurred
  
  @see @ref PTB_NucleiPpmRefInit, @ref PTB_NucleiPpmWorkInit, @ref PTB_NucleiPpmRefSet,
       @ref PTB_NucleiPpmRefGet, @ref PTB_NucleiPpmWorkGet
       
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_NucleiPpmWorkSet(const char *nucleusName, 
                         double ppmWork);

/** Get reference ppm value for a nucleus.   

  Find first entry corresponding to @a nucleusName in @c PVM_NucleiPpmTable
  and get reference and working ppm values from it.
   
  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_NucleiPpmRefGet(PVM_Nucleus1, &PVM_FrqRefPpm[0]);
  @endcode
  
  @param[in]  nucleusName Name of nucleus
  @param[out] ppmRef      Reference frequency [ppm]
  
  @see @ref PTB_NucleiPpmRefInit, @ref PTB_NucleiPpmWorkInit, @ref PTB_NucleiPpmRefSet,
       @ref PTB_NucleiPpmWorkSet, @ref PTB_NucleiPpmWorkGet
       
  @return @c 0 = ok, else nucleus was not found
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_NucleiPpmRefGet(const char *nucleusName, 
                        double *ppmRef);

/** Get working ppm value for a nucleus.   

  Find first entry corresponding to @a nucleusName in @c PVM_NucleiPpmTable
  and get reference and working ppm values from it.

  @PVM_PARS
  NONE

  @PVM_TBCALL
  NONE

  @PVM_RELCALL
  NONE

  @PVM_PRECOND
  NONE

  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_NucleiPpmWorkGet(PVM_Nucleus1, &PVM_FrqWorkPpm[0]);
  @endcode
  
  @param[in]  nucleusName Name of nucleus
  @param[out] ppmWork     Working frequency [ppm]
  
  @see @ref PTB_NucleiPpmRefInit, @ref PTB_NucleiPpmWorkInit, @ref PTB_NucleiPpmRefSet,
       @ref PTB_NucleiPpmWorkSet, @ref PTB_NucleiPpmRefGet
       
  @return @c 0 = ok, else nucleus was not found
  
  @todo Incomplete documentation: PVM_AVAILABLE

  @ingroup PVM_PTB
*/
int PTB_NucleiPpmWorkGet(const char *nucleusName, 
                         double *ppmWork);

/* gen/src/prg/pvm_toolboxes/PvPvmTools/ParamImport.c */

/** Inserts a transfer feature for parameter import.

  This function is used to enable the import and export of certain parameters for a method. 
  It inserts a feature into the list of transferable features. 
  
  @PVM_AVAILABLE
  20100101
  
  @PVM_PARS
  - @c PVM_ExportHandler
  - @c PVM_ImportHandler
  
  @PVM_TBCALL
  NONE
  
  @PVM_RELCALL
  NONE
  
  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  - A feature with the Id specified as argument already exists, but context and description are
    not identical.
    
  @PVM_EXAMPLE
  Offer local parameter class for transfer
  @code
  PTB_InsertTransferFeature("MyTaggingParID",
                            "", // empty context
                            "Tagging Parameters");
  @endcode
  
  @param id             Unique identifier of the transfer feature
                        - Use internal Id for Bruker defined transfer features
  @param context        Specifies special conditions for the data transfer
                        - May be empty
  @param description    Text in the import GUI
                        - Mandatory for user defined transfer features
                        - Ignored for Bruker defined transfer features

  @return @c Yes = transfer feature was inserted @n
          @c No = transfer feature already exists
  
  @see @ref PTB_RemoveTransferFeature, @ref PTB_SetImportList

  @ingroup PVM_PTB
*/
YesNo PTB_InsertTransferFeature(const char *const id,
                                const char *const context,
                                const char *const description);

/** Removes a transfer feature for parameter import.

  This function is used to disable the import and export of certain parameters for a method. 
  It removes a feature from the list of transferable features. 
  
  @PVM_AVAILABLE
  20100101
  
  @PVM_PARS
  - @c PVM_ExportHandler
  - @c PVM_ImportHandler
    
  @PVM_TBCALL
  NONE
  
  @PVM_RELCALL
  NONE
  
  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  NONE

  @PVM_EXAMPLE
  @code
  PTB_RemoveTransferFeature("MyTaggingParID");
  @endcode
  
  @param id    Unique identifier of the transfer feature
               - Use internal Id for Bruker defined transfer features

  @return @c Yes = transfer feature was removed @n
          @c No = transfer feature was not found
  
  @see @ref PTB_InsertTransferFeature, @ref PTB_SetImportList

  @ingroup PVM_PTB
*/
YesNo PTB_RemoveTransferFeature(const char *const id);

/** Prepares transfer feature for parameter import.

  This function is used to define the parameters that are transfered with a certain transfer
  feature. 
  
  @PVM_AVAILABLE
  20100101
  
  @PVM_PARS
  - @c PVM_ImportList
  
  @PVM_TBCALL
  NONE
  
  @PVM_RELCALL
  NONE
  
  @PVM_PRECOND
  NONE
  
  @PVM_ERROR
  - Illegal values in list content

  @PVM_EXAMPLE
  Prepare import of EPI parameter group
  @code
  PARIMPORT_LIST_TYPE myIlist[] =
  {
    {"PVM_Matrix",     "PVM_Matrix", "",               No},
    {"PVM_EffSWh",     "PVM_EffSWh", "",               No},
    {"EPI_Parameters", "",           "PVM_EpiHandler", No}
  };
    
  PTB_SetImportList(myIlist, 3);
  @endcode
  
  @param ilist    List of parameters to be transfered with the following elements per entry:
                  - Parameter name / parameter class used to retrieve parameter values
                    (mandatory)
                  - Parameter name used to store the source values in the destination dataset
                    (empty string is replaced by source name, ignored for parameter class)
                  - Handler parameter for the transfer
                    (relation called in the target parameter space after the actual transfer)
                  - @c No = call redirected relation, @c Yes = call default relation
  @param size     Number of entries in @a ilist

  @see @ref PTB_InsertTransferFeature, @ref PTB_RemoveTransferFeature

  @ingroup PVM_PTB
*/
void PTB_SetImportList(const     PARIMPORT_LIST_TYPE *ilist,
                       const int size);

/* gen/src/prg/pvm_toolboxes/PvPvmTools/recoDebug.c */

/** Prints reco network.
  
  Prints the text description of reconstruction network
  as it is given by the parameters @c RecoStageNodes and 
  @c RecoStageEdges to the standard output (Parx output).

  This function is the default relation of the parameter
  @c RecoDebug.
    
  @ingroup PVM_PTB_INT
*/
void PTB_RecoDebugRels(void);

#endif
#endif

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/
