# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(GUI VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES WIN32
            src/main.cpp
            src/GUI.cpp
            external/imgui/misc/cpp/imgui_stdlib.cpp
            external/imgui/imgui.cpp
            external/imgui/imgui_draw.cpp
            external/imgui/imgui_widgets.cpp
            external/imgui/imgui_tables.cpp
            external/imgui/backends/imgui_impl_glfw.cpp
            external/imgui/backends/imgui_impl_opengl3.cpp)

set(LINK_LIBRARIES  glew32
                    glfw3
                    # Replace this line with the proper path to your OpenGL32.Lib file
                    "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/OpenGL32.Lib"
                    )

include_directories( external/glew-2.1.0/include
                     external
                     external/glfw-3.4/include
                     external/imgui
                     external/imgui/backends
                     )

link_directories(   external/glew-2.1.0/lib/Release/x64
                    external/glfw-3.4/build/src/Debug
                    lib)

# Add the executable
add_executable(GUI ${SOURCES})

target_link_libraries(GUI ${LINK_LIBRARIES})