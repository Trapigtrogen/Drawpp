cmake_minimum_required(VERSION 3.13.4)

project(OpenGLGraphicsLibrary)

add_executable(${PROJECT_NAME} src/main.cpp external/glad/src/glad.c)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glfw/include)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)