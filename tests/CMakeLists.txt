set(CMAKE_CXX_STANDARD 11)

if (NOT MSVC)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    link_libraries(${PROJECT_NAME})
else ()
    link_libraries(${LIB_PATH})
endif (NOT MSVC)

include_directories(include)
include_directories(external/glad/include/glad)

# Add all test source files as executables
file( GLOB_RECURSE source_list RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")
foreach( file_path ${source_list} )
    string( REPLACE ".cpp" "" new_name ${file_path} )
    get_filename_component( filename ${new_name} NAME )
    add_executable( test_${filename} ${filename}.cpp )

    if (MSVC)
        add_dependencies(test_${filename} ${PROJECT_NAME})
        set_property(TARGET test_${filename} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
        target_compile_options(test_${filename} PRIVATE /W0 /MP)
    endif (MSVC)
endforeach()

if (NOT MSVC)
    file(COPY "${CMAKE_SOURCE_DIR}/tests/assets" DESTINATION "${CMAKE_BINARY_DIR}/bin/tests")
endif (NOT MSVC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tests)