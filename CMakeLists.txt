cmake_minimum_required(VERSION 3.10)

# Project name and language
project(FluidSim CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define sources explicitly
set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/renderer.cpp
        ${CMAKE_SOURCE_DIR}/src/fluid.cpp
        ${CMAKE_SOURCE_DIR}/src/random.cpp
        #        ${CMAKE_SOURCE_DIR}/src/input.cpp
)

# Create executable
add_executable(FluidSim ${SOURCES})

# Link SDL2
target_link_libraries(FluidSim SDL2)
