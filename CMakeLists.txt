cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OpenGLGraphicsLibrary)

add_library(${PROJECT_NAME} STATIC src/drawpp.cpp
                                   external/glad/src/glad.c
                                   src/application.cpp
                                   src/window.cpp
                                   src/input.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glfw/include)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(tests)
add_subdirectory(examples)