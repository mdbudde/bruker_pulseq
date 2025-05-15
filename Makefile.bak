# -------------------------------------------------------------
# /pvVersions/linux_intel/Pv601/prog/parx/src/bruker_pulseq/Makefile
# 
# Copyright (c) 2001-2011
# Bruker BioSpin MRI GmbH
# D-76275 Ettlingen, Germany
#
# All Rights Reserved
#
# To copy the directory and compile the copy it is only
# necessary to change SRCDIR.
# -------------------------------------------------------------

# -------------------------------------------------------------
#  ParaVision Linux templates
# -------------------------------------------------------------

# -------------------------------------------------------------
#  ParaVision templates
# -------------------------------------------------------------

XWINSHLIBDIR = $(PROGDIR)/shlib
XWINSHLIBDIROPT = -L$(XWINSHLIBDIR)

THIRDPARTY_SHLIBDIR64 = $(PROGDIR)/shlib64

THIRDPARTY_SHLIBDIR = $(PROGDIR)/pvshlib
THIRDPARTY_SHLIBDIROPT = -L$(THIRDPARTY_SHLIBDIR)

XWINSHARELIBEXT = $(SHARELIBEXT)

PVSHLIBDIR = $(PROGDIR)/pvshlib

MAKEDEPEND	= makedepend

RMD		= rm -rf

SHARELIBBASEOPTS = -shared

PV_EXTRA_DEFINES =

PV_DEFINES = -D_REENTRANT -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

PV_ARCH_FLAG = -m32

PV_COMPILE_FLAGS = $(PV_ARCH_FLAG) -fPIC -rdynamic

LOCALBINDIR = $(LOCALROOT)/bin

# -------------------------------------------------------------
# Defaults for LAPACK / CLAPACK
# -------------------------------------------------------------

LAPACK_LIBRARIES = $(PVSHLIBDIR)/liblapack$(SHARELIBEXT) $(PVSHLIBDIR)/libblas$(SHARELIBEXT) $(SIMPLE_FORTRAN_LIBRARIES)

TOPSPIN_IMPORTLIBS = $(XWINSHLIBDIR)/editpar$(XWINSHARELIBEXT) $(XWINSHLIBDIR)/libacq$(XWINSHARELIBEXT)  $(XWINSHLIBDIR)/libPath$(XWINSHARELIBEXT) $(XWINSHLIBDIR)/libShapeIO$(XWINSHARELIBEXT) $(XWINSHLIBDIR)/libap$(XWINSHARELIBEXT) $(XWINSHLIBDIR)/libcb$(XWINSHARELIBEXT) $(XWINSHLIBDIR)/uni$(XWINSHARELIBEXT) $(XWINSHLIBDIR)/util$(XWINSHARELIBEXT)

TOPSPIN_PROGLIBS =

# -------------------------------------------------------------
# Define TCL definitions
# -------------------------------------------------------------

# -------------------------------------------------------------
# $Source: /bscl/CvsTree/bscl/gen/config/linux_intel.cf,v $
#
# Copyright (c) 2000
# BRUKER BIOSPIN GMBH
# D-76287 Rheinstetten, Germany
#
# All Rights Reserved
#
# $Id: linux_intel.cf,v 1.79.4.4 2012/03/12 06:06:03 pvadm Exp $
# -------------------------------------------------------------

# -------------------------------------------------------------
# $Source: /bscl/CvsTree/bscl/gen/config/gcc.def,v $
#
# Copyright (c) 2000
# BRUKER BIOSPIN GMBH
# D-76287 Rheinstetten, Germany
#
# All Rights Reserved
#
# $Id: gcc.def,v 1.105.4.3 2012/07/16 05:08:02 pvadm Exp $
# -------------------------------------------------------------

