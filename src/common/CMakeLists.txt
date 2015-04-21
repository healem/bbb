#find_library(STDLIB 
#             NAMES stdc++
#             HINTS "${CMAKE_FIND_ROOT_PATH}")
#message(STATUS "STD C++ libs: ${STDLIB} on path ${CMAKE_FIND_ROOT_PATH}/lib")
#include_directories(${CMAKE_FIND_ROOT_PATH}/include)
add_library(logger logger.cpp)
install(TARGETS logger
        DESTINATION lib)
