cmake_minimum_required(VERSION 3.13.4)

project(OpenGLGraphicsLibrary)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)