set(CMAKE_CXX_STANDARD 11)

if (NOT MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif (NOT MSVC)

link_libraries(${LIB_PATH})

include_directories(include)

add_executable(windowtest window.cpp)

if (MSVC)
    add_dependencies(windowtest ${PROJECT_NAME})
endif (MSVC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tests)