// In this example we make a simple
// animation seqeuence with the shape functions.
//
// The animation is separated into 7 stages,
// and the stage will change at specified points.
//
// All stages use the variable val to control some 
// aspect of the shapes being drawn. val is increased 
// or decreased every frame to create the animation.

#include <drawpp.hpp>

// Current stage
int stage = 0;

// Value used for animation
float val = 0;

// setup is called once before the application loop starts
void setup()
{
    // Initialize some properties

    rectMode(CENTER);
    ellipseMode(CENTER);
    strokeCap(SQUARE);
    strokeWeight(20);
}

// draw is called once every frame
void draw(float t)
{
    // Fill the background
    background(200,255,100);

    // Move drawing to the center 
    translate(500,500);

    switch(stage)
    {
        // Start with a line that gets wider
        case 0:
        {
            val += 2;
            line(-val,0,val,0);

            if(val == 250)
            {
                stage = 1;
                val = 20;
            }
            break;
        }

        // After line is 500 pixels wide, draw a rectangle that gets taller
        case 1:
        {
            val += 4;
            rect(0,0,500,val);
            
            if(val == 500)
            {
                stage = 2;
                val = 0;
            }
            break;
        }

        // After rectangle is 500 pixels tall, beging rounding the corners
        case 2:
        {
            val += 2;
            rect(0,0,500,500, val);
            if(val == 250)
            {
                stage = 3;
                val = 500;
            }
            break;
        }

        // When the rectangle has fully rounded corners, and looks like a circle,
        // draw an ellipse, which gets squished
        case 3:
        {
            val -= 4;
            ellipse(0,0,500,val);

            if(val == 100)
            {
                stage = 4;
                val = 500;
            }
            break;
        }

        // When ellipse is 100 pixels tall, begin decreasing it's width
        case 4:
        {
            val -= 4;
            ellipse(0,0,val,100);

            if(val == 100)
            {
                stage = 5;
                val = 20;
            }
            break;
        }

        // When ellipse is 100 pixels wide, start increasing the stroke
        case 5:
        {
            val += 2;
            strokeWeight(val);
            circle(0,0,50);

            if(val == 50)
            {
                stage = 6;
            }
            break;
        }

        // When stroke fully covers the circle, start decreasing its radius
        // Decrease stroke weight at the same time to prevent artefacting
        // When circle is no longer visible, return back to stage 0
        case 6:
        {
            val -= 2;
            strokeWeight(val);
            circle(0,0,val);

            if(val == 0)
            {
                stage = 0;
                strokeWeight(20);
            }
            break;
        }
    }
}

int main()
{
    // Create the application object
    Application app(1000,1000,"Drawpp example: Shape animation");

    // Run the application
    return app.run(draw,setup);
}