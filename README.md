[Processing](https://processing.org/) style graphic library for c++ using OpenGL. Support for Windows and Linux desktops and Raspberry Pi 3 upwards.\
Linux build is X11 and Wayland native.
#### Note: Latest tested Windows build is the [1.0.0 release](https://gitlab.com/Trapigtrogen/graphics-library/-/releases/v1.0.0). I don't have any Windows machines or knowledge of what is needed for Windows. Master may or may not work.

For an in-depth user's manual, see the [beginner's guide](drawpp_guide.md).

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

# Building
Install git\
Clone with `git clone https://gitlab.com/Trapigtrogen/graphics-library.git` where ever you want. graphics-library folder will be downloaded.

## Automatic
A scripts for building releases is provided in the project's root directory.\
Windows script 'build-release.bat' assumes you have cmake and Visual Studio installed.\
On Linux there's 'install-dependencies.sh' which installs dependencies using you distro's package manager. 'build-release.sh' for building the release.

Release folder will be created and deployed program will be build there.\
External libraries are automatically combined to the releaseable Drawpp library.

## Manual
The build tests and examples will be in graphics-library/build/bin folder\
And library in graphics-library/build/lib folder.

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
and open the snl with Visual Studio

### Linux
You need to install your distripution's development packages:
* __Arch__ `sudo pacman -Sy base-devel cmake --needed --noconfirm`
  * If you want to build docs install `doxygen` as well
* __Debian__/__Raspberry Pi OS__  `sudo apt-get -y install g++ cmake libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglu1-mesa-dev libxxf86vm-dev`
  * On Ubuntu the doxygen package is not found by default. You need to add `universe` repository first: `sudo apt-add-repository universe`
  * Then you can install `doxygen` normally
  * Ubuntu cannot link some libraries so the release won't work. Any other debian based should work just fine
* On Raspberry Pi make sure that you are using Legacy OpenGL driver from `sudo raspi-config` -> Advanced options -> GL Driver -> Legacy - Original non-GL desktop driver

Type following in the terminal:
```
cd <path to graphics-library>

mkdir build
cd build
cmake ..
make
```
If you want to merge external libraries into the releaseable Drawpp library use `ar -M <combine` in build directory
