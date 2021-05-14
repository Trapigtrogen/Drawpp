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
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else ()
    set(LIBNAME ${PROJECT_NAME})
    set(LIBDIR ${CMAKE_BINARY_DIR}/lib)
endif (MSVC)

# Add all source files
file( GLOB_RECURSE source_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_library(${LIBNAME} STATIC external/glad/src/glad.c ${source_list})

set_target_properties(${LIBNAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LIBDIR})

if(MSVC)
    target_compile_options(${LIBNAME} PRIVATE /W0 /MP)
    target_compile_options(${LIBNAME} PRIVATE $<$<CONFIG:Debug>:/Z7>)
else()
    target_compile_options(${LIBNAME} PRIVATE -Wall -Wextra)
endif()

include_directories(include)
include_directories(external/glad/include)
include_directories(external/glad/include/glad)
include_directories(external/glfw/include)
include_directories(external/stb)
include_directories(external/nanosvg)
include_directories(external/freetype/include)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(external/glfw)
add_subdirectory(external/freetype)

if(MSVC)
    target_compile_options(freetype PRIVATE /W0 /MP)
    target_compile_options(glfw PRIVATE /W0 /MP)
    target_compile_options(freetype PRIVATE $<$<CONFIG:Debug>:/Z7>)
    target_compile_options(glfw PRIVATE $<$<CONFIG:Debug>:/Z7>)
endif(MSVC)

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

    file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/combine CONTENT 
"create lib${PROJECT_NAME}.a
addlib lib/lib${PROJECT_NAME}.a
addlib external/freetype/libfreetype.a
addlib external/glfw/src/libglfw3.a
save
end")
    
#    add_custom_target(${PROJECT_NAME} ALL
#                    COMMAND ar -M <combine.ar
#                    COMMAND ar -s ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a
#                    DEPENDS glfw ${PROJECT_NAME}_tmp
#                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
#    set(LIB_PATH ${CMAKE_BINARY_DIR}/lib/${PROJECT_NAME}.a)
endif (MSVC)

find_package(Doxygen QUIET)

if (DPP_BUILD_DOCS AND DOXYGEN_FOUND)
    set(DOXYGEN_ALWAYS_DETAILED_SEC YES)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)
    set(doxyfile ${CMAKE_BINARY_DIR}/doxyfile)
    set(DOXYGEN_OUTPUT_DIRECTORY ./docs)

    doxygen_add_docs(doxygen ALL
                ${CMAKE_SOURCE_DIR}/include)
endif (DPP_BUILD_DOCS AND DOXYGEN_FOUND)

if (DPP_BUILD_TESTS)
    add_subdirectory(tests)
endif (DPP_BUILD_TESTS)

if (DPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif (DPP_BUILD_EXAMPLES)
