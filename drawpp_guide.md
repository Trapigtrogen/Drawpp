Beginner's guide to Drawpp
===

## Table of contents
- [Building the library](#building-the-library)
- [Generating a release](#generating-a-release)
    - [Prerequisites](#prerequisites)
- [Simple application](#simple-application)
- [Setup and cleanup](#setup-and-cleanup)
- [Drawing functions](#drawing-functions)
- [Drawing properties](#drawing-properties)
- [Transforms](#transforms)
- [Stacks](#stacks)
- [Input](#input)
- [Colors](#colors)
- [Time](#time)
- [Random](#random)
- [Noise](#noise)
- [File loading](#file-loading)
- [Miscellaneous](#miscellaneous)
- [Offscreen drawing](#offscreen-drawing)
- [Filters](#filters)

<br>

## <a id="building-the-library">Building the library</a> 

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

## <a id="generating-a-release">Generating a release</a>

<br>Generating a release is done with `build_release` script. On Windows, use the batch version, on Linux, use the shell version. The script will ask you for some options for the release. If you don't care about those, you can generate a default release by passing -f flag to the script.<br>

#### <a id="prerequisites">Prerequisites</a>

Both versions of the script require you to have CMake (at least version 3.13.4), and git installed on your system.<br>
If you need to generate the documentation, you must have Doxygen installed on your system.<br>

On Windows, you will need Visual Studio.<br>

On Linux, you must have the development packages for you distribution. These can be installed using the `install_dependencies.sh` script.<br>

<br>

## <a id="simple-application">Simple application</a>

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

<br>Now all that's left is to start the application. This can be done with the member function ***run()***. It will take as parameters, the loop function we created earlier, and some optional parameters which we'll look at in the next section. The ***run()*** function will also return an error code, so we can use that as the return value from main.<br>


```cpp
return app.run(draw);
```

<br>Lastly, so that we don't have to look at a back screen, put a call to the ***background()*** function inside of the *draw* function. The ***background()*** function will color the window with the color we give it.<br>


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

## <a id="setup-and-cleanup">Setup and cleanup</a>

<br>Often you need to initialize some things at the beginning of your program. Normally you would do that in the beginning of the main function, but when using the Drawpp library, we strongly recommend you do all initializing in a setup function. This is because a lot of things need the application to be running to work.<br>

Here is an example of a setup function:<br>

```cpp
void setup()
{
    strokeWeight(5);
}
```

<br> There, we call the ***strokeWeight()*** function. Were you to call it in main, before starting the application, the program would probably crash. The ***strokeWeight()*** function will set the thickness of a stroke, or a line that will be drawn.<br>

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

## <a id="drawing-functions">Drawing functions</a>

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

<br>Here, the first two parameters for the ***rect()*** call are it's position, and the next two are it's size.<br>
The parameter for the ***background()*** call, is a color constant provided by the library. The ***background()*** function will fill the whole window with the given color.<br>

<br>

## <a id="drawing-properties">Drawing properties</a>

<br>When drawing, there are some options you can change. These options will determine how things are drawn.<br>
Some of the functions listed have several overloads, details of which you can look up in the generated documentation.<br>

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
- clip()
    - Restrict the drawing area to a rectangle.
- noClip()
    - Disable clipping.


<br>Position modes dictate what is considered the origin of the thing being drawn. Position mode ***CORNER*** means that the origin is in the upper left corner. For example, were you to draw a square in the coordinates (100,100), the upper left corner of the square, will be in the position (100,100).<br>
Position mode ***CENTER***, means that the origin is in the center.<br>


<br>

## <a id="transforms">Transforms</a>

<br>On their own, the drawing functions can't for example draw rotated shapes. To achieve this, you can use the transform functions.<br>

- translate()
    - Displaces the scene by the given amounts.
- rotate()
    - Rotates the scene by the given angle (radians), around the origin.
- scale()
    - Scales the scene by the given amounts.
- shearX()
    - Shears the scene in the X-axis.
- shearY()
    - Shears the scene in the Y-axis.
- applyMatrix()
    - Multiply the current transform matrix by your own.


<br>It should be noted, that the transformations don't affect already drawn elements. Only the calls after the transformation will be affected. The transform matrix is also reset after every loop cycle.<br>


<br>

## <a id="stacks">Stacks</a>

<br>Sometimes you may want to save transformations or properties between between drawing calls. This can be done with the transform stack, and property stack. To use them, you can call ***pushMatrix()*** and ***popMatrix()***, and ***pushStyle()*** and ***popStyle()***.<br>

***pushMatrix()*** will push the current transform matrix onto the transform stack. You can then freely call the transformation functions, and at any point, restore the pushed matrix with ***popMatrix()***. <br>
Same logic applies to the properties, with ***pushStyle()*** and ***popStyle()***.<br>

Additionally, if you want to save both at the same time, you can call ***push()***, and then ***pop()*** to restore them.<br>

The stacks are persistent between cycles.<br>


<br>

## <a id="input">Input</a>

<br>The library provides several callbacks and variables for input handling. The callbacks must be assigned before running the application. For example, if we want to know when a keyboard key was pressed, we would create a function called ***keyPressed***, and then assign the callback like this:<br>



```cpp
void main()
{
    Application app(500,500);

    // Here we assign the keyPressed callback
    app.setKeyPressed(keyPressed);

    return app.run(draw);
}
```

<br>Here is a list of all the available input callbacks:
- keyPressed
    - Called every time a keyboard key is pressed.
    - Use the *key* and *keyCode* variables to get the key that was pressed.
- keyReleased
    - Called every time a keyboard key is released.
    - Use the *key* and *keyCode* variables to get the key that was released.
- mouseClicked
    - Called when a mouse button is pressed down, and then released.
    - Use the *mouseButton* variable to get the button that was clicked.
- mousePressed
    - Called every time a mouse button is pressed.
    - Use the *mouseButton* variable to get the button that was pressed.
- mouseReleased
    - Called every time a mouse button is released.
    - Use the *mouseButton* variable to get the button that was released.
- mouseWheel
    - Called every time the mouse wheel is moved.
    - Takes one float as parameter, which will be the distance the mouse wheel was scrolled. The direction of the scroll can be interpreted from the sign of the value.
- mouseMoved
    - Called every time the mouse is moved, and no mouse buttons are being pressed.
- mouseDragged
    - Called every time the mouse is moved, while a mouse button is pressed.

<br>Of all of these, only mouseWheel takes any parameters.<br>

In addition to the input callbacks, you also have some variables at your disposal:
- key
    - The last keyboard key that was pressed.
    - If the keyboard key cannot be represented as an ascii character, key will be equal to CODED (or 0).
- keyCode
    - Keycode of the last keyboard key that was pressed.
    - This will always hold the proper keycode, even if key is CODED.
- mouseButton
    - Id of the last mouse button to be pressed or released.
- mouseX
    - Latest mouse X position.
- mouseY
    - Latest mouse Y position.
- pmouseX
    - Previous mouse X position.
- pmouseY
    - Previous mouse Y position.
- pfmouseX
    - Last mouse X position of the previous cycle.
- pfmouseY
    - Last mouse Y position of the previous cycle.

<br>Here is an example:<br>


```cpp
void keyPressed()
{
    if(key == 'a')
    {
        puts("Pressed a");
    }
    else if(key == VK_ESC)
    {
        exit();
    }
}

void main()
{
    Application app(500,500);

    app.setKeyPressed(keyPressed);

    return app.run(draw);
}
```

<br>Above, in the keyPressed function, we check if the key 'a' was pressed, and if so, print "Pressed a". If instead of 'a', 'escape' was pressed, we quit the application. Note that we compare escape with VK_ESC. Since escape is an ascii character, we could compare it with '\0x1B', 0x1B, '\033' or 27 as well. But VK_ESC is much easier to remember and understand, so prefer using it.<br>
You can also test the alphanumeric keys with for example VK_A, but in this case whether you use 'a' or VK_A, doesn't really make a difference in understanding the code. Note however that only lowercase character literals will work, so for example 'A' is invalid.<br>


<br>

## <a id="colors">Colors</a>

<br>For colors, we have the Color, and HSBColor classes.<br>

The Color class will hold four 8 bit values, representing the red, green, blue and alpha channels. Every channel will be in range [0, 255].<br>
The HSBColor class will hold four floating point values, representing the hue, saturation, brightness, and alpha components. The hue is in range [0.0, 360.0], and the other components are in range [0.0, 100.0].<br>

You can use these classes to work with colors, but if you want more flexibility, you can use the ***color()*** function.<br>
Using it, you can set your own ranges for color components. By default, it will interpret the passed values as RGBA, in range [0, 255].<br>

To change the ranges, and between RGB and HSB modes, use the ***colorMode()*** function.
The first parameter is always either RGB, or HSB, and the subsequent parameters will dictate the ranges for the components. See details in the generated documentation.<br>

Whatever ranges you set, the Color object created will still have its values in the range [0, 255].<br>
If you want to extract the components from a Color object, in the ranges you have defined, you can use the following functions:
- red()
- green()
- blue()
- alpha()
- hue()
- saturation()
- brightness()

These functions all take a Color object as a parameter.<br>

Sometimes you may want to mix colors together. For this, you we have the ***lerpColor()*** function. You pass it two colors, and a t-value. The t-value should be in range [0.0, 1.0], and will dictate the amount of either color in the result.<br>

If you want to use a hex value in the form of a string to define your colors, you can call the constructor of the Color object with your string.<br>
If you need to convert a color back into a hex string, you can use the ***hex()*** function.<br>

The library also provides a small number of colors in the ***colors*** namespace:
- red
- green
- blue
- yellow
- orange
- cyan
- purple
- brown
- magenta
- pink
- violet
- maroon
- turquoise
- lime
- teal
- indigo
- tan
- olive
- indigo
- black
- white
- grey


<br>

## <a id="time">Time</a>

<br>In the draw function, you already have the delta time at your disposal, but you may want some additional information about time. Here is a list of time related functions:

- millis()
    - Get the number of milliseconds since last counter reset. 
- second()
    - Get the current second of the system clock.
- minute()
    - Get the current minute of the system clock.
- hour()
    - Get the current hour of the system clock.
- day()
    - Get the current day of the system clock.
- month()
    - Get the current month of the system clock.
- year()
    - Get the current year of the system clock.
- timeReset()
    - Resets the millisecond counter.


<br>

## <a id="random">Random</a>

<br>Often you will need random numbers. Here are some functions you can use to generate them:

- randomInt()
    - Generate a random integer in the given range.
- randomFloat()
    - Generate a random float in the given range.
- randomGaussian()
    - Generate a float in a gaussian distribution.
    - The mean for the distribution is 0.0, and standard deviation is 1.0.
- randomSeed()
    - Set a new seed for the random number generator.

If you need multiple generators, you can use the Random class. It will also have the above functions, and in fact, the above functions are using an instance of Random in the background. The Random class also has a convenience function ***randomFloat01()***, which will generate a random float in [0.0, 1.0) range.<br>


<br>

## <a id="noise">Noise</a>

<br>If you need procedural 1D or 2D noise, you can these functions:

- noise()
    - Get a value from the given coordinate.
- noiseSeed()
    - Set a new seed for the noise.
- noiseScale()
    - Set a new scale for the noise.
    - Affects the intensivity of the value spikes.
    - This is 1.3 by default.
- noiseDetails()
    - Set the amount of detail in the noise.
    - Two parameters: Octaves and falloff.
    - Octaves affect the blurriness of the map and falloff affects the zoom.
    - Octaves is 8 by default. Falloff is 0.5.
- noiseMapSize()
    - Change the size/resolution of the generated noise.

As with random numbers, you can have multiple noise generators by using the Noise class.<br>


<br>

## <a id="file-loading">File loading<a/>

<br>If you want images, or fonts, you need to load them from files. Here are the functions for that:

- loadImage()
    - Loads an image from the given path.
    - Supported formats are: png, jpg, bmp, tga, psd, pnm, ppm and pgm.
- loadSVGImage()
    - Loads an SVG image from the given path.
- loadFont()
    - Loads a font from the given path.
    - Supported formats: ttf, otf, pfa, pfb and cef.
    - See generated documentation for details.
- loadShape()
    - Loads an SVG file from the given path, as a shape.
- loadFilterFromFile()
    - Loads a post-processing filter from a file.


<br>

## <a id="miscellaneous">Miscellaneous</a>

<br>Here are various functions you can use for different things:

- exit()
    - Quit the application.
    - Calling this will not immediately exit, instead, the application will terminate after the current cycle is complete.
- frameRate()
    - Set the maximum framerate the application can run at.
- vSync()
    - Enable or disable vsync.
- cursor()
    - Set the mouse cursor to an icon of your choice.
    - You can either use one of the icons provided by the system, or your own.
    - The system icons are: ARROW, HAND, CROSS and TEXT.
- noCursor()
    - Hide the cursor.
- size()
    - Resize the window.
- fullScreen()
    - Set the application to fullscreen mode.
    - fullScreen takes one int as a parameter, which will be the id of the monitor you want to use.
    - To exit fullscreen mode, call size().
- setTitle()
    - Set the window title.
- setLocation()
    - Set the application window location.
    - Location is relative to the top left corner of the primary monitor.
- getMonitorWidth()
    - Get the pixel width of a given monitor.
- getMonitorHeight()
    - Get the pixel height of a given monitor. 
- delay()
    - Stop the application for a number of milliseconds.
- save()
    - Save a screenshot to the given path.
- saveFrame()
    - Save a screenshot to a given path, with the frame number appended.
    - Appended frame number will be padded with zeros to up to 5 digits.
    - Make your own format by using '#' characters in the path to mark the place for the frame number.


<br>In addition to these functions, there is also a couple of variables:

- focused
    - true if the application window is currently focused, false otherwise
- frameCount
    - The number of rendered frames that have been displayed since application startup.


<br>

## <a id="offscreen-drawing">Offscreen drawing</a>

<br>If you want to draw to a different draw target than the application window, you can use the DGraphics class.<br>
You can take a look at the generated documentation for details, but DGraphics has all of the drawing and color related functions mentioned previously.<br>
When you draw to a DGraphics target, you must first call ***beginDraw()***, and when you are finished, call ***endDraw()***. Between them, you must not draw to any other target, or things will break.<br>

Here is an example:<br>

```cpp
DGraphics mytarget;

void draw(float t)
{
    mytarget.beginDraw();

    mytarget.background(colors::tan);
    mytarget.strokeWeight(20);
    mytarget.rect(100,100,200,300);
    mytarget.line(300,400,400,100);

    mytarget.endDraw();
}
```

<br>All transforms, styles, stacks and everything else, are specific to a target. Meaning that, if you were to call ***strokeWeight(10)*** globally, the stroke weight of ***mytarget*** would not be affected.<br>

Now, after drawing to your custom target, you can save it to a file with its ***save()*** member function, or convert it to an image with ***toImage()***. You can also draw it to another target without converting it first, with the ***image()*** function. You might want to do that for example in a case where you will redraw the offscreen target every frame, as converting to image is a relative expensive process.<br>

Once again, remember to initialize your draw target in the ***setup()*** function, and not before that.<br>


<br>

## <a  id="filters">Filters</a>

<br>You can apply post-processing effects to your drawings with filters. There are some filters provided by the Drawpp library, and you can create your own as well.<br>

To use the provided filters, call the ***filter()*** function, with the filter you want to apply, and an optional parameter.<br>Here are couple examples:<br>

```cpp

void draw(float)
{
    filter(INVERT);
    filter(PIXELATE,5);
}
```

<br>Here is a full list of the provided filters:<br>

- PIXELATE
    - Pixelates the target.
    - Takes the pixel scale as a parameter.
- INVERT
    - Inverts the colors in the target.
- GREY
    - Greyscales the image.
- THRESHOLD
    - Takes a threshold value as a parameter (in range [0.0, 1.0]).
    - Will first greyscale the image, and then turn all colors below the threshold to black, and the rest to white.

<br>If you want to make your own filter, you can do that with the ***loadFilter()***, and ***loadFilterFromFile()*** functions. The former takes the filter source code as a string, and the latter will load it from a file.<br>

The filters are written in GLSL ES 1.0.0, and you can read the documentation of that if you want to learn more.<br>In the filter however, you don't need to create anything else except for the ***main()*** function. You can also use a couple of uniforms provided by the library. Here is a list:<br>

- source
    - sampler2D
    - This is the image which the filter is applied to.
- source_size
    - vec2
    - Source image size.

<br>Note also, that the uniform name ***pos*** is reserved by the library. You can still have a variable called pos, but it cannot be a uniform.<br>

If you need uniforms in your filter, you can add them into the GLSL ES source. To set their values in runtime, you need to pass a initializer function to the ***filter()*** call, which will do the required OpenGL calls. This function must take one parameter of type unsigned int, which will be the shader program id for the filter. You don't have to use it, but the function signature must match. For all this, you need to include glad.h in your source code.<br>

Here is an example of a custom filter, recreating the pixelate effect:

```cpp
#include <drawpp.hpp>
#include <glad.h>

DFilter pixelate;
int pixelate_scale_location;

float pixel_scale = 10;

void setup()
{
    pixelate = loadFilter(R"(
        uniform float scale;
        void main()
        {
            vec2 pos = gl_FragCoord.xy/source_size;
            pos -= mod(pos, vec2(scale) / source_size);
            gl_FragColor = texture2D(source, pos);
        }
    )");

    glGetUniformLocation(pixelate.getProgram(),"scale");
}

void draw(float)
{
    filter(pixelate,[=](unsigned int p){
        glUniform1f(pixelate_scale_location,pixel_scale);
    });
}

int main()
{
    Application app(1000,1000);
    return app.run(draw,setup);
}
```

<br>Ideally, if you are creating your own filters, and setting uniforms in them, you'd be familiar with GLSL ES and the OpenGL API.<br>
In any case, here are explanations of the functions used in the above example:<br>

- glGetUniformLocation()
    - Takes a shader program id, and a uniform name string as parameters.
    - Will return the location of that uniform in the shader program.
- glUniform1f()
    - Takes a uniform location, and a float value as parameters.
    - Will set the uniform at the location, to the value.

The scale uniform location is cached because the operation of getting it is not very cheap. This is fine, because the location will not change, unless you recompile the filter. In newer versions of GLSL ES it's possible to set the uniform location explicitly in the shader, but we can't do that here.<br>

Another thing you can do with filters, is to just use them as shader renderers. You can draw whatever you want in them, and you can choose to ignore the *source* texture.
