cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OpenGLGraphicsLibrary)

add_library(${PROJECT_NAME}_tmp STATIC src/drawpp.cpp
                                   external/glad/src/glad.c
                                   src/application.cpp
                                   src/window.cpp)
set_target_properties(${PROJECT_NAME}_tmp PROPERTIES 
                        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/tmp)

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glfw/include)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME}_tmp glfw)

if (WIN32)
    add_custom_target(${PROJECT_NAME} ALL
                        COMMAND lib.exe /OUT:${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.lib $<TARGET_FILE:glfw> $<TARGET_FILE:${PROJECT_NAME}_tmp>
                        DEPENDS glfw ${PROJECT_NAME}_tmp
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    set(LIB_PATH ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.lib)
else()
    file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/combine.ar CONTENT "CREATE ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a
ADDLIB $<TARGET_FILE:glfw>
ADDLIB $<TARGET_FILE:${PROJECT_NAME}_tmp>
SAVE
END")

    add_custom_target(${PROJECT_NAME} ALL
                    COMMAND ar -M <combine.ar
                    COMMAND ar -s ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a
                    DEPENDS glfw ${PROJECT_NAME}_tmp
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    set(LIB_PATH ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a)
endif (WIN32)

add_subdirectory(tests)
add_subdirectory(examples)