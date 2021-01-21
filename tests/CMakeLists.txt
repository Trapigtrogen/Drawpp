set(CMAKE_CXX_STANDARD 11)

link_libraries(${LIB_PATH})

include_directories(include)

add_executable(windowtest window.cpp)
add_dependencies(windowtest ${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tests)