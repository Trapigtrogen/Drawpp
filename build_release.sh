#!/bin/sh
cd `dirname $(realpath $0)`

if [ ! -d ./release ]; then
  mkdir -p ./release;
fi

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
        if [ ! -d ./release ]; then
            mkdir -p ./release;
        fi
        break
        ;;
    [nN])
        echo "Will build in release mode"
        debugBuild="OFF"
        if [ ! -d ./release ]; then
            mkdir -p ./release;
        fi
        break
        ;;
    *)
        echo "Invalid input. Should be y/n"
        ;;
    esac
done

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
cp -r ../include/ ./
#cp -r ../external/glad/include/ ./include/
#cp -r ../external/glfw/include/GLFW ./include/
#cp -r ../external/stb ./include/
#cp -r ../external/nanosvg ./include/

echo "Combining libraries..."
# combine libraries
mkdir lib1 && cd lib1 && ar -x ../lib/libOpenGLGraphicsLibrary.a
cd ..
mkdir lib2 && cd lib2 && ar -x ../external/glfw/src/libglfw3.a
cd ..
ar -qc libOpenGLGraphicsLibrary.a ./lib1/*.o ./lib2/*.o

# move tests to main folder
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
echo "link_libraries(\${CMAKE_SOURCE_DIR}/../OpenGLGraphicsLibrary.lib)">>./examples/CMakeLists.txt

echo "include_directories(\${CMAKE_SOURCE_DIR}/../include)">>./examples/CMakeLists.txt
echo "set(EXECUTABLE_OUTPUT_PATH \${CMAKE_BINARY_DIR}/bin)">>./examples/CMakeLists.txt
#add example files here like this
#echo add_executable(example_window window.cpp)>>./examples/CMakeLists.txt

#for now, no examples
echo "message(SEND_ERROR \"No examples!\")">>./examples/CMakeLists.txt



# FINAL CLEANUP:

echo "final cleanup..."
rm -rf ./bin

# Remove temp folders
rm -rf ./lib1
rm -rf ./lib2

# Remove library folders
rm -rf ./lib
rm -rf ./external

# remove other unnecessary folders
rm -rf ./CMakeFiles
rm -rf ./tests

echo "Done!"