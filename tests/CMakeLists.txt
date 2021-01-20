set(CMAKE_CXX_STANDARD 11)

link_libraries(${PROJECT_NAME})

include_directories(include)

add_executable(test_window window.cpp)
add_executable(test_image image.cpp)
add_executable(test_shape shape.cpp)
add_executable(test_line line.cpp)
add_executable(test_background background.cpp)
add_executable(test_input input.cpp)
add_executable(test_movement movement.cpp)
add_executable(test_multiobjectmovement multiobjectmovement.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tests)