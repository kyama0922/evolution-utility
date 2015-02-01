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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1360923845/evolution_binary_search_collection.o \
	${OBJECTDIR}/_ext/1360923845/evolution_collection.o \
	${OBJECTDIR}/_ext/761014165/evolution_zip_loader.o \
	${OBJECTDIR}/_ext/1419175185/adler32.o \
	${OBJECTDIR}/_ext/1419175185/compress.o \
	${OBJECTDIR}/_ext/1419175185/crc32.o \
	${OBJECTDIR}/_ext/1419175185/deflate.o \
	${OBJECTDIR}/_ext/1419175185/gzclose.o \
	${OBJECTDIR}/_ext/1419175185/gzlib.o \
	${OBJECTDIR}/_ext/1419175185/gzread.o \
	${OBJECTDIR}/_ext/1419175185/gzwrite.o \
	${OBJECTDIR}/_ext/1419175185/infback.o \
	${OBJECTDIR}/_ext/1419175185/inffast.o \
	${OBJECTDIR}/_ext/1419175185/inflate.o \
	${OBJECTDIR}/_ext/1419175185/inftrees.o \
	${OBJECTDIR}/_ext/1419175185/trees.o \
	${OBJECTDIR}/_ext/1419175185/uncompr.o \
	${OBJECTDIR}/_ext/1419175185/zutil.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_array.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_boolean.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_null.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_number.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_object.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_root.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_serialize.o \
	${OBJECTDIR}/_ext/760885289/evolution_json_string.o \
	${OBJECTDIR}/_ext/760813065/evolution_math_utility.o \
	${OBJECTDIR}/_ext/760813065/evolution_matrix.o \
	${OBJECTDIR}/_ext/760813065/evolution_quaternion.o \
	${OBJECTDIR}/_ext/760813065/evolution_vector2.o \
	${OBJECTDIR}/_ext/760813065/evolution_vector3.o \
	${OBJECTDIR}/_ext/760813065/evolution_vector4.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-utility.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-utility.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-utility.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-utility.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-utility.a

${OBJECTDIR}/_ext/1360923845/evolution_binary_search_collection.o: ../etc/evolution_binary_search_collection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360923845
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360923845/evolution_binary_search_collection.o ../etc/evolution_binary_search_collection.cpp

${OBJECTDIR}/_ext/1360923845/evolution_collection.o: ../etc/evolution_collection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360923845
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360923845/evolution_collection.o ../etc/evolution_collection.cpp

${OBJECTDIR}/_ext/761014165/evolution_zip_loader.o: ../file/evolution_zip_loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/761014165/evolution_zip_loader.o ../file/evolution_zip_loader.cpp

${OBJECTDIR}/_ext/1419175185/adler32.o: ../file/zlib/adler32.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/adler32.o ../file/zlib/adler32.c

${OBJECTDIR}/_ext/1419175185/compress.o: ../file/zlib/compress.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/compress.o ../file/zlib/compress.c

${OBJECTDIR}/_ext/1419175185/crc32.o: ../file/zlib/crc32.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/crc32.o ../file/zlib/crc32.c

${OBJECTDIR}/_ext/1419175185/deflate.o: ../file/zlib/deflate.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/deflate.o ../file/zlib/deflate.c

${OBJECTDIR}/_ext/1419175185/gzclose.o: ../file/zlib/gzclose.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/gzclose.o ../file/zlib/gzclose.c

${OBJECTDIR}/_ext/1419175185/gzlib.o: ../file/zlib/gzlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/gzlib.o ../file/zlib/gzlib.c

${OBJECTDIR}/_ext/1419175185/gzread.o: ../file/zlib/gzread.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/gzread.o ../file/zlib/gzread.c

${OBJECTDIR}/_ext/1419175185/gzwrite.o: ../file/zlib/gzwrite.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/gzwrite.o ../file/zlib/gzwrite.c

${OBJECTDIR}/_ext/1419175185/infback.o: ../file/zlib/infback.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/infback.o ../file/zlib/infback.c

${OBJECTDIR}/_ext/1419175185/inffast.o: ../file/zlib/inffast.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/inffast.o ../file/zlib/inffast.c

${OBJECTDIR}/_ext/1419175185/inflate.o: ../file/zlib/inflate.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/inflate.o ../file/zlib/inflate.c

${OBJECTDIR}/_ext/1419175185/inftrees.o: ../file/zlib/inftrees.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/inftrees.o ../file/zlib/inftrees.c

${OBJECTDIR}/_ext/1419175185/trees.o: ../file/zlib/trees.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/trees.o ../file/zlib/trees.c

${OBJECTDIR}/_ext/1419175185/uncompr.o: ../file/zlib/uncompr.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/uncompr.o ../file/zlib/uncompr.c

${OBJECTDIR}/_ext/1419175185/zutil.o: ../file/zlib/zutil.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1419175185
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1419175185/zutil.o ../file/zlib/zutil.c

${OBJECTDIR}/_ext/760885289/evolution_json_array.o: ../json/evolution_json_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_array.o ../json/evolution_json_array.cpp

${OBJECTDIR}/_ext/760885289/evolution_json_boolean.o: ../json/evolution_json_boolean.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_boolean.o ../json/evolution_json_boolean.cpp

${OBJECTDIR}/_ext/760885289/evolution_json_null.o: ../json/evolution_json_null.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_null.o ../json/evolution_json_null.cpp

${OBJECTDIR}/_ext/760885289/evolution_json_number.o: ../json/evolution_json_number.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_number.o ../json/evolution_json_number.cpp

${OBJECTDIR}/_ext/760885289/evolution_json_object.o: ../json/evolution_json_object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_object.o ../json/evolution_json_object.cpp

${OBJECTDIR}/_ext/760885289/evolution_json_root.o: ../json/evolution_json_root.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_root.o ../json/evolution_json_root.cpp

${OBJECTDIR}/_ext/760885289/evolution_json_serialize.o: ../json/evolution_json_serialize.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_serialize.o ../json/evolution_json_serialize.cpp

${OBJECTDIR}/_ext/760885289/evolution_json_string.o: ../json/evolution_json_string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760885289
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760885289/evolution_json_string.o ../json/evolution_json_string.cpp

${OBJECTDIR}/_ext/760813065/evolution_math_utility.o: ../math/evolution_math_utility.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760813065
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760813065/evolution_math_utility.o ../math/evolution_math_utility.cpp

${OBJECTDIR}/_ext/760813065/evolution_matrix.o: ../math/evolution_matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760813065
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760813065/evolution_matrix.o ../math/evolution_matrix.cpp

${OBJECTDIR}/_ext/760813065/evolution_quaternion.o: ../math/evolution_quaternion.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760813065
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760813065/evolution_quaternion.o ../math/evolution_quaternion.cpp

${OBJECTDIR}/_ext/760813065/evolution_vector2.o: ../math/evolution_vector2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760813065
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760813065/evolution_vector2.o ../math/evolution_vector2.cpp

${OBJECTDIR}/_ext/760813065/evolution_vector3.o: ../math/evolution_vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760813065
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760813065/evolution_vector3.o ../math/evolution_vector3.cpp

${OBJECTDIR}/_ext/760813065/evolution_vector4.o: ../math/evolution_vector4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760813065
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760813065/evolution_vector4.o ../math/evolution_vector4.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-utility.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
