
// In this example we will make a simple paint application.

#include <drawpp.hpp>

// Current brush size
float brush_size = 5.0f;

// Set some limits for the brush size
float brush_min = 1.0f;
float brush_max = 100.0f;

// setup is called once before the application loop starts
void setup()
{
    // Initialize stroke
    strokeWeight(brush_size);

    // Clear background
    background(220,220,220);
}

// draw is called once every frame
void draw(float)
{
    // We don't actually need draw for this example
}

// mouseDragged is called every time a mouse button is pressed down
// and the mouse is moved
void mouseDragged()
{
    // Draw a line from the current mouse position to the previous mouse position
    line(mouseX,mouseY,pmouseX,pmouseY);
}

// mouseWheel is called every time a mouse wheel is scrolled
// 't' indicates the distance and direction of the scroll
void mouseWheel(float t)
{
    // Calculate a new brush size 

    float new_brush = brush_size + t;

    if(new_brush > brush_max)
    {
        brush_size = brush_max;
    }
    else if(new_brush < brush_min)
    {
        brush_size = brush_min;
    }
    else
    {
        brush_size = new_brush;
    }

    strokeWeight(brush_size);
}

// keyPressed is called every time a keyboard key is pressed
// 'key' is the keycode of the last keyboard key to be pressed
void keyPressed()
{
    switch (key)
    {
        // Clear the window when spacebar is pressed
        case VK_SPACE: background(220,220,220); break;

        // Change the stroke color when number keys are pressed
        case VK_0: stroke(0,0,0);       break;
        case VK_1: stroke(255,255,255); break;
        case VK_2: stroke(255,0,0);     break;
        case VK_3: stroke(0,200,0);     break;
        case VK_4: stroke(0,0,255);     break;
        case VK_5: stroke(255,255,0);   break;
        case VK_6: stroke(255,0,255);   break;
        case VK_7: stroke(0,200,200);   break;
        case VK_8: stroke(255,200,100); break;
        case VK_9: stroke(100,200,255); break;

        // Save a screenshot when 'S' is pressed
        case VK_S: save("paintImage"); break;
    }
}

int main()
{
    // Create the application object
    Application app(1000,1000,"Drawpp example: Draw");

    // Set the input callbacks
    app.setMouseDragged(mouseDragged);
    app.setMouseWheel(mouseWheel);
    app.setKeyPressed(keyPressed);

    // Run the application
    return app.run(draw,setup);
}