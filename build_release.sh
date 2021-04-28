#!/bin/sh
cd `dirname $(realpath $0)`
# Either create or empty release folder
if [ ! -d ./release ]; then
    mkdir -p ./release;
else
    rm -rf ./release/*
fi

# If -f is used use default settings
if [ $1 == "-f" ]; then
    incDoc="OFF"
    debugBuild="OFF"
else

    while true
    do
        read -r -p "Include documentation? [y/n] " docs

        case $docs in
        [yY])
            echo "Will include documentation"
            incDoc="ON"
            break
            ;;
        [nN])
            echo "Won't include documentation"
            incDoc="OFF"
            break
            ;;
        *)
            echo "Invalid input. Should be y/n"
            ;;
        esac
    done

    while true
    do
        read -r -p "Debug build? [y/n] " mode

        case $mode in
        [yY])
            echo "Will build in debug mode"
            debugBuild="ON"
            break
            ;;
        [nN])
            echo "Will build in release mode"
            debugBuild="OFF"
            break
            ;;
        *)
            echo "Invalid input. Should be y/n"
            ;;
        esac
    done

fi

# Update GLFW
git submodule update --init --recursive

cd ./release

# CMake and build
cmake .. -DDPP_BUILD_DOCS=$incDoc -DPP_BUILD_TESTS=OFF -DPP_BUILD_EXAMPLES=ON -DPP_BUILD_DEBUG=$debugBuild
make || { echo "Build failed. Exiting.."; exit 1; }


echo "Removing some build files..."
# remove all loose files
rm ./*.*
rm ./Makefile

echo "Copying headers over..."
# copy include files
mkdir include

cp ../include/application.hpp ./include/
cp ../include/color.hpp ./include/
cp ../include/hsbcolor.hpp ./include/
cp ../include/colors.hpp ./include/
cp ../include/drawpp.hpp ./include/
cp ../include/graphics.hpp ./include/
cp ../include/image.hpp ./include/
cp ../include/keys.hpp ./include/
cp ../include/matrix4.hpp ./include/
cp ../include/noise.hpp ./include/
cp ../include/random.hpp ./include/
cp ../include/shape.hpp ./include/
cp ../include/vector3.hpp ./include/
cp ../include/font.hpp ./include/
cp ../include/path.hpp ./include/
cp ../include/constants.hpp ./include/
cp ../include/filter.hpp ./include/

echo "Combining libraries..."
# combine libraries
mkdir lib1 && cd lib1 && ar -x ../lib/libDrawpp.a
cd ..
mkdir lib2 && cd lib2 && ar -x ../external/glfw/src/libglfw3.a
cd ..
mkdir lib3 && cd lib3 && ar -x ../external/freetype/libfreetype.a
cd ..
ar -qc libDrawpp.a ./lib1/*.o ./lib2/*.o ./lib3/*.o

# move tests to main folder
rm -rf ./tests
if [ -d ./bin/tests ] && [ $debugBuild = "ON" ]; then
    echo "Copying tests over..."
    mv ./bin/tests ./
fi

# EXAMPLES:
if [ ! -d ./examples ]; then
    mkdir examples
fi

cp -r ../examples ./

# Create CMakeLists.txt file for examples
echo "cmake_minimum_required(VERSION 3.13.4)">./examples/CMakeLists.txt
echo "set(CMAKE_CXX_STANDARD 11)">>./examples/CMakeLists.txt
echo "set(CMAKE_CXX_STANDARD_REQUIRED ON)">>./examples/CMakeLists.txt
echo "project(GraphicsLib_Examples)">>./examples/CMakeLists.txt
echo "link_libraries(\${CMAKE_SOURCE_DIR}/../libDrawpp.a)">>./examples/CMakeLists.txt

echo "include_directories(\${CMAKE_SOURCE_DIR}/../include)">>./examples/CMakeLists.txt
echo "set(EXECUTABLE_OUTPUT_PATH \${CMAKE_BINARY_DIR}/bin)">>./examples/CMakeLists.txt

# Add examples to CMakeLists.txt
for file in ./examples/*.cpp
do
    filename=$(basename "$file")
    fname="${filename%.*}"
    echo "add_executable(example_$fname $filename)">>./examples/CMakeLists.txt
done


# FINAL CLEANUP:

echo "final cleanup..."
rm -rf ./bin

# Remove temp folders
rm -rf ./lib1
rm -rf ./lib2
rm -rf ./lib3

# Remove library folders
rm -rf ./lib
rm -rf ./external

# remove other unnecessary folders
rm -rf ./CMakeFiles

echo "Done!"