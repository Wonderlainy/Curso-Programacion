# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(proyecto VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
link_directories(lib)

# Add the executable
add_executable(proyecto main.cpp)

target_link_libraries(proyecto SDL2 SDL2main SDL2test)
