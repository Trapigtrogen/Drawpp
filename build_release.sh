#!/bin/sh

# Start in the folder where the script is
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

# Update GLFW and Freetype
git submodule update --recursive

cd ./release

# CMake and build
cmake .. -DDPP_BUILD_DOCS=$incDoc -DPP_BUILD_TESTS=$debugBuild -DPP_BUILD_EXAMPLES=OFF -DPP_BUILD_DEBUG=$debugBuild
make || { echo "Build failed. Exiting.."; exit 1; }


echo "Removing some build files..."
# remove all loose files
rm ./*.*
rm ./Makefile

echo "Copying headers over..."
# copy include files
mkdir include
mkdir include/KHR

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
cp ../include/filters.hpp ./include/

cp ../external/glad/include/glad/glad.h ./include/
cp ../external/glad/include/KHR/khrplatform.h ./include/KHR/

echo "Combining libraries..."
# combine libraries using script
ar -M <combine
# Remove script
rm combine


# TESTS:
rm -r ./tests
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
mkdir ./examples/build
mkdir ./examples/build/bin
mv ./examples/assets ./examples/build/bin/

# Create CMakeLists.txt file for building examples
echo "cmake_minimum_required(VERSION 3.13.4)">./examples/CMakeLists.txt
echo "include(CheckIncludeFiles)">>./examples/CMakeLists.txt
echo "include(CheckFunctionExists)">>./examples/CMakeLists.txt
echo "set(CMAKE_CXX_STANDARD 11)">>./examples/CMakeLists.txt
echo "set(CMAKE_CXX_STANDARD_REQUIRED ON)">>./examples/CMakeLists.txt
echo "project(GraphicsLib_Examples)">>./examples/CMakeLists.txt
echo "set(THREADS_PREFER_PTHREAD_FLAG ON)">>./examples/CMakeLists.txt
echo "find_package(Threads REQUIRED)">>./examples/CMakeLists.txt
echo "set(DPP_WLIBS \"\")">>./examples/CMakeLists.txt
echo "set(DPP_WINCS \"\")">>./examples/CMakeLists.txt
echo "include(CMakeDependentOption)">>./examples/CMakeLists.txt
echo "cmake_dependent_option(DPP_USE_WINDOW_WAYLAND \"Use Wayland as window system\" OFF \"UNIX;NOT APPLE\" OFF)">>./examples/CMakeLists.txt
echo "if (DPP_USE_WINDOW_WAYLAND)">>./examples/CMakeLists.txt
echo "    find_package(ECM REQUIRED NO_MODULE)">>./examples/CMakeLists.txt
echo "    list(APPEND CMAKE_MODULE_PATH \"\${ECM_MODULE_PATH}\")">>./examples/CMakeLists.txt
echo "    find_package(Wayland REQUIRED Client Cursor Egl)">>./examples/CMakeLists.txt
echo "    find_package(WaylandScanner REQUIRED)">>./examples/CMakeLists.txt
echo "    find_package(WaylandProtocols 1.15 REQUIRED)">>./examples/CMakeLists.txt
echo "    list(APPEND DPP_WINCS \"\${Wayland_INCLUDE_DIRS}\")">>./examples/CMakeLists.txt
echo "    list(APPEND DPP_WLIBS \"\${Wayland_LIBRARIES}\" \"\${CMAKE_THREAD_LIBS_INIT}\")">>./examples/CMakeLists.txt
echo "    find_package(XKBCommon REQUIRED)">>./examples/CMakeLists.txt
echo "    list(APPEND DPP_WINCS \"\${XKBCOMMON_INCLUDE_DIRS}\")">>./examples/CMakeLists.txt
echo "    check_include_files(xkbcommon/xkbcommon-compose.h HAVE_XKBCOMMON_COMPOSE_H)">>./examples/CMakeLists.txt
echo "    check_function_exists(memfd_create HAVE_MEMFD_CREATE)">>./examples/CMakeLists.txt
echo "    if (NOT (\"\${CMAKE_SYSTEM_NAME}\" STREQUAL \"Linux\"))">>./examples/CMakeLists.txt
echo "        find_package(EpollShim)">>./examples/CMakeLists.txt
echo "        if (EPOLLSHIM_FOUND)">>./examples/CMakeLists.txt
echo "            list(APPEND DPP_WINCS \"\${EPOLLSHIM_INCLUDE_DIRS}\")">>./examples/CMakeLists.txt
echo "            list(APPEND DPP_WLIBS \"\${EPOLLSHIM_LIBRARIES}\")">>./examples/CMakeLists.txt
echo "        endif()">>./examples/CMakeLists.txt
echo "    endif()">>./examples/CMakeLists.txt
echo "elseif (UNIX)">>./examples/CMakeLists.txt
echo "    find_package(X11 REQUIRED)">>./examples/CMakeLists.txt
echo "    list(APPEND DPP_WINCS \"\${X11_X11_INCLUDE_PATH}\")">>./examples/CMakeLists.txt
echo "    list(APPEND DPP_WLIBS \"\${X11_X11_LIB}\"" >>./examples/CMakeLists.txt
echo "                            \"\${CMAKE_THREAD_LIBS_INIT}\")">>./examples/CMakeLists.txt
echo "    if (NOT X11_Xrandr_INCLUDE_PATH)">>./examples/CMakeLists.txt
echo "        message(FATAL_ERROR \"RandR headers not found; requires libxrandr development package\")">>./examples/CMakeLists.txt
echo "    endif()">>./examples/CMakeLists.txt
echo "    if (NOT X11_Xinerama_INCLUDE_PATH)">>./examples/CMakeLists.txt
echo "        message(FATAL_ERROR \"Xinerama headers not found; requires libxinerama development package\")">>./examples/CMakeLists.txt
echo "    endif()">>./examples/CMakeLists.txt
echo "    if (NOT X11_Xkb_INCLUDE_PATH)">>./examples/CMakeLists.txt
echo "        message(FATAL_ERROR \"XKB headers not found; requires X11 development package\")">>./examples/CMakeLists.txt
echo "    endif()">>./examples/CMakeLists.txt
echo "    if (NOT X11_Xcursor_INCLUDE_PATH)">>./examples/CMakeLists.txt
echo "        message(FATAL_ERROR \"Xcursor headers not found; requires libxcursor development package\")">>./examples/CMakeLists.txt
echo "    endif()">>./examples/CMakeLists.txt
echo "    if (NOT X11_Xi_INCLUDE_PATH)">>./examples/CMakeLists.txt
echo "        message(FATAL_ERROR \"XInput headers not found; requires libxi development package\")">>./examples/CMakeLists.txt
echo "    endif()">>./examples/CMakeLists.txt
echo "    list(APPEND DPP_WINCS \"\${X11_Xrandr_INCLUDE_PATH}\"">>./examples/CMakeLists.txt
echo "                            \"\${X11_Xinerama_INCLUDE_PATH}\"">>./examples/CMakeLists.txt
echo "                            \"\${X11_Xkb_INCLUDE_PATH}\"">>./examples/CMakeLists.txt
echo "                            \"\${X11_Xcursor_INCLUDE_PATH}\"">>./examples/CMakeLists.txt
echo "                            \"\${X11_Xi_INCLUDE_PATH}\")">>./examples/CMakeLists.txt
echo "else()">>./examples/CMakeLists.txt
echo "    message(FATAL_ERROR \"No supported window system was found\")">>./examples/CMakeLists.txt
echo "endif()">>./examples/CMakeLists.txt
echo "link_libraries(\${CMAKE_DL_LIBS})">>./examples/CMakeLists.txt
echo "link_libraries(\${CMAKE_SOURCE_DIR}/../libDrawpp.a)">>./examples/CMakeLists.txt
echo "link_libraries(\${DPP_WLIBS})">>./examples/CMakeLists.txt
echo "include_directories(\${CMAKE_SOURCE_DIR}/../include)">>./examples/CMakeLists.txt
echo "set(EXECUTABLE_OUTPUT_PATH \${CMAKE_BINARY_DIR}/bin)">>./examples/CMakeLists.txt
echo "include_directories(\${DPP_WINCS})">>./examples/CMakeLists.txt


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
rm -rf ./lib
rm -rf ./external
rm -rf ./CMakeFiles

echo "Done!"