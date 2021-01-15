Processing style graphic library for c++ using OpenGL

# Building
Clone with `git clone git@gitlab.com:Trapigtrogen/graphics-library.git --recursive` to get the dependensies also

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

Type following in the terminal:
```
cd <path to graphics-library>

md build
cd build
cmake ..
make
```
\
\
The build files will be in graphics-library/bin folder
