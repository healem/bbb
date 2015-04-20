# CMake toolchain file for building Intel software on OI environment
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)
# force shared libs to be built
SET(BUILD_SHARED_LIBS ON)
# specify the cross compiler
SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
SET(CMAKE_STRIP /usr/bin/strip)
# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /lib/x86_64-linux-gnu)
# Set staging area
SET(CMAKE_STAGING_PREFIX /home/healem/gnu-intel-staging)
SET(CMAKE_INSTALL_PREFIX /home/healem/builds/gnu-intel-bbb)
# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) 
