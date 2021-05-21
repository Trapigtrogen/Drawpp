
// Tickle - Processing example from:
// https://processing.org/examples/tickle.html

#include <drawpp.hpp>

float x, y; // X and Y coordinates of text
float hr, vr;  // horizontal and vertical radius of the text

void setup() {
    // Load font from assets folder to show our text with
    textFont(loadFont("assets/Tuffy.ttf", 30));

    hr = 100;
    vr = 30;
    noStroke();
    x = 320;
    y = 180;
}

void draw(float) {
    // Instead of clearing the background, fade it by drawing
    // a semi-transparent rectangle on top
    fill(204, 120);
    rect(0, 0, 640, 360);
        
    // If the cursor is over the text, change the position
    if (abs(mouseX - x) < hr &&
        abs(mouseY - y) < vr) {
        x += randomInt(-5, 5);
        y += randomInt(-5, 5);
    }
    fill(0);
    text("tickle", x, y);
}

int main()
{
    // Create the application object
    Application app(640, 360, "Drawpp example: Tickle");

    // Run the application
    return app.run(draw, setup);
}