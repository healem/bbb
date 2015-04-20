# CMake toolchain file for building ARM software on OI environment
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)
# force shared libs to be built
SET(BUILD_SHARED_LIBS ON)
# specify the cross compiler
SET(CMAKE_C_COMPILER /usr/bin/clang-3.5)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++-3.5)
#SET(CMAKE_STRIP /usr/bin/arm-linux-gnueabihf-strip)
# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)
# Set staging area
SET(CMAKE_STAGING_PREFIX /home/healem/clang-arm-staging)
SET(CMAKE_INSTALL_PREFIX /home/healem/builds/clang-arm-bbb)
# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) 

SET(CMAKE_CROSSCOMPILING True)
SET(LLVM_TABLEGEN /usr/bin/llvm-tblgen-3.5)
SET(CLANG_TABLEGEN /usr/bin/clang-tblgen-3.5)
SET(LLVM_DEFAULT_TARGET_TRIPLE arm-linux-gnueabihf)
SET(LLVM_TARGET_ARCH ARM)
SET(LLVM_TARGETS_TO_BUILD ARM)
