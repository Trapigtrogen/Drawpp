// In this example we draw to a offscreen target,
// and draw that to the window.

#include <drawpp.hpp>

// Target used for drawing
DGraphics draw_target;

// setup is called once before the application loop starts
void setup()
{
    // Initialize the draw target. This must be done
    // in setup, and not any earlier
    draw_target = DGraphics(1000,1000);

    // Set stroke weight of out target to 50
    draw_target.strokeWeight(50);

    // Set stroke weight of the global target to 5
    strokeWeight(5);
}


// draw is called once every frame
void draw(float t)
{
    // To start drawing to our target, call beginDraw
    draw_target.beginDraw();

    // Fill the background, and draw a point at mouse position
    draw_target.background(200,255,100);
    draw_target.point(mouseX,mouseY);

    // To end drawing to our target, call endDraw
    draw_target.endDraw();


    // Draw the target as an image, 4 times
    image(draw_target,0,0,500,500);
    image(draw_target,500,0,500,500);
    image(draw_target,0,500,500,500);
    image(draw_target,500,500,500,500);


    // Draw some lines to make the image borders clear
    line(500,0,500,1000);
    line(0,500,1000,500);
}

int main()
{
    // Create the application object
    Application app(1000,1000,"Drawpp example: Repeat window");

    // Run the application
    return app.run(draw,setup);
}