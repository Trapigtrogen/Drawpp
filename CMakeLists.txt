cmake_minimum_required(VERSION 3.13.4)

project(OpenGLGraphicsLibrary)

add_library(${PROJECT_NAME} STATIC src/tmp_main_source.cpp external/glad/src/glad.c)
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