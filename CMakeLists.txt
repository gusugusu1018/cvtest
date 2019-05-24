cmake_minimum_required(VERSION 3.0)
project(gusucv LANGUAGES CXX C)

if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()
if(POLICY CMP0074)
    cmake_policy(SET CMP0074 OLD)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

########################
# Set compiler options #
########################

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")

#######################
# Check C++11 support #
#######################

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    message(STATUS "C++11 support: OK (-std=c++11)")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    message(STATUS "C++11 support: OK (-std=c++0x)")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# OpenCV
find_package(OpenCV 3.4)
if(NOT OpenCV_FOUND)
    find_package(OpenCV 4.0)
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV > 3.4.0 not found")
    endif()
endif()
message(STATUS "Use OpenCV ${OpenCV_VERSION}")
include_directories(${OpenCV_INCLUDE_DIRS})

# Eigen
#find_package(Eigen3 3.2 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})

# g2o
#find_package(G2O REQUIRED)
#include_directories(${G2O_INCLUDE_DIR})

add_executable(opencvtest src/opencvtest.cpp)
target_link_libraries(opencvtest ${OpenCV_LIBS})
