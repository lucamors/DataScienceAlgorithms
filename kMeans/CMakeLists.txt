# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(kMeans VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(../RandomNumberGenerators/)
include_directories(include)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Include the SDL2 include directories
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.c")
set (CMAKE_C_FLAGS "-O3")

# Add the executable
add_executable(${PROJECT_NAME} main.c ${SOURCES})

target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
