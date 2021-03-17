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
# TODO add build mode
cmake .. -DDPP_BUILD_DOCS=$incDoc -DPP_BUILD_TESTS=OFF -DPP_BUILD_EXAMPLES=ON -DPP_BUILD_DEBUG=$debugBuild
make || { echo "Build failed. Exiting.."; exit 1; }


# CLEANUP:

echo "Removing build files..."
# remove all loose files
rm ./*.*
rm ./Makefile
# remove unnecessary folders
rm -rf ./CMakeFiles
rm -rf ./examples
rm -rf ./tests

echo "Copying headers over..."
# copy include files
cp -r ../include/ ./
cp -r ../external/glad/include/ ./include/
cp -r ../external/glfw/include/GLFW ./include/
cp -r ../external/stb ./include/
cp -r ../external/nanosvg ./include/

echo "Combining libraries..."
# combine libraries
mkdir lib1 && cd lib1 && ar -x ../lib/libOpenGLGraphicsLibrary.a
cd ..
mkdir lib2 && cd lib2 && ar -x ../external/glfw/src/libglfw3.a
cd ..
ar -qc libOpenGLGraphicsLibrary.a ./lib1/*.o ./lib2/*.o

echo "Copying tests and examples over..."
# move tests and examples to main folder and release empty folders
if [ -d ./bin/tests ] && [ $debugBuild = "ON" ]; then
    mv ./bin/tests ./
fi
if [ -d ./bin/examples ]; then
mv ./bin/examples ./
fi

echo "final cleanup..."
rm -rf ./bin

# Remove temp folders
rm -rf ./lib1
rm -rf ./lib2

# Remove library folders
rm -rf ./lib
rm -rf ./external

echo "Done!"