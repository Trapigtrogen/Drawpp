
// In this example we will change background 
// color with mouse wheel

#include <drawpp.hpp>

Color bg_color;
float bg_hue = 0.0f;

// setup is called once before the application loop starts
void setup()
{
    // Set color mode to hsb, with
    // hue in range 0 - 360
    // saturation in range 0 - 100
    // brightness in range 0 - 100
    colorMode(HSB,360.0f,100.0f,100.0f);

    // Initialize color to light red
    bg_color = color(bg_hue,60.0f,100.0f);
}

// draw is called once every frame
void draw(float)
{
    // Fill background
    background(bg_color);
}

// mouseWheel is called every time a mouse wheel is scrolled
// 't' indicates the distance and direction of the scroll
void mouseWheel(float t)
{
    // Add 5 or -5 to hue depending on scroll direction
    bg_hue += t*5;

    // Create a new background color from the new hue
    bg_color = color(bg_hue,60.0f,100.0f);
}

int main()
{
    // Create the application object
    Application app(1000,1000,"Drawpp example: Color Mousewheel");

    // Set the input callbacks
    app.setMouseWheel(mouseWheel);

    // Run the application
    return app.run(draw,setup);
}