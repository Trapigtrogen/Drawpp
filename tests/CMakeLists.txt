set(CMAKE_CXX_STANDARD 11)

if (NOT MSVC)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    link_libraries(${PROJECT_NAME})
else ()
    link_libraries(${LIB_PATH})
endif (NOT MSVC)


include_directories(include)

add_executable(test_window window.cpp)
add_executable(test_textures textures.cpp)
add_executable(test_shape shape.cpp)
add_executable(test_line line.cpp)
add_executable(test_background background.cpp)
add_executable(test_input input.cpp)
add_executable(test_movement movement.cpp)
add_executable(test_multiobjectmovement multiobjectmovement.cpp)
add_executable(test_draw_ellipse_circle draw_ellipse_circle.cpp)
add_executable(test_draw_triangle draw_triangle.cpp)
add_executable(test_draw_rect_square draw_rect_square.cpp)
add_executable(test_draw_line_point draw_line_point.cpp)
add_executable(test_draw_quad draw_quad.cpp)
add_executable(test_noise noiseTest.cpp)
add_executable(test_draw_text draw_text.cpp)

if (MSVC)
    add_dependencies(test_window ${PROJECT_NAME})
    add_dependencies(test_textures ${PROJECT_NAME})
    add_dependencies(test_shape ${PROJECT_NAME})
    add_dependencies(test_line ${PROJECT_NAME})
    add_dependencies(test_background ${PROJECT_NAME})
    add_dependencies(test_input ${PROJECT_NAME})
    add_dependencies(test_movement ${PROJECT_NAME})
    add_dependencies(test_multiobjectmovement ${PROJECT_NAME})
    add_dependencies(test_draw_ellipse_circle ${PROJECT_NAME})
    add_dependencies(test_draw_triangle ${PROJECT_NAME})
    add_dependencies(test_draw_rect_square ${PROJECT_NAME})
    add_dependencies(test_draw_line_point ${PROJECT_NAME})
    add_dependencies(test_draw_quad ${PROJECT_NAME})
    add_dependencies(test_noise ${PROJECT_NAME})
    add_dependencies(test_draw_text ${PROJECT_NAME})

    set_property(TARGET test_window
                        test_textures
                        test_shape
                        test_line
                        test_background
                        test_input
                        test_movement
                        test_multiobjectmovement
                        test_draw_ellipse_circle
                        test_draw_triangle
                        test_draw_rect_square
                        test_draw_line_point
                        test_draw_quad
                        test_noise
                        test_draw_text
                 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
else ()
    file(COPY "${CMAKE_SOURCE_DIR}/tests/assets" DESTINATION "${CMAKE_BINARY_DIR}/bin/tests")
endif (MSVC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tests)