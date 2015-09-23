
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)
# force shared libs to be built
SET(BUILD_SHARED_LIBS ON)
# specify the cross compiler
SET(CMAKE_CROSSCOMPILING True)
SET(triple arm-linux-gnueabihf)

SET(CMAKE_LIBRARY_ARCHITECTURE ${triple})

SET(CMAKE_C_COMPILER /usr/bin/clang-3.5)
SET(CMAKE_C_COMPILER_TARGET ${triple})
#SET(CMAKE_C_LINK_EXECUTABLE /usr/arm-linux-gnueabihf/bin/ld)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++-3.5)
SET(CMAKE_CXX_COMPILER_TARGET ${triple})
#SET(CMAKE_CXX_LINK_EXECUTABLE /usr/arm-linux-gnueabihf/bin/ld)
#SET(CMAKE_STRIP /usr/bin/arm-linux-gnueabihf-strip)
# where is the target environment
include_directories(/usr/${triple})
SET(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)

## CLang workarounds
#set(lib_dir1 /usr/lib/gcc-cross/${triple}/4.8)
#set(lib_dir2 /usr/${triple}/lib/)
#set(CMAKE_TOOLCHAIN_LINK_FLAGS "-B${lib_dir1} -B${lib_dir2} -L${lib_dir1} -L${lib_dir2}")

# CMake workarounds
#set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_TOOLCHAIN_LINK_FLAGS} CACHE INTERNAL "exe link flags")
#set(CMAKE_MODULE_LINKER_FLAGS ${CMAKE_TOOLCHAIN_LINK_FLAGS} CACHE INTERNAL "module link flags")
#set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_TOOLCHAIN_LINK_FLAGS} CACHE INTERNAL "shared link flags")

# Set staging area
SET(CMAKE_STAGING_PREFIX /home/healem/clang-arm-staging)
SET(CMAKE_INSTALL_PREFIX /home/healem/builds/clang-arm-bbb)
# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) 
# Set overrides
SET(CMAKE_USER_MAKE_RULES_OVERRIDE "$ENV{HOMEDIR}/clang-arm-overrides.txt")
#SET (CMAKE_CXX_FLAGS '-target armv7a-linux-gnueabihf -mcpu=cortex-a8 -I/usr/arm-linux-gnueabihf/include/c++/4.7.2/arm-linux-gnueabihf/ -I/usr/arm-linux-gnueabihf/include/ -mfloat-abi=hard -ccc-gcc-name arm-linux-gnueabihf-gcc')
