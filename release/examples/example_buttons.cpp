
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
int btn_width = 200;
int btn_height = 100;

// setup is called once before the application loop starts
void setup()
{
    // Load the images from files
    image1 = DImage::loadImage("assets/happy.png");
    image2 = DImage::loadImage("assets/sad.png");

    // Set image mode and rect mode to centre, so that they
    // will be drawn on the proper spot
    imageMode(CENTRE);
    rectMode(CENTRE);

    // We want some stroke around the buttons, so set stroke to 5
    strokeWeight(5);
}

// draw is called once every frame
void draw(float)
{
    // Draw the background
    background(color(200,255,100));

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
    fill(color(250,100,100));
    rect(300,700,btn_width,btn_height,30);

    // Draw the left side button, with blue color 
    fill(color(100,100,250));
    rect(700,700,btn_width,btn_height,30);
}

// mouseClicked is called every time a mouse button is clicked
void mouseClicked()
{
    // Here we test if the mouse position is inside 
    // either of the buttons, and set image_select accordingly

    int btn_width2 = btn_width/2;
    int btn_height2 = btn_height/2;

    // Right side button is the sad button
    if(mouseX > 300-btn_width2 &&
       mouseX < 300+btn_width2 &&
       mouseY > 700-btn_height2 &&
       mouseY < 700+btn_height2)
    {
        image_select = false;
    }

    // Left side button is the happy button
    else if(mouseX > 700-btn_width2 &&
            mouseX < 700+btn_width2 &&
            mouseY > 700-btn_height2 &&
            mouseY < 700+btn_height2)
    {
        image_select = true;
    }
}


int main()
{
    // Create the application object
    Application app(1000,1000,"Drawpp example: Buttons");

    // Set the mouse click callback
    app.setMouseClicked(&mouseClicked);

    // Run the application
    return app.run(&draw,&setup);
}