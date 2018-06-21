cmake_minimum_required(VERSION 3.10)
project(UnusualArtGallery)

set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
set(CMAKE_MAKE_PROGRAM "C:/MinGW/bin/mingw32-make.exe")
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/glew/include)
include_directories(${PROJECT_SOURCE_DIR}/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/glm/)
include_directories(${PROJECT_SOURCE_DIR}/Lodepng)
link_directories(${PROJECT_SOURCE_DIR}/glew/lib)
link_directories(${PROJECT_SOURCE_DIR}/glfw/lib)

add_executable(UnusualArtGallery main.cpp 
        Setup.cpp
        Camera.cpp Camera.h
        ShaderProgram.h ShaderProgram.cpp
        Lodepng/lodepng.h Lodepng/lodepng.cpp
        Texture.h Texture.cpp
        Model.cpp Model.h
        SimulatorEngine.cpp SimulatorEngine.h 
        )
add_definitions(-DGLEW_STATIC)

target_link_libraries(UnusualArtGallery glew32s glfw3 opengl32 gdi32 glu32)