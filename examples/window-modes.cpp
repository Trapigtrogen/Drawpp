
#include <drawpp.hpp>

// Window size
int window_w = 640;
int window_h = 360;

// Rect settings for quick change
int rect_size = 100;

// TIMER:

// Current timer total value
// Start with value 1 to draw the first frame immediately
float timer = 1; 
// To quickly change timer resetting time from everywhere
float timerMax = 1; 

// Variables to get the randoms in every second
int rect1_x = 0;
int rect1_y = 0;
int rect2_x = 0;
int rect2_y = 0;
int rect3_x = 0;
int rect3_y = 0;

// Current fullscreen mode
bool isFullscreen = false;
void toggleFullscreen()
{
    // Check current mode
    if(isFullscreen) {
        size(window_w, window_h);
        isFullscreen = false;
    }
    else {
        // Change to fullscreen
        fullScreen(0);
        isFullscreen = true;
    }

    // Reset timer to draw new frame immediately
    timer = 1;
}


void setup() 
{
    // Limit fps to 30
    // Note that this also limits how input and window's elements react (i.e. exit button)
    // So this is not suitable for limitting animation. Create a timer instead
    frameRate(30);

    // Or enable Vsync (monitor's refresh rate)
    // vSync(true);
}

void draw(float deltaTime) 
{
    // Change the rectangle size depending on fullscreen mode
    int newRectSize;
    isFullscreen ? newRectSize = rect_size : newRectSize = rect_size / 2;

    // Delta time tells how many seconds the last frame took to draw (value 1.0 = 1sec. Frame generally takes 0.0X seconds)
    // We're using the it to create animation timer so rectangles change palce only every 1sec
    timer += deltaTime; // Add deltaTime to total
    if (timer >= 1.0)  // Do every second
    {
        // Remember to reset the timer
        timer = 0.0;

        if (isFullscreen)
        {
            // Change rectangle positions
            rect1_x = randomInt(0, getMonitorWidth(0) - newRectSize);
            rect1_y = randomInt(0, getMonitorHeight(0) - newRectSize);
            rect2_x = randomInt(0, getMonitorWidth(0) - newRectSize);
            rect2_y = randomInt(0, getMonitorHeight(0) - newRectSize);
            rect3_x = randomInt(0, getMonitorWidth(0) - newRectSize);
            rect3_y = randomInt(0, getMonitorHeight(0) - newRectSize);
        }
        else
        {
            // Change rectangle positions
            rect1_x = randomInt(0, window_w - newRectSize);
            rect1_y = randomInt(0, window_h - newRectSize);
            rect2_x = randomInt(0, window_w - newRectSize);
            rect2_y = randomInt(0, window_h - newRectSize);
            rect3_x = randomInt(0, window_w - newRectSize);
            rect3_y = randomInt(0, window_h - newRectSize);
        }
    }


    // DRAW

    // Draw the stuff
    // clear screen with black
    background(colors::black);

    // Draw the rectangles depending on screen mode
    fill(colors::white);
    rect(rect1_x, rect1_y, newRectSize, newRectSize);
    rect(rect2_x, rect2_y, newRectSize, newRectSize);
    rect(rect3_x, rect3_y, newRectSize, newRectSize);
}

void onKeyPress() 
{
    switch (key)
    {
        case VK_F: // Press the key 'f' to toggle between fulscreen and windowed mode
            toggleFullscreen();
        break;

        case VK_1: // Default window size
            window_w = 640;
            window_h = 360;
            size(window_w, window_h);
            isFullscreen = false;

            // Reset timer to draw new frame immediately
            timer = 1;
        break;

        case VK_2: // Double the window size
            window_w = 1280;
            window_h = 720;
            size(window_w, window_h);
            isFullscreen = false;

            // Reset timer to draw new frame immediately
            timer = 1;
        break;

        case VK_ESC: // Exit the application with 'esc' key
            exit();
        break;
    }
}

int main()
{
    // Create the application object
    Application app(window_w, window_h, "Drawpp example: Window modes and settings");

    app.setKeyPressed(onKeyPress);

    // Run the application
    return app.run(draw, setup);
}