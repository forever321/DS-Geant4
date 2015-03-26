# $Id: GNUmakefile,v 1.2 2000/10/19 12:22:10 stanaka Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------
ifndef G4INSTALL
  G4INSTALL = ../../..
endif

name := twodets
G4TARGET := $(name)
G4EXLIB := true

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

########################### ROOT #################################
ifdef ROOTSYS
ifndef G4UI_USE_ROOT
CPPFLAGS += -DG4ANALYSIS_USE_ROOT $(shell $(ROOTSYS)/bin/root-config --cflags) -I/usr/local/gsl/include/
ROOTLIBS = $(shell $(ROOTSYS)/bin/root-config --nonew --glibs) -lMinuit 
ROOTLIBS := $(filter-out -lNew,$(ROOTLIBS))
#ROOTLIBS := $(filter-out -lThread,$(ROOTLIBS)) G. Soti
ROOTLIBS := $(filter-out -lpthread,$(ROOTLIBS)) 
LDLIBS += $(ROOTLIBS) -lgsl -lgslcblas -lm
endif
endif
######################### END_ROOT ################################

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

