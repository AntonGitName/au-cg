cmake_minimum_required(VERSION 3.1)
project(lab1)
INCLUDE(FindPkgConfig)

find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)



pkg_search_module(GLFW REQUIRED glfw3)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GlmIncludeDir} ${GLFW_INCLUDE_DIRS} )
add_definitions(-Wall -Wextra -pedantic -O3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main.cpp src/MandelbrotRenderer.cpp src/WindowWrapper.cpp src/ShaderWrapper.cpp src/ShaderWrapper.h src/Pane.cpp src/Pane.h src/MandelbrotTexture.cpp src/MandelbrotTexture.h src/AbstractWindowListener.h)

add_executable(fractal ${SOURCE_FILES})

target_link_libraries(fractal
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARY})