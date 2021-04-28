cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Drawpp)

option(DPP_BUILD_DEBUG "Debug build" OFF)
option(DPP_BUILD_DOCS "Generate documentation with Doxygen" ON)
option(DPP_BUILD_TESTS "Include tests" ON)
option(DPP_BUILD_EXAMPLES "Include examples" ON)

if (DPP_BUILD_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
else ()
    set(CMAKE_BUILD_TYPE Release)
endif (DPP_BUILD_DEBUG)

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
                                   src/window.cpp
                                   src/input.cpp
                                   src/window.cpp
                                   src/matrix4.cpp
                                   src/vector3.cpp
                                   src/random.cpp
                                   src/graphics.cpp
                                   src/time.cpp
                                   src/shader.cpp
                                   src/image.cpp
                                   src/color.cpp
                                   src/shape.cpp
                                   src/noise.cpp
                                   src/font.cpp
                                   src/vec2f.cpp
                                   src/path.cpp
                                   src/colors.cpp
                                   src/filter.cpp)
set_target_properties(${LIBNAME} PROPERTIES 
                        ARCHIVE_OUTPUT_DIRECTORY ${LIBDIR})

if(MSVC)
    target_compile_options(${LIBNAME} PRIVATE /W4)
else()
    target_compile_options(${LIBNAME} PRIVATE -Wall -Wextra)
endif()

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glfw/include)
include_directories(external/stb)
include_directories(external/nanosvg)
include_directories(external/freetype/include)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(external/glfw)
add_subdirectory(external/freetype)
target_link_libraries(${LIBNAME} glfw)
target_link_libraries(${LIBNAME} freetype)

if (MSVC)
    add_custom_target(${PROJECT_NAME} ALL
                        COMMAND lib.exe /OUT:${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.lib $<TARGET_FILE:glfw> $<TARGET_FILE:freetype> $<TARGET_FILE:${PROJECT_NAME}_tmp>
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

if (DPP_BUILD_DOCS AND DOXYGEN_FOUND)
    set(DOXYGEN_ALWAYS_DETAILED_SEC YES)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)
    set(doxyfile ${CMAKE_BINARY_DIR}/doxyfile)
    set(DOXYGEN_OUTPUT_DIRECTORY ./docs)

    doxygen_add_docs(doxygen ALL
                ${CMAKE_SOURCE_DIR}/include)
elseif(NOT DOXYGEN_FOUND)
    message(SEND_ERROR "Doxygen executable not found")
endif (DPP_BUILD_DOCS AND DOXYGEN_FOUND)

if (DPP_BUILD_TESTS)
    add_subdirectory(tests)
endif (DPP_BUILD_TESTS)

if (DPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif (DPP_BUILD_EXAMPLES)


# Fix bug in Linux where the HAVE_FCNTL_H is not defined even when it's found in the system
if (UNIX)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/freetype/builds/unix/ftsystem.c)
        execute_process(COMMAND git submodule update --init --recursive)
    endif ()
    execute_process(COMMAND sed -i"s/#ifdef HAVE_FCNTL_H/#if 1/g" ${CMAKE_SOURCE_DIR}/external/freetype/builds/unix/ftsystem.c)
endif (UNIX)