# -------------------------------------------------------------
#
# $Source: /bscl/CvsTree/bscl/gen/config/CPlusPlus.tmpl,v $
#
# Copyright (c) 1997
# BRUKER BIOSPIN GMBH
# D-76287 Rheinstetten, Germany
#
# All Rights Reserved
#
# $Id: CPlusPlus.tmpl,v 1.19 2005/09/15 08:59:28 wem Exp $
#
# Defaults for various generic parameters for C++ programs.
# You may overwrite this defaults in either dir.def, site.def
# or linux_intel.cf
# -------------------------------------------------------------

CPLUSPLUS		= $(EXECDISKUNIT)/gnu/bin/c++ -B$(EXECDISKUNIT)/gnu/lib/gcc-lib/

STD_PLUSPLUS_LIBRARIES	= -ldl -lrt -lpthread $(EXTRA_STDLIBS)
ALL_PLUSPLUS_LIBRARIES	= $(LIBRARIES) $(EXTRA_LIBRARIES) $(STD_PLUSPLUS_LIBRARIES)

STD_PLUSPLUS_LIBPATH 	=
ALL_PLUSPLUS_LIBPATH	= $(LIBPATH) $(STD_PLUSPLUS_LIBPATH)

STD_PLUSPLUS_INCPATH 	= $(STD_INCPATH)
ALL_PLUSPLUS_INCPATH	= $(INCPATH) $(EXTRA_INCPATH) $(STD_PLUSPLUS_INCPATH)

STATICSTDCPLUSPLUS	= -static-libgcc -static-libstdc++

SHAREDSTDCPLUSPLUS	= libgcc_s.so.1 libstdc++.so.6

STD_PLUSPLUS_DEFINES 	= $(PV_EXTRA_DEFINES) $(PV_DEFINES) $(SHARED_DEFINES)
ALL_PLUSPLUS_DEFINES	= $(OS_DEFINES) $(DEFINES) $(EXTRA_DEFINES) $(DLL_DEFINES) $(STD_PLUSPLUS_DEFINES)

CORBA_SOURCE_DEFINES	=

CPLUSPLUSDEBUGFLAGS	= -O3 -DNDEBUG $(LINKTIME_OPTIMIZE)

CPLUSPLUSOPTIONS	= $(PV_COMPILE_FLAGS) -Wall -Wextra -Wpointer-arith -Wsign-compare -Wwrite-strings -Wmissing-declarations -Woverloaded-virtual -Wundef -Wdisabled-optimization -Wunused -Wlogical-op -Wuninitialized -Winit-self -std=gnu++98 -Wcast-qual -Wcast-align -Wno-variadic-macros -fimplicit-templates -fnon-call-exceptions -fno-common $(COMPILE_OPTIONS)
CPLUSPLUSLDOPTIONS	= $(PV_COMPILE_FLAGS) -fno-common -fexceptions $(LINKTIME_OPTIMIZE) $(LINK_OPTIONS) $(CPLUSPLUSDEBUGFLAGS)

CPLUSPLUSFLAGS		= $(CPLUSPLUSDEBUGFLAGS) $(CPLUSPLUSOPTIONS) $(ALL_PLUSPLUS_INCPATH) $(ALL_PLUSPLUS_DEFINES)

CPLUSPLUSLDFLAGS	= $(CPLUSPLUSLDOPTIONS) $(ALL_PLUSPLUS_LIBPATH)

PPSUFFIX		= .cc

.SUFFIXES:            # Delete the default suffixes

.PHONY: clean cproto depend install all

IMAKEFILE_DIR = $(SRCDIR)

.PHONY: Makefile64
Makefile64::

all::

# -------------------------------------------------------------
# C++ rules
# -------------------------------------------------------------

# -------------------------------------------------------------
# platform-specific configuration parameters - edit
# linux_intel.cf to change
# -------------------------------------------------------------

# -------------------------------------------------------------
# $Source: /bscl/CvsTree/bscl/gen/config/linux_intel.cf,v $
#
# Copyright (c) 2000
# BRUKER BIOSPIN GMBH
# D-76287 Rheinstetten, Germany
#
# All Rights Reserved
#
# $Id: linux_intel.cf,v 1.79.4.4 2012/03/12 06:06:03 pvadm Exp $
# -------------------------------------------------------------

