set(CMAKE_CXX_STANDARD 11)

if (NOT MSVC)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    link_libraries(${PROJECT_NAME})
else ()
    link_libraries(${LIB_PATH})
endif (NOT MSVC)

include_directories(include)

add_executable(example_de-jong-attractor example_de-jong-attractor.cpp)

if (MSVC)
    add_dependencies(example_de-jong-attractor ${PROJECT_NAME})
    
    #add working dir and asset copy code here if needed
endif (MSVC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/examples)