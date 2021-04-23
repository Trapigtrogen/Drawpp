Processing style graphic library for c++ using OpenGL. Support for Windows and Linux desktops and Raspberry Pi 3 upwards.\
Linux: X11 only. Wayland works mostly but support for it isn't prioritized right now.

# Features
* Draw lines and basic shapes
* Render Image as texture
* Shape class with GameObject like parent-child hierarcy
  * Load SVG to shape (currently draws only the outlines)
  * SVG to texture for full image
* Color API
* Random API
* Perlin noise generator
* Load and render fonts

### Upcoming
* More stuff to do with vector graphics and SVG shapes

# Building
Clone with `git clone https://gitlab.com/Trapigtrogen/graphics-library.git --recursive` to get the dependensies also\
You can also update the submodule afterwards with `git submodule update --init`

## Automatic
We provide scripts for building releases.\
Windows script 'build-release.bat' assumes you have cmake and Visual Studio installed.\
On Linux there's 'install-dependencies.sh' which installs dependencies using you distro's package manager. 'build-release.sh' for building the release.

Release folder will be created and deployed program will be build there.\
External libraries are automatically combined to the releaseable Drawpp library

## Manual
The build tests and examples will be in graphics-library/build/bin folder\
And library in graphics-library/build/lib folder

### Windows
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

### Linux
You need to install your distripution's development packages:
* __Arch__ `sudo pacman -Sy base-devel git cmake`
* __Debian__/__Raspberry Pi OS__  `sudo apt-get -y install g++ git cmake libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libopenal-dev libglu1-mesa-dev libxxf86vm-dev`\
On Raspberry Pi make sure that you have using Legacy OpenGL driver from `sudo raspi-config` -> Advanced options -> GL Driver -> Legacy - Original non-GL desktop driver

Type following in the terminal:
```
cd <path to graphics-library>

mkdir build
cd build
cmake ..
make
```
If you want to merge external libraries into the releaseable Drawpp library use `ar -M <combine.mri` in build directory
