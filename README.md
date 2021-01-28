Processing style graphic library for c++ using OpenGL. Support for Windows and Linux desktops and Raspberry Pi 3 upwards

# Building
Clone with `git clone git@gitlab.com:Trapigtrogen/graphics-library.git --recursive` to get the dependensies also\
You can also update the submodule afterwards with `git submodule update --init`

## Windows

Use CMake-gui 

  * Where is the source code: "path to graphics-library"
  * Where to build the binaries: "path to graphics-library"\build

Configure and Generate the project files for your IDE

or type following in the Command Prompt:
```
cd <path to graphics-library>

md build
cd build
cmake ..
```

## Linux

You need to install your distripution's development packages:
* __Arch__ `sudo pacman -Sy base-devel`
* __Debian__ `sudo apt-get -y install g++ libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libopenal-dev libglu1-mesa-dev libxxf86vm-dev`
* __Raspberry Pi OS__ `sudo apt-get -y install g++ libglu1-mesa-dev libopenal-dev libxi-dev libxrandr-dev libxinerama-dev libxcursor-dev libxxf86vm-dev libx11-dev libgl1-mesa-dev libqt5webkit5-dev libqt5sensors5-dev qtlocation5-dev libxslt1-dev libsqlite3-dev libgstreamer-plugins-base0.10-dev qt5-default libicu-dev`\
In addition you might need to change the OpenGL driver from `sudo raspi-config` -> Advanced options -> GL Driver -> GL (Full KMS) OpenGL desktop driver with full KMS

Type following in the terminal:
```
cd <path to graphics-library>

mkdir build
cd build
cmake ..
make
```
\
\
The build tests and examples will be in graphics-library/build/bin folder\
And library in graphics-library/build/lib folder
