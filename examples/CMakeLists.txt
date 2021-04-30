set(CMAKE_CXX_STANDARD 11)

if (NOT MSVC)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    link_libraries(${PROJECT_NAME})
else ()
    link_libraries(${LIB_PATH})
endif (NOT MSVC)

include_directories(include)
include_directories(external/glad/include/glad)

add_executable(example_de-jong-attractor example_de-jong-attractor.cpp)
add_executable(example_buttons example_buttons.cpp)
add_executable(example_draw example_draw.cpp)
add_executable(example_perlin-noise example_perlin-noise.cpp)
add_executable(example_color_mousewheel example_color_mousewheel.cpp)
add_executable(example_custom_filter custom_filter.cpp)

if (MSVC)
    add_dependencies(example_de-jong-attractor ${PROJECT_NAME})
    add_dependencies(example_buttons ${PROJECT_NAME})
    add_dependencies(example_draw ${PROJECT_NAME})
    add_dependencies(example_perlin-noise ${PROJECT_NAME})
    add_dependencies(example_color_mousewheel ${PROJECT_NAME})
    add_dependencies(example_custom_filter ${PROJECT_NAME})
    
    set_property(TARGET example_de-jong-attractor
                        example_buttons
                        example_draw
                        example_perlin-noise
                        example_color_mousewheel
                        example_custom_filter
                 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/examples")
else ()
    file(COPY "${CMAKE_SOURCE_DIR}/examples/assets" DESTINATION "${CMAKE_BINARY_DIR}/bin/examples")
endif (MSVC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/examples)