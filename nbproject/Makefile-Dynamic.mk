#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=g++.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW_1-Windows
CND_DLIB_EXT=dll
CND_CONF=Dynamic
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ConfigFile.o \
	${OBJECTDIR}/src/Drawing.o \
	${OBJECTDIR}/src/Button.o \
	${OBJECTDIR}/src/Virtuals.o \
	${OBJECTDIR}/src/Frame.o \
	${OBJECTDIR}/src/Sprites.o \
	${OBJECTDIR}/src/Spinner.o \
	${OBJECTDIR}/src/Text.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/lib -L/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/lib/x86 -L/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/lib -L/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/lib/x86 -lSDL.dll -lSDLmain -lSDL_image -lcairo.dll -lSDL_ttf

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSprigen.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSprigen.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSprigen.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ConfigFile.o: src/ConfigFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConfigFile.o src/ConfigFile.cpp

${OBJECTDIR}/src/Drawing.o: src/Drawing.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Drawing.o src/Drawing.cpp

${OBJECTDIR}/src/Button.o: src/Button.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Button.o src/Button.cpp

${OBJECTDIR}/src/Virtuals.o: src/Virtuals.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Virtuals.o src/Virtuals.cpp

${OBJECTDIR}/src/Frame.o: src/Frame.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Frame.o src/Frame.cpp

${OBJECTDIR}/src/Sprites.o: src/Sprites.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sprites.o src/Sprites.cpp

${OBJECTDIR}/src/Spinner.o: src/Spinner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Spinner.o src/Spinner.cpp

${OBJECTDIR}/src/Text.o: src/Text.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/Cairo/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Text.o src/Text.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSprigen.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
