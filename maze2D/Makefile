# Example Makefile for ArcEngine C++ Programming on Windows

#
# The PROGRAM macro defines the name of the program or project.  It
# allows the program name to be changed by editing in only one
# location
#

PROGRAM = app.exe

#
# Command line parameters: Edit these parameters so that you can
# easily run the sample by typing "nmake -f Makefile.Windows run".
#
# You will need to:
# (1) Describe parameters here. ex: IN_SHAPEFILE is the input shapefile
# (2) Define parameters below this comment box.
#       ex: IN_SHAPEFILE = /mycomp/data/shapefile.shp
# (3) Add the parameters to the run target at the end of this file
#       ex: ./$(PROGRAM) $(IN_SHAPEFILE)
#

#
# The INCLUDEDIRS macro contains a list of include directories
# to pass to the compiler so it can find necessary header files.
#
# The LIBDIRS macro contains a list of library directories
# to pass to the linker so it can find necessary libraries.
#
# The LIBS macro contains a list of libraries that the the
# executable must be linked against.
#

INCLUDEDIRS = 


LIBDIRS =


LIBS = 

#
# The CPPSOURCES macro contains a list of source files.
#
# The CPPOBJECTS macro converts the CPPSOURCES macro into a list
# of object files.
#
# The CPPFLAGS macro contains a list of options to be passed to
# the compiler.  Adding "-g" to this line will cause the compiler
# to add debugging information to the executable.
#
# The CPP macro defines the C++ compiler.
#
# The LINKFLAGS macro contains all of the library and library
# directory information to be passed to the linker.
#

CPPSOURCES = main.cpp Maze2D.cpp     # list of source files
CPPOBJECTS = $(CPPSOURCES:.cpp=.obj) # expands to list of object files
CPPOPT = /EHsc /D_CRT_SECURE_NO_DEPRECATE
CPPFLAGS = -DESRI_WINDOWS $(INCLUDEDIRS) $(CPPOPT)
CPP = cl.exe

LINKFLAGS = $(LIBDIRS) $(LIBS)

.PHONY: clean all run

#
# Default target: the first target is the default target.
# Just type "nmake -f Makefile.Windows" to build it.
#

all: $(PROGRAM)

#
# Link target: automatically builds its object dependencies before
# executing its link command.
#

$(PROGRAM): $(CPPOBJECTS)
	link.exe /out:$(PROGRAM) $(CPPOBJECTS) $(LINKFLAGS)

#
# Object targets: rules that define objects, their dependencies, and
# a list of commands for compilation.
#

basic_sample.obj: main.cpp
	$(CPP) $(CPPFLAGS) /c main.cpp

#
# Clean target: "nmake -f Makefile.Windows clean" to remove unwanted objects and executables.
#

clean:
	del $(CPPOBJECTS) $(PROGRAM)

#
# Run target: "nmake -f Makefile.Windows run" to execute the application
# You will need to add $(VARIABLE_NAME) for any command line parameters
# that you defined earlier in this file.
#

run:
	$(PROGRAM)
