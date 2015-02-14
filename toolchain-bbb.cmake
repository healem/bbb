# CMake toolchain file for building ARM software on OI environment
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)
# force shared libs to be built
SET(BUILD_SHARED_LIBS ON)
# specify the cross compiler
SET(CMAKE_C_COMPILER /home/healem/linaro/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /home/healem/linaro/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_STRIP /home/healem/linaro/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin/arm-linux-gnueabihf-strip)
# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /home/healem/linaro/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/arm-linux-gnueabihf)
# Set staging area
SET(CMAKE_STAGING_PREFIX /home/healem/staging)
SET(CMAKE_INSTALL_PREFIX /home/healem/builds/bbb)
# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) 
