# https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md

# EQ CMakeLists.txt

# Set CMake version
cmake_minimum_required(VERSION 3.22)

# Name and version of the project
project(EQ VERSION 0.0.1)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
include(cmake/cpm.cmake)