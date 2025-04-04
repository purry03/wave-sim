cmake_minimum_required(VERSION 3.10)

# Project name and language
project(wavesim CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(SDL2 REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories("/usr/lib/python3/dist-packages/numpy/core/include")

# Define sources explicitly
set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/renderer.cpp
        ${CMAKE_SOURCE_DIR}/src/fluid.cpp
        ${CMAKE_SOURCE_DIR}/src/random.cpp
        #        ${CMAKE_SOURCE_DIR}/src/input.cpp
)

# Create executable
add_executable(wavesim ${SOURCES})

# Link SDL2
target_link_libraries(wavesim SDL2)
target_link_libraries(wavesim ${PYTHON_LIBRARIES})