# -------------------------------------------------------------
# $Source: /bscl/CvsTree/bscl/gen/config/gcc.def,v $
#
# Copyright (c) 2000
# BRUKER BIOSPIN GMBH
# D-76287 Rheinstetten, Germany
#
# All Rights Reserved
#
# $Id: gcc.def,v 1.105.4.3 2012/07/16 05:08:02 pvadm Exp $
# -------------------------------------------------------------

# -------------------------------------------------------------
# Defaults for various generic parameters defined in
# "$(EXECDISKUNIT)/gen/config/ParxExport.tmpl". You may overwrite this defaults in either
# dir.def, site.def or linux_intel.cf
# -------------------------------------------------------------

AWK		= awk

BASENAME	= basename

BASH		= bash

CAT		= cat

CC		= $(EXECDISKUNIT)/gnu/bin/gcc -B$(EXECDISKUNIT)/gnu/lib/gcc-lib/

CHMOD		= chmod

CKSUM		= cksum

CMP		= cmp

CP		= cp

CP_R		= cp -r

CPASC		= cp

CUT		= cut

DATE		= date

DIFF		= diff

ECHO		= /bin/echo -e

EXECSTACK	= execstack

FIND		= find

GREP		= grep

GTAR		= $(ARCH_LOCAL)/tar-1.26/bin/tar

HEAD		= head

LN		= ln

LS		= ls

M4		= m4

MAKE		= make

MAKEDEPEND	= makedepend

MKDIR		= mkdir -p

MV		= mv

PERL		= perl

RCP		= rcp

SCP		= scp

RM		= rm -f

RMDIR		= rm -rf

SED		= sed

SHARELIBCMD	=

SHELL		= sh

TAR		= tar

TOUCH		= touch

UNAME		= uname

WHOAMI		= whoami

NOOP		= true

STRIP		= $(CC_ROOT)/bin/strip

SORT		= sort -u

XXD		= xxd

DOS2UNIX	= dos2unix

SSH		= ssh

COMM		= comm

ZIPCMD		= gzip -f

UNZIPCMD	= gunzip -f

TOP		= .
CURRENT_DIR	= .

RM_CMD		= $(RM) *.CKP *.ln *.BAK *.bak *.o core errs ,* *~ *.a *.lib .emacs_* tags TAGS make.log MakeOut

APP_SUBSYSTEM	=

STD_LIBRARIES	= -ldl -lrt -lpthread $(EXTRA_STDLIBS)
ALL_LIBRARIES	= $(LIBRARIES) $(EXTRA_LIBRARIES) $(STD_LIBRARIES)

STD_LIBPATH	=
ALL_LIBPATH	= $(LIBPATH) $(STD_LIBPATH)

STD_INCPATH	= -I $(EXECDISKUNIT)/prog/include
ALL_INCPATH	= $(INCPATH) $(EXTRA_INCPATH) $(STD_INCPATH)

STD_DEFINES	= $(PV_EXTRA_DEFINES) $(PV_DEFINES) $(SHARED_DEFINES)
OS_DEFINES	= -DLINUX_INTEL
DLL_DEFINES	=
ALL_DEFINES	= $(OS_DEFINES) $(DEFINES) $(EXTRA_DEFINES) $(DLL_DEFINES) $(STD_DEFINES)

CDEBUGFLAGS	= -O3 -DNDEBUG $(LINKTIME_OPTIMIZE)

CCOPTIONS	= $(PV_COMPILE_FLAGS) -Wall -Wextra  -Wpointer-arith -Wsign-compare -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Winline -Wundef -Wunused -Wdisabled-optimization -Wlogical-op -pedantic -Wuninitialized -Winit-self -std=gnu99 -Wconversion -Wcast-qual -Wcast-align -fexceptions -fno-common $(COMPILE_OPTIONS)

CCLDOPTIONS	= $(PV_COMPILE_FLAGS) -fno-common -fexceptions $(LINKTIME_OPTIMIZE) $(LINK_OPTIONS)

