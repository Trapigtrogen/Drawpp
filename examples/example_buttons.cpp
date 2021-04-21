
// In this example will load two images, and create
// two buttons to change which image is being displayed.

#include <drawpp.hpp>

// Happy face image
DImage image1;

// Sad face image
DImage image2;

// Boolean used to decide which image to draw.
// true for happy face, false for sad face
bool image_select = true;

// Button size
int btn_width  = 200;
int btn_height = 100;

// Half of button size, used for hit detection
int btn_width2  = btn_width/2;
int btn_height2 = btn_height/2;

// Button coordinates
int button1_x = 300;
int button1_y = 700;

int button2_x = 700;
int button2_y = 700;


// Helper function for the left side button hit detection
bool mouseInBtn1()
{
    if(mouseX > button1_x-btn_width2 &&
       mouseX < button1_x+btn_width2 &&
       mouseY > button1_y-btn_height2 &&
       mouseY < button1_y+btn_height2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Helper function for the right side button hit detection
bool mouseInBtn2()
{
    if(mouseX > button2_x-btn_width2 &&
       mouseX < button2_x+btn_width2 &&
       mouseY > button2_y-btn_height2 &&
       mouseY < button2_y+btn_height2)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// setup is called once before the application loop starts
void setup()
{
    // Load the images from files
    image1 = DImage::loadImage("assets/happy.png");
    image2 = DImage::loadImage("assets/sad.png");

    // Set image mode and rect mode to centre, so that they
    // will be drawn on the proper spot
    imageMode(CENTER);
    rectMode(CENTER);

    // We want some stroke around the buttons, so set stroke to 5
    strokeWeight(5);
}

// draw is called once every frame
void draw(float)
{
    // Draw the background
    background(200,255,100);

    // Depending on image_select, draw a happy face or a sad face
    if(image_select)
    {
        image(image1,500,300);
    }
    else
    {
        image(image2,500,300);
    }

    // Draw the right side button, with red color
    fill(250,100,100);
    rect(button1_x,button1_y,btn_width,btn_height,30);

    // Draw the left side button, with blue color 
    fill(100,100,250);
    rect(button2_x,button2_y,btn_width,btn_height,30);
}

// mouseMoved is called every time the mouse is moved
void mouseMoved()
{
    // Change cursor to a hand, if mouse is over a button
    if(mouseInBtn1() || mouseInBtn2())
    {
        cursor(HAND);
    }
    else
    {
        cursor(ARROW);
    }
}

// mouseClicked is called every time a mouse button is clicked
void mouseClicked()
{
    // If mouse was over one of the buttons when clicked,
    // set image_select accordingly

    // Right side button is the sad button
    if(mouseInBtn1())
    {
        image_select = false;
    }

    // Left side button is the happy button
    else if(mouseInBtn2())
    {
        image_select = true;
    }
}

int main()
{
    // Create the application object
    Application app(1000,1000,"Drawpp example: Buttons");

    // Set the mouse click callback and mouse move callback
    app.setMouseClicked(mouseClicked);
    app.setMouseMoved(mouseMoved);

    // Run the application
    return app.run(draw,setup);
}