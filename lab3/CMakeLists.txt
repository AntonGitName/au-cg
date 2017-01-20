cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lab3/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(lab3)
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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(SOURCE_FILES src/cpp/main.cpp
        src/cpp/AbstractRenderer.h
        src/cpp/AbstractWindowListener.h
        src/cpp/WindowWrapper.cpp
        src/cpp/LoadedObject.cpp src/cpp/LoadedObject.h
        src/cpp/ShaderWrapper.cpp src/cpp/ShaderWrapper.h
        src/cpp/ObjectBuffersWrapper.cpp src/cpp/ObjectBuffersWrapper.h
        src/cpp/ObjectRenderer.cpp src/cpp/ObjectRenderer.h
        src/cpp/CameraObject.cpp src/cpp/CameraObject.h
        src/cpp/LightingSphereRenderer.cpp src/cpp/LightingSphereRenderer.h
        src/cpp/AbstractCamera.h
        src/cpp/PhongObjectRenderer.cpp src/cpp/PhongObjectRenderer.h
        src/cpp/AbstractShaderRenderer.cpp src/cpp/AbstractShaderRenderer.h
        src/cpp/ImageRenderer.cpp src/cpp/ImageRenderer.h
        src/cpp/Scene.cpp src/cpp/Scene.h
        src/cpp/AxisRenderer.cpp src/cpp/AxisRenderer.h
        src/cpp/PointLightInfo.h
        src/cpp/PhongRenderer.cpp src/cpp/PhongRenderer.h
        src/cpp/PhongTextureRenderer.cpp src/cpp/PhongTextureRenderer.h)

add_executable(shading ${SOURCE_FILES})

target_link_libraries(shading
        ${OPENGL_LIBRARIES}
        ${SOIL_LIBRARY}
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARY}
        )