Beginners guide to Drawpp
===

## Table of contents
- [Building the library](#build)
- [Generating a release](#release)
    - [Prerequisites](#release_prerequisites)
- [Simple application](#simpleapp)
- [Setup and cleanup](#setupcleanup)
- [Drawing functions](#drawing_functions)
- [Drawing properties](#drawing_properties)


<br>

## <a id="build">Building the library</a> 

<br>To build the library, you will be using CMake (at least version 3.13.4). You can do this using CMake-gui, or on the command line.<br>

Before that though, you should run `git submodule update --init --recursive`, to make sure all submodules are present.<br>

Now, you will need to create a directory where the build will be generated. In this example we'll create a directory called `build`, right in the Drawpp project directory.<br>

On the command line, this is done with the command `mkdir build`.<br>

Next, navigate into the build directory with `cd build`.<br>
Now, run CMake, with `cmake ..`.<br>
If your build folder is elsewhere, you should replace the `..`, with the path to the project directory.<br>
If you want to configure the project, you can do that by adding `-D<option-name>=<state>`, where `state` is either `ON` or `OFF`. The option names can be found in the `CMakeLists.txt` file, near the beginning.<br><br>

If you are using CMake-gui, you should put the project directory path to the `Where is the source code` field, and the build directory path to the `Where to build the binaries` field.<br>
When those are set, press the `Configure` button to configure the project, though you don't have to, if you are fine with the default options. If you do want to configure the project, only the options beginning with DPP_ should be modified.<br>
To generate the build files, press the `Generate` button, and select your generator.<br><br>


At this point, if you are on Windows, you will find a Visual Studio project called `Drawpp.sln`, in the `build` directory. You can go ahead and build it using Visual Studio.<br>

On Linux, makefiles will have been generated into the `build` directory, and you can build the library with the `make` command.<br>

<br>

## <a id="release">Generating a release</a>

<br>Generating a release is done with `build_release` script. On Windows, use the batch version, on Linux, use the shell version. The script will ask you for some options for the release. If you don't care about those, you can generate a default release by passing -f flag to the script.<br>

#### <a id="release_prerequisites">Prerequisites</a>

Both versions of the script require you to have CMake (at least version 3.13.4), and git installed on your system.<br>
If you need to generate the documentation, you must have Doxygen installed on your system.<br>

On Windows, you will need Visual Studio.<br>

On Linux, you must have the development packages for you distribution. These can be installed using the `install_dependencies.sh` script.<br>

<br>

## <a id="simpleapp">Simple application</a>

<br>When creating an application with the Drawpp library, you will first have to include the main header in your file.<br>

```cpp
#include "drawpp.hpp"
```

<br>Next up, create a function for the application loop. We'll call it draw, and it should look something like this:<br>

```cpp
void draw(float t)
{

}
```

<br>The parameter `float t` will tell you the time elapsed during the last cycle (or frame).
Next, create the main function.<br>

```cpp
int main()
{

}
```

<br>In the main function, we want to create our application instance. As parameters for the constructor, you should give the width and height of the application window. You can also give a title for the window.<br>


```cpp
Application app(500,500,"Drawpp application");
```

<br>Now all that's left is to start the application. This can be done with the member function ***run***. It will take as parameters, the loop function we created earlier, and some optional parameters which we'll look at in the next section. The ***run*** function will also return an error code, so we can use that as the return value from main.<br>


```cpp
return app.run(draw);
```

<br>Lastly, so that we don't have to look at a back screen, put a call to the ***background*** function inside of the *draw* function. The ***background*** function will color the window with the color we give it.<br>


```cpp
background(200,255,100);
```

<br>And now we're done. You now should be able to build and run the application.
Here is the full code we wrote for this app:<br>

```cpp
#include "drawpp.hpp"

void draw(float t)
{
    background(200,255,100);
}

int main()
{
    Application app(500,500,"Drawpp application");
    return app.run(draw);
}
```

<br>

## <a id="setupcleanup">Setup and cleanup</a>

<br>Often you need to initialize some things at the beginning of your program. Normally you would do that in the beginning of the main function, but when using the Drawpp library, we strongly recommend you do all initializing in a setup function. This is because a lot of things need the application to be running to work.<br>

Here is an example of a setup function:<br>

```cpp
void setup()
{
    strokeWeight(5);
}
```

<br> There, we call the ***strokeWeight*** function. Were you to call it in main, before starting the application, the program would probably crash. The ***strokeWeight*** function will set the thickness of a stroke, or a line that will be draw.<br>

To run the setup function, you should give it as a parameter to the *app.run* function, when starting up your application:<br>

```cpp
app.run(draw,setup);
```

<br>The setup function will be called once by the application, before it starts the draw loop.<br>

Conversely, if you need to do any cleanup after the application exits, you can create a cleanup function, and pass that to the *app.run* function as well:<br>

```cpp
app.run(draw,setup,cleanup);
```

<br>The cleanup function will be called right after the draw loop had exited.<br>

<br>

## <a id="drawing_functions">Drawing functions</a>

<br>The Drawpp library provides several drawing functions. All of them have at least two overloads, one where the position and size parameters are floats, and one where they are vectors.<br>

When deciding where to draw, note that the coordinate (0,0) is in the upper left corner of the window. The X coordinate increases to the right, and the Y coordinate increases down.<br>

Here is a list of the drawing functions, not including their overloads. A full list, and detailed descriptions can be found in the generated documentation.

- shape()
- circle()
- ellipse()
- line()
- point()
- quad()
- rect()
- square()
- triangle()
- bezier()
- text()
- image()
- background()
- clear()

#### Example

<br>You can use the drawing functions anywhere, after the application has been started. This example will draw a rectangle on a green background.<br>


```cpp
void draw(float t)
{
    background(colors::green);

    rect(100,100,300,500);
}
```

<br>Here, the first two parameters for the ***rect*** call are it's position, and the next two are it's size.<br>
The parameter for the ***background*** call, is a color constant provided by the library. The ***background*** function will fill the whole window with the given color.<br>

<br>

## <a id="drawing_properties">Drawing properties</a>

<br>When drawing, there are some options you can change. These options will determine how things are drawn.<br>
Some of the functions listed have several overloads, details of which you can loop up in the generated documentation.<br>

- fill()
    - Set the fill color, which will be used when drawing primitives.
- stroke()
    - Set the stroke color, which will be used when drawing primitives.
- tint()
    - Set the tint color, which will be used when drawing images.
- noFill()
    - Disable filling entirely.
    - By default, filling is enabled.
- noStroke()
    - Disable stroke entirely.
    - By default, stroke is enabled.
- noTint()
    - Disable tint entirely.
    - By default, tint is disabled.
- strokeWeight()
    - Set the stroke thickness, which will be used when drawing primitives and lines.
- strokeCap()
    - Set the stroke cap style. This affects lines and points.
    - By default, stroke cap style is round.
- bezierDetail()
    - Set the amount of detail to be used, when drawing bézier curves.
- rectMode()
    - Set the position mode which will be used for rectangles and squares.
    - By default, rect mode is corner.
- ellipseMode()
    - Set the position mode which will be used for ellipses and circles.
    - By default, rect mode is center.
- imageMode()
    - Set the position mode which will be used for images.
    - By default, rect mode is corner.
- textFont()
    - Set the font which will be used for drawing text.
    - By default, no font is set, so to draw text, you must first set a font.


<br>Position modes dictate what is considered the origin of the thing being drawn. Position mode ***CORNER*** means that the origin is in the upper left corner. For example, were you to draw a square in the coordinates (100,100), the upper left corner of the square, will be in the position (100,100).<br>
Position mode ***CENTER***, means that the origin is in the center.