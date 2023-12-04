# Set CMake version
cmake_minimum_required(VERSION 3.22)

# Name of the project
project(EQ)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)

# Compile without warnings being treated as errors
option (TRACKTION_CI_ENABLED "" OFF)

if (TRACKTION_CI_ENABLED)
    #set CI-only options, add warning as errors, etc
endif()

# Setting the library directory
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Including the CPM package manager
include(cmake/cpm.cmake)

# Adding the JUCE framework with version 7.0.9
CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 7.0.9
    VERSION 7.0.9
    SOURCE_DIR ${LIB_DIR}/juce
)

# Setting compile options
if(MSVC)
    add_compile_options(/Wall /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(Source)