# CMake toolchain file for building Intel software on OI environment
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)
# force shared libs to be built
SET(BUILD_SHARED_LIBS ON)
# specify the cross compiler
SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
#SET(CMAKE_STRIP /usr/bin/strip)
# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /lib/x86_64-linux-gnu)
# Set staging area
SET(CMAKE_STAGING_PREFIX /home/healem/clang-intel-staging)
SET(CMAKE_INSTALL_PREFIX /home/healem/builds/clang-intel-bbb)
# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) 
# set overrides
SET(CMAKE_USER_MAKE_RULES_OVERRIDE "$ENV{HOMEDIR}/clang-intel-overrides.txt")
