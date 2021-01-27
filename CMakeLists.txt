cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OpenGLGraphicsLibrary)

if (MSVC)
    set(LIBNAME ${PROJECT_NAME}_tmp)
    set(LIBDIR ${CMAKE_BINARY_DIR}/lib/tmp)
else ()
    set(LIBNAME ${PROJECT_NAME})
    set(LIBDIR ${CMAKE_BINARY_DIR}/lib)
endif (MSVC)

add_library(${LIBNAME} STATIC src/drawpp.cpp
                                   external/glad/src/glad.c
                                   src/application.cpp
                                   src/input.cpp)
                                   src/window.cpp)
set_target_properties(${LIBNAME} PROPERTIES 
                        ARCHIVE_OUTPUT_DIRECTORY ${LIBDIR})

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glfw/include)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(external/glfw)
target_link_libraries(${LIBNAME} glfw)

if (MSVC)
    add_custom_target(${PROJECT_NAME} ALL
                        COMMAND lib.exe /OUT:${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.lib $<TARGET_FILE:glfw> $<TARGET_FILE:${PROJECT_NAME}_tmp>
                        DEPENDS glfw ${LIBNAME}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    set(LIB_PATH ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.lib)
else ()
    set(LIB_PATH ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a)
#else()
#    file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/combine.ar CONTENT "CREATE ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a
#ADDLIB $<TARGET_FILE:glfw>
#ADDLIB $<TARGET_FILE:${PROJECT_NAME}_tmp>
#SAVE
#END")
#
#    add_custom_target(${PROJECT_NAME} ALL
#                    COMMAND ar -M <combine.ar
#                    COMMAND ar -s ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a
#                    DEPENDS glfw ${PROJECT_NAME}_tmp
#                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
#    set(LIB_PATH ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a)
endif (MSVC)

find_package(Doxygen)
option(GEN_DOCS "Generate documentation with doxygen" ${DOXYGEN_FOUND})

if (GEN_DOCS)
    if(NOT DOXYGEN_FOUND)
        message(SEND_ERROR "Doxygen executable not found")
    else ()
        set(doxyfile ${CMAKE_BINARY_DIR}/doxyfile)
        set(DOXYGEN_OUTPUT_DIRECTORY ./docs)

        doxygen_add_docs(doxygen ALL
                    ${CMAKE_SOURCE_DIR}/include)
    endif (NOT DOXYGEN_FOUND)
endif (GEN_DOCS)

add_subdirectory(tests)
add_subdirectory(examples)