link_libraries(${PROJECT_NAME})

include_directories(include)

add_executable(windowtest window.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tests)