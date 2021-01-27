set(CMAKE_CXX_STANDARD 11)

if (NOT MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    link_libraries(${PROJECT_NAME})
else ()
    link_libraries(${LIB_PATH})
endif (NOT MSVC)


include_directories(include)

add_executable(test_window window.cpp)
add_executable(test_image image.cpp)
add_executable(test_shape shape.cpp)
add_executable(test_line line.cpp)
add_executable(test_background background.cpp)
add_executable(test_input input.cpp)
add_executable(test_movement movement.cpp)
add_executable(test_multiobjectmovement multiobjectmovement.cpp)

if (MSVC)
    add_dependencies(test_window ${PROJECT_NAME})
    add_dependencies(test_image ${PROJECT_NAME})
    add_dependencies(test_shape ${PROJECT_NAME})
    add_dependencies(test_line ${PROJECT_NAME})
    add_dependencies(test_background ${PROJECT_NAME})
    add_dependencies(test_input ${PROJECT_NAME})
    add_dependencies(test_movement ${PROJECT_NAME})
    add_dependencies(test_multiobjectmovement ${PROJECT_NAME})
endif (MSVC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tests)