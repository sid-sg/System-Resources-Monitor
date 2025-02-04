cmake_minimum_required(VERSION 3.10)
project(System-Resources-Monitor VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(systemMonitor 
    src/main.cpp
    src/cpu_stats.cpp
    src/graphics.cpp
)

target_link_libraries(systemMonitor 
    PRIVATE
    OpenGL::OpenGL
    GLEW::GLEW
    glfw
    GLUT::GLUT
)