LDDEBUGFLAGS	=

LDOPTIONS	=

DLLLDOPTIONS	=

CFLAGS		= $(CDEBUGFLAGS) $(CCOPTIONS) $(ALL_INCPATH) $(ALL_DEFINES)
CCLDFLAGS	= $(CDEBUGFLAGS) $(CCOPTIONS) $(CCLDOPTIONS) $(ALL_LIBPATH)

EXECEXT		=

OBJEXT		= .o

STATICLIBEXT	= .a

STATICCRTLIBEXT	= .a

DYNAMICLIBEXT	= .so

ASMEXT		= .asm

ROMEXT		= .rom

ZIPEXT		= .gz

SHARELIBEXT	= .so

CPROTO		= $(EXECDISKUNIT)/prog/bin/cproto
CPROTOOPTIONS	= -E"$(CC) -E" -f2
CPROTO_DEFINES	= -DCPROTO
CPROTOFLAGS	= $(CPROTOOPTIONS) $(CPROTO_DEFINES) $(ALL_DEFINES) $(ALL_INCPATH)

MATH_LIBRARIES	= -lm

PTHREAD_LIBRARIES= -lpthread

# -------------------------------------------------------------
#
# $Source: /bscl/CvsTree/bscl/gen/config/sca.rules,v $
#
# Copyright (c) 2007
# BRUKER BIOSPIN GMBH
# D-76287 Rheinstetten, Germany
#
# All Rights Reserved
#
# $Id: sca.rules,v 1.15 2010/05/21 13:15:18 jgo Exp $
# -------------------------------------------------------------

# -------------------------------------------------------------
# rules for static code analysis:
# -------------------------------------------------------------

# -------------------------------------------------------------
# $Source: /bscl/CvsTree/bscl/gen/config/Standard.tmpl,v $
#
# Copyright (c) 1995
# BRUKER BIOSPIN GMBH
# D-76287 Rheinstetten, Germany
#
# All Rights Reserved
#
# $Id: Standard.tmpl,v 1.27 2009/12/07 07:16:54 wem Exp $
# -------------------------------------------------------------

# -------------------------------------------------------------
# Standard build parameters
# -------------------------------------------------------------

EXECDISKUNIT	= /opt/PV6.0.1

PROGDIR		= $(EXECDISKUNIT)/prog

STANDALONEDIR	= $(EXECDISKUNIT)/prog/bin

SHLIBDIR	= $(PROGDIR)/pvshlib

DLLDIR		= $(PROGDIR)/pvshlib

# For compatibilty to old Imakefiles - do not use !

PROTOHEADERDIR	= $(EXECDISKUNIT)/prog/include/proto

TMPDIR		= /tmp

DEPENDFLAGS	= -DMAKEDEPEND

# -------------------------------------------------------------
# Standard rule set
# -------------------------------------------------------------

DEPEND_START = \# DO NOT DELETE THIS LINE -- make depend depends on it

# -------------------------------------------------------------
# Start of Imakefile
# -------------------------------------------------------------

PARCOMP_OPTS     =
PARCOMP_DEFINES  = -DInParxOvl
PARCOMP_FLAGS	 = $(PARX_EXTRA_FLAGS) $(ALL_INCPATH) $(DEFINES) $(PARCOMP_DEFINES) $(PARCOMP_OPTS) $(PARCOMP_DEBUG)
PARCOMP_DEBUG    =
PARCOMP	         = $(EXECDISKUNIT)/prog/bin/scripts/methcomp

PARX_OVT_FLAGS	 =
PARX_OVE_FLAGS	 = -P $(PULPROG) $(PULPROG_INC)

PARX_OVL_LIBPATH = -L$(EXECDISKUNIT)/gnu/lib -L$(SHLIBDIR) -L$(XWINSHLIBDIR)
PARX_OVL_LIBS	 = $(LIBS)
PARX_OVL_LIBRARIES = $(LIBRARIES) $(STD_LIBRARIES)
PARX_OVL_CPP     =
PARX_OVL_LD      = $(EXECDISKUNIT)/gnu/bin/c++ -B$(EXECDISKUNIT)/gnu/lib/gcc-lib/
PARX_OVL_EXT     = .so
PARX_OVL_AR      = $(AR)
PARX_OVL_ARFLAGS =
PARX_TK_EXT      = $(SHARELIBEXT)

PARX_PP_STD_INCL = -p $(PPG_DIR) -p $(EXP_LISTS_DIR)/pp -p $(EXP_LISTS_DIR)/pp.dtomo -p $(EXP_LISTS_DIR)/pp.dexam

METHODS_DIR	 = $(EXECDISKUNIT)/prog/curdir/$(USER)/ParaVision/methods

EXP_LISTS_DIR    = $(EXECDISKUNIT)/exp/stan/nmr/lists
PPG_DIR	 = $(EXECDISKUNIT)/prog/curdir/$(USER)/ParaVision/exp/lists/pp
SEQ_DIR	 = $(EXECDISKUNIT)/prog/curdir/$(USER)/ParaVision/exp/lists/seq
EXTRA_DEFINES    = $(PARCOMP_DEFINES)

.SILENT:

all::
showppg ::
	@if [ "$(PULPROG)" != "none" ]; then echo $(notdir $PULPROG); fi

OVERLAY		= bruker_pulseq
PULPROG		= none
PULPROG_INC	=

SRCDIR		= $(EXECDISKUNIT)/prog/curdir/$(USER)/ParaVision/methods/src/bruker_pulseq

INCPATH		= -I.

RELOBJS		=	\
			initMeth$(OBJEXT) \
			loadMeth$(OBJEXT) \
			parsRelations$(OBJEXT) \
			BaseLevelRelations$(OBJEXT) \
			RecoRelations$(OBJEXT) \
			backbone$(OBJEXT) \
			deriveVisu$(OBJEXT) \
			pulseqRelations$(OBJEXT)
			
			

OBJS		= 		  $(OVERLAY)$(OBJEXT) 		  $(RELOBJS)

SRCS		= $(addprefix $(SRCDIR)/, $(addsuffix  .c,  $(basename $(notdir $(OBJS)))))

RELSRCS		= $(addprefix $(SRCDIR)/, $(addsuffix  .c,  $(basename $(notdir $(RELOBJS)))))

CPPRELOBJS = pulseq_wrapper$(OBJEXT) ExternalSequence$(OBJEXT) md5$(OBJEXT)
CPPRELSRCS = $(addprefix $(SRCDIR)/, $(addsuffix  .cpp,  $(basename $(notdir $(CPPRELOBJS)))))


LIBS	        = 		  $(SHLIBDIR)/libPvUtil$(SHARELIBEXT) 		  $(SHLIBDIR)/libPvUtilTools$(SHARELIBEXT)                   $(SHLIBDIR)/libPvCfgTools$(SHARELIBEXT) 		  $(SHLIBDIR)/libPvAcqTools$(SHARELIBEXT) 		  $(SHLIBDIR)/libPvPvmTools$(SHARELIBEXT) 		  $(SHLIBDIR)/libPvMrTools$(SHARELIBEXT) 		  $(SHLIBDIR)/libPvGeoTools$(SHARELIBEXT) 		  $(SHLIBDIR)/libPvSeqTools$(SHARELIBEXT) 		  $(SHLIBDIR)/libPvPvmTools$(SHARELIBEXT)                   $(SHLIBDIR)/libPvOvlTools$(SHARELIBEXT) 		  $(SHLIBDIR)/libParxRels$(SHARELIBEXT)       $(SHLIBDIR)/libPvPath$(SHARELIBEXT)

LIBRARIES	= 		  -lm

all::	$(OVERLAY)$(PARX_OVL_EXT)

install:: $(OVERLAY)$(PARX_OVL_EXT)
	@$(ECHO) Install $(METHODS_DIR)/$(OVERLAY)$(PARX_OVL_EXT)
	if [ ! -d $(METHODS_DIR) ]; then $(MKDIR) $(METHODS_DIR) ; fi
	$(RM) $(METHODS_DIR)/$(OVERLAY)$(PARX_OVL_EXT)
	$(CP) $(OVERLAY)$(PARX_OVL_EXT) $(METHODS_DIR)

clean::
	$(RM) $(OVERLAY)$(PARX_OVL_EXT)

instclean::
	$(RM) $(METHODS_DIR)/$(OVERLAY)$(PARX_OVL_EXT)

instlist::
	@echo $(METHODS_DIR)/$(OVERLAY)$(PARX_OVL_EXT)


$(CPPRELOBJS):
	@$(ECHO) Compile $(SRCDIR)/$(@:$(OBJEXT)=.cpp)
	$(CPLUSPLUS) -c $(SRCDIR)/$(@:%.o=%.cpp) -o $@ $(CPLUSPLUSFLAGS)

	
$(OVERLAY)$(PARX_OVL_EXT): $(OBJS) $(CPPRELOBJS) $(PARX_OVL_LIBS)
	@$(ECHO) Link $(OVERLAY)$(PARX_OVL_EXT)
	$(RM) $(OVERLAY)$(PARX_OVL_EXT)
	$(PARX_OVL_LD) -shared -Wl,-no-undefined,-soname,$(OVERLAY)$(PARX_OVL_EXT) \
	   $(CPLUSPLUSLDOPTIONS) $(OBJS) $(CPPRELOBJS) \
	   $(PARX_OVL_LIBPATH)  $(PARX_OVL_LIBS) \
	   $(PARX_OVL_LIBRARIES) -o $(OVERLAY)$(PARX_OVL_EXT)

DEP_SRCS += $(SRCS) $(CPPRELSRCS)
DEP_LINES += " "
depend::
	$(RM) Makefile.bak
	$(MV) Makefile Makefile.bak
	@$(SED) '/^$(DEPEND_START)/,$$d' < Makefile.bak > Makefile
	@$(ECHO) "$(DEPEND_START)" >> Makefile
	$(CPLUSPLUS) -MM $(CPLUSPLUSFLAGS) $(DEPENDFLAGS) $(DEP_SRCS) >> Makefile
	for line in $(DEP_LINES); do echo $$line >> Makefile; done

	
$(RELOBJS): $(OVERLAY)$(OBJEXT)
	@$(ECHO) Compile $(SRCDIR)/$(@:$(OBJEXT)=.c)
	$(PARCOMP) $(SRCDIR)/$(OVERLAY).c $(PARCOMP_FLAGS) -r $(SRCDIR)/$(@:$(OBJEXT)=.c)

$(OVERLAY)$(OBJEXT):
	@$(ECHO) Compile $(SRCDIR)/$(OVERLAY).c
	$(PARCOMP) $(SRCDIR)/$(OVERLAY).c   $(PARX_OVE_FLAGS) $(PARCOMP_FLAGS)

install::
	if [ ! -d $(METHODS_DIR) ]; then $(MKDIR) $(METHODS_DIR) ; fi
	@if [ -f $(SRCDIR)/$(OVERLAY).xml ]; then \
	   $(ECHO) Install $(METHODS_DIR)/$(OVERLAY).xml; \
	   $(RM) $(METHODS_DIR)/$(OVERLAY).xml ; \
	   $(CPASC) $(SRCDIR)/$(OVERLAY).xml $(METHODS_DIR)/$(OVERLAY).xml; \
	fi

instclean::
	$(RM) $(METHODS_DIR)/$(OVERLAY).xml

instlist::
	@echo $(METHODS_DIR)/$(OVERLAY).xml

installppg :: $(PPG_DIR)/$(notdir $(SRCDIR)/$(OVERLAY).ppg)
$(PPG_DIR)/$(notdir $(SRCDIR)/$(OVERLAY).ppg) : $(SRCDIR)/$(OVERLAY).ppg
	   if [ ! -d $(PPG_DIR) ]; then $(MKDIR) $(PPG_DIR) ; fi
	   $(RM) $(PPG_DIR)/$(notdir $(SRCDIR)/$(OVERLAY).ppg)
	   $(CP) $(SRCDIR)/$(OVERLAY).ppg $(PPG_DIR)/$(notdir $(SRCDIR)/$(OVERLAY).ppg)

instclean::
	$(RM) $(PPG_DIR)/$(notdir $(SRCDIR)/$(OVERLAY).ppg)

instlist::
	@echo $(PPG_DIR)/$(notdir $(SRCDIR)/$(OVERLAY).ppg)


install :: 
	if [ ! -d $(SEQ_DIR) ]; then $(MKDIR) $(SEQ_DIR) ; fi
	@if [ -f $(SRCDIR)/gre.seq ]; then \
	   $(ECHO) Install $(SEQ_DIR)/greseq; \
	   $(RM) $(SEQ_DIR)/greseq ; \
	   $(CPASC) $(SRCDIR)/gre.seq $(SEQ_DIR)/greseq; \
	fi

instclean::
	$(RM) $(SEQ_DIR)/greseq

instlist::
	@echo $(SEQ_DIR)/greseq

showppg ::
	@echo $(notdir $(SRCDIR)/$(OVERLAY).ppg)

cproto::
	-if [ ! -r relProtos_p.h ]; then			  		\
		$(TOUCH) relProtos_p.h;				\
	fi
	$(CPROTO) $(CPROTOFLAGS) -o relProtos.new -O relProtos.err $(RELSRCS)
	cat relProtos.err
	file=relProtos.err; test -z "`cat $$file`"
	$(CMP) -s relProtos relProtos.new || \
	{ \
		$(ECHO) "Install new prototype file"; \
		$(RM) relProtos_p.h; \
		$(MV) relProtos.new relProtos_p.h; \
	}
	$(RM) relProtos.new
	$(RM) relProtos.err

# -------------------------------------------------------------
# Common rules for all Makefiles - do not edit
# -------------------------------------------------------------

emptyrule::

dvd::

clean::
	$(RM_CMD)

# -------------------------------------------------------------
# Empty rules for directories that do not have SUBDIRS
# -------------------------------------------------------------

depend::

Makefiles::

all::

test::

sca::

install::

cproto::

dll::

idl::

docu::

# -------------------------------------------------------------
# Dependencies generated by makedepend
# -------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it
bruker_pulseq.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/bruker_pulseq.c \
 /opt/PV6.0.1/prog/include/bruktyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/Visu/VisuTypes.h \
 /opt/PV6.0.1/prog/include/Visu/VisuDefines.h \
 /opt/PV6.0.1/prog/include/generated/VisuIds.h \
 /opt/PV6.0.1/prog/include/proto/acq_extern.h \
 /opt/PV6.0.1/prog/include/proto/subj_extern.h \
 /opt/PV6.0.1/prog/include/proto/pvm_extern.h \
 /opt/PV6.0.1/prog/include/proto/visu_extern.h \
 /opt/PV6.0.1/prog/include/methodFormat.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsDefinition.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseqPars.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseqTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/callbackDefs.h \
 /opt/PV6.0.1/prog/include/methodClassDefs.h \
 /opt/PV6.0.1/prog/include/digitizerClassDefs.h \
 /opt/PV6.0.1/prog/include/epiClassDefs.h \
 /opt/PV6.0.1/prog/include/SpiralCls.h \
 /opt/PV6.0.1/prog/include/TrajectoryCls.h \
 /opt/PV6.0.1/prog/include/diffusionClassDefs.h \
 /opt/PV6.0.1/prog/include/modulesClassDefs.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsLayout.h
initMeth.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/initMeth.c \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h
loadMeth.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/loadMeth.c \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h
parsRelations.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsRelations.c \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h
BaseLevelRelations.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/BaseLevelRelations.c \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h
RecoRelations.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/RecoRelations.c \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h
backbone.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/backbone.c \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h
deriveVisu.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/deriveVisu.c \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h \
 /opt/PV6.0.1/prog/include/Visu/VisuTypes.h \
 /opt/PV6.0.1/prog/include/Visu/VisuDefines.h \
 /opt/PV6.0.1/prog/include/generated/VisuIds.h
