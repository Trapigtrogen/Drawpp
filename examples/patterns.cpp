
// Patterns - Processing example from:
// https://processing.org/examples/pattern.html

#include <drawpp.hpp>

// The simple method variableEllipse() was created specifically 
// for this program. It calculates the speed of the mouse
// and draws a small ellipse if the mouse is moving slowly
// and draws a large ellipse if the mouse is moving quickly 
void variableEllipse(int x, int y, int px, int py) {
    float speed = abs(x - px) + abs(y - py);
    stroke(speed);
    ellipse(x, y, speed, speed);
}

// setup is called once before the application loop starts
void setup() 
{
    size(640, 360);
    background(102);
}

// draw is called once every frame
void draw(float) 
{
    // Call the variableEllipse() method and send it the
    // parameters for the current mouse position
    // and the previous mouse position
    variableEllipse(mouseX, mouseY, pmouseX, pmouseY);
}

int main()
{
    // Create the application object
    Application app(1000,1000,"Drawpp example: Patterns");

    // Run the application
    return app.run(draw,setup);
}