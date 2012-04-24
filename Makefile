#####################################################################
#
#	MAKE SYSTEM FOR PEIKER ACUSTIC  DIGITAL SIGNAL PROCESSING LIBRARIES
#
#	This is a non recursive build concept based on the following recommendations:
#	
#	1.) Miller, P.A. (1998), Recursive Make Considered Harmful, AUUGN Journal of AUUG Inc., 19(1), pp. 14-25.
#	2.) van Bergen, Emile, Implementing non-recursive make
#
#	Adaptation for Peiker acustics 2008-10, Otto Linnemann
#	
#####################################################################


# target specific options for crosscompiler and overall flags eg.g position independent code generation
include configure.make


### Build flags for all targets
#
CF_ALL          += -Wall
LF_ALL          +=
LL_ALL          +=


#
# The generalized eigenvector beamformer (pa_gev_beamformer) module uses
# a fixpoint implementations of some Basic Linear Algebra Subprograms (BLAS).
# For further development of the signal processing library it can be helpful 
# to have an appropriate C-implementation of this library installed on your 
# system and integrated into the build process.
#
# This requires to have the archive libblas.a installed in your library path 
# and header file cblas.h in your header path.
#  
# On debian based Linux systems use the following command to install the 
# package:
# 
# sudo apt-get install refblas3-dev
#
# For integration of the reference BLAS implementation 
# (binding to Fortran legacy code) uncomment the following 
# line:

# LL_ALL += -lblas


#
# The GNU Scientific Library was considered for a foundation of
# linear algebra operations, too. After a more detailed analysis
# we consider this approach beeing not efficient enough for
# real time signal processing. Nevertheless some GSL functions
# can be helpful for development and testing. 
#
# For integration of the GNU Scientific Library  (GSL) 
# uncomment the following line:

# LL_ALL += -lgsl -lgslcblas


#
# Floating point math library, still needed for some initialisation
# functions

LL_ALL += -lm



COMP            = $(CC) $(CF_ALL) $(CF_TGT) -o $@ -c $<
LINK            = $(CC) $(LF_ALL) $(LF_TGT) -o $@ $^ $(LL_TGT) $(LL_ALL)
COMPLINK        = $(CC) $(CF_ALL) $(CF_TGT) $(LF_ALL) $(LF_TGT) -o $@ $< $(LL_TGT) $(LL_ALL)
ARCH			= $(AR) -r $@ $^ ; $(RANLIB) $@

### Standard parts
#
include Rules.mk
