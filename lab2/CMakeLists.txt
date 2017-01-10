cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lab2/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(lab2)
INCLUDE(FindPkgConfig)


find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SOIL REQUIRED)
find_package(GLM REQUIRED)


pkg_search_module(GLFW REQUIRED glfw3)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GlmIncludeDir} ${GLFW_INCLUDE_DIRS} ${SOIL_INCLUDE_DIRS})
add_definitions(-Wall -Wextra -pedantic -g)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
set(SOURCE_FILES src/cpp/main.cpp src/cpp/AbstractRenderer.h src/cpp/AbstractWindowListener.h src/cpp/WindowWrapper.cpp src/cpp/LoadedObject.cpp src/cpp/LoadedObject.h src/cpp/BunnyRenderer.cpp src/cpp/BunnyRenderer.h src/cpp/ShaderWrapper.cpp src/cpp/ShaderWrapper.h src/cpp/ObjectBuffersWrapper.cpp src/cpp/ObjectBuffersWrapper.h src/cpp/ObjectRenderer.cpp src/cpp/ObjectRenderer.h src/cpp/CubeRenderer.cpp src/cpp/CubeRenderer.h src/cpp/CameraObject.cpp src/cpp/CameraObject.h src/cpp/CameraCentered.cpp src/cpp/CameraCentered.h src/cpp/AbstractCamera.cpp src/cpp/AbstractCamera.h)

add_executable(reflection ${SOURCE_FILES})

target_link_libraries(reflection
        ${OPENGL_LIBRARIES}
        ${SOIL_LIBRARY}
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARY}
        )