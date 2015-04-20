cmake_minimum_required(VERSION 2.8.8)
project(bbb)

SET(CMAKE_CROSSCOMPILING True)
SET(LLVM_TABLEGEN /usr/bin/llvm-tblgen-3.5)
SET(CLANG_TABLEGEN /usr/bin/clang-tblgen-3.5)
SET(LLVM_DEFAULT_TARGET_TRIPLE arm-linux-gnueabihf)
SET(LLVM_TARGET_ARCH ARM)
SET(LLVM_TARGETS_TO_BUILD ARM)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Now build our tools
add_executable(bbb src/bbb.cpp)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(bbb ${llvm_libs})