pulseqRelations.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseqRelations.c \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/method.h \
 /opt/PV6.0.1/prog/include/pvmachine.h \
 /opt/PV6.0.1/prog/include/machine.h /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/PvSystem.h \
 /opt/PV6.0.1/prog/include/brukdef.h /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/Parx/Parx.h \
 /opt/PV6.0.1/prog/include/Parx/publicTypes.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/Parx/libParxRels.h \
 /opt/PV6.0.1/prog/include/Parx/ovlinterface.h \
 /opt/PV6.0.1/prog/include/Parx/pardef.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvUtil/perfhash.h \
 /opt/PV6.0.1/prog/include/ta_config.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/debugdef.h \
 /opt/PV6.0.1/prog/include/lib/libPvPath.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/gradient_ramp_typ.h \
 /opt/PV6.0.1/prog/include/acqumtyp.h /opt/PV6.0.1/prog/include/acqutyp.h \
 /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/Reco/RecoStageTyp.h \
 /opt/PV6.0.1/prog/include/subjtyp.h \
 /opt/PV6.0.1/prog/include/generated/ParxDefs.h \
 /opt/PV6.0.1/prog/include/methodTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/publicPvmTypes.h \
 /opt/PV6.0.1/prog/include/Parx/Dynenum.h \
 /opt/PV6.0.1/prog/include/lib/PvSysinfoClient_state.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/bruktyp.h \
 /opt/PV6.0.1/prog/include/PvUtil/TimeDefs.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/generated/DataPath.h \
 /opt/PV6.0.1/prog/include/generated/KeyUids.h \
 /opt/PV6.0.1/prog/include/PvCfg/ResultParsType.h \
 /opt/PV6.0.1/prog/include/adjManagerDefs.h \
 /opt/PV6.0.1/prog/include/PvmTypes/geotyp.h \
 /opt/PV6.0.1/prog/include/pvidl.h \
 /opt/PV6.0.1/prog/include/generated/GeoObjIds.h \
 /opt/PV6.0.1/prog/include/PvmTypes/ReportTypes.h \
 /opt/PV6.0.1/prog/include/generated/ParImport.h \
 /opt/PV6.0.1/prog/include/PvmTypes/wobbleTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/epiTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/TrajectoryTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/internalPvmTypes.h \
 /opt/PV6.0.1/prog/include/PvmTypes/SpiralTypesInternal.h \
 /opt/PV6.0.1/prog/include/PVMTools.h /opt/PV6.0.1/prog/include/recotyp.h \
 /opt/PV6.0.1/prog/include/PvUtilTools.h \
 /opt/PV6.0.1/prog/include/PvAcqTools.h \
 /opt/PV6.0.1/prog/include/PvCfgTools.h \
 /opt/PV6.0.1/prog/include/PvCfg/PvCfg.h \
 /opt/PV6.0.1/prog/include/PvGeoTools.h \
 /opt/PV6.0.1/prog/include/PvMrTools.h \
 /opt/PV6.0.1/prog/include/PvPvmTools.h \
 /opt/PV6.0.1/prog/include/adjManagerTypes.h \
 /opt/PV6.0.1/prog/include/PvSeqTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/RecoTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/VisuTools.h \
 /opt/PV6.0.1/prog/include/ovl_toolbox/Utils.h \
 /opt/PV6.0.1/prog/include/PvUtil/PvUtil.h \
 /opt/PV6.0.1/prog/include/machine.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/relProtos_p.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseqTypes.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseq_wrapper.h
pulseq_wrapper.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseq_wrapper.cpp \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/ExternalSequence.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseq_wrapper.h
ExternalSequence.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/ExternalSequence.cpp \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/ExternalSequence.h \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/md5.h
md5.o: \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/md5.cpp \
 /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/md5.h

