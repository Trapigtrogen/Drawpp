cmake_minimum_required(VERSION 3.13.4)

project(OpenGLGraphicsLibrary)

add_executable(${PROJECT_NAME} src/main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glfw/include)