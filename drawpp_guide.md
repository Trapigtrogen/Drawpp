Beginners guide to Drawpp
===

## Table of contents
- [Building the library](#build)
- [Generating a release](#release)
- [Simple application](#simpleapp)


<br>

## <a id="build">Building the library</a> 

This is how you build the drawpp library, and generate documentation. <br>
*Not implemented*


<br>

## <a id="release">Generating a release</a>

This is how you generate a release of the drawpp library.<br>
*Not implemented*


<br>

## <a id="simpleapp">Simple application</a>

When creating an application with the drawpp library, you will first have to include the main header in your file.<br>
<br>
```cpp
#include "drawpp.hpp"
```

Next up, create a function for the application loop. We'll call it draw, and it should look something like this:<br>
<br>

```cpp
void draw(float t)
{

}
```

The parameter `float t` will tell you the time elapsed during the last cycle (or frame).<br>

Next, create the main function.

```cpp
int main()
{

}
```

In the main function, we want to create our application instance. As parameters for the constructor, you should give the width and height of the application window. You can also give a title for the window.

```cpp
Application app(500,500,"Drawpp application");
```

Now all that's left is to start the application. This can be done with the member function ***run***. It will take as parameters, the loop function we created earlier, and some optional parameters which aren't relevant right now. The ***run*** function will also return an error code, so we can use that as the return value from main.

```cpp
return app.run(draw);
```

Lastly, so that we don't have to look at a back screen, put a call to the ***background*** function inside of the *draw* function. The ***background*** function will color the window with the color we give it.

```cpp
background(200,255,100);
```

And now we're done. You now should be able to build and run the application. <br>
Here is the full code we wrote for this app:

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