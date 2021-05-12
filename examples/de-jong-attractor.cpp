
// In this example we draw a Peter de Jong Attractor.
// 
// To learn more about attractors, see Wikipedia:
// www.wikipedia.org/wiki/Attractor
// 
// To learn more about the Peter de Jong Attractor, see:
// paulbourke.net/fractals/peterdejong/
// 
// 
// We will generate the attractor using a histogram,
// decreasing the value at x,y by a small amount every iteration.
// 
// Increasing the iteration count will reduce the values
// more overall, as does decreasing the multiplier.
// 
// Increasing the histogram size will result in a 
// shallower distribution of hits, so in that case you
// may want to increase the iteration count, or the multiplier.
//
// Note that increasing the histogram size, or the iteration count
// will greatly impact the performance of the program.

#include <drawpp.hpp>
#include <vector>
#include <algorithm>

// Size of the histogram where the attractor is generated
constexpr int GEN_WIDTH = 200;
constexpr int GEN_HEIGHT = 200;

// Application window size
constexpr int W_WIDTH = 1000;
constexpr int W_HEIGHT = 1000;

// Pixel sizes
constexpr float PX_WIDTH = (W_WIDTH / (float)GEN_WIDTH);
constexpr float PX_HEIGHT = (W_HEIGHT / (float)GEN_HEIGHT);

// Number of iterations to run the generator for
constexpr unsigned iterations = 2000000u;

// Multiplier for each hit
constexpr float multiplier = 0.995f;

// Histogram storing the values
std::vector<float> histogram = std::vector<float>(GEN_WIDTH*GEN_HEIGHT);

// Generator parameters
// Try changing these
float a = 2.0f, b = 5.0f, c = 3.5f, d = 2.0f;

// setup is called once before the application loop starts
void setup()
{
    // We don't want any stroke, so turn it off
    noStroke();
}

// draw is called once every frame
void draw(float)
{
    // Increment 'a' every frame to animate the attractor
    a += 0.01f;

    // Initialize starting position x and y
    float x = 0.0f, y = 0.0f;
    
    // Initialize histogram
    std::fill(histogram.begin(),histogram.end(),1.0f);

    for(unsigned i = 0; i < iterations; ++i)
    {   
        // Generate next x and y positions
        // These are the attractor equations
        float nx = sin(a * y) - cos(b * x);
        float ny = sin(c * x) - cos(d * y);
        
        // Next we plot the position to the histogram
        // Try the variants to get different results
        
        // Polar plot
        int xp = GEN_WIDTH/2.0 + GEN_WIDTH/4.0 * nx*cos(ny);
        int yp = GEN_HEIGHT/2.0 + GEN_HEIGHT/4.0 * nx*sin(ny);

        // Normal plot
        //int xp = GEN_WIDTH * (1 + x * 0.43f) * 0.5f;
        //int yp = GEN_HEIGHT * (1 + y * 0.43f) * 0.5f;

        // Variant 1
        //int xp = GEN_WIDTH/2 + GEN_WIDTH/2 * sin(nx) * cos(3.141 * nx);
        //int yp = GEN_HEIGHT/2 + GEN_HEIGHT/2 * cos(ny) * sin(3.141 * ny);

        // Variant 2
        //int xp = GEN_WIDTH/2 + GEN_WIDTH/2 * sin(ny) * cos(3.141 * nx) * 0.95;
        //int yp = GEN_HEIGHT/2 + GEN_HEIGHT/2 * cos(nx) * sin(3.141 * ny) * 0.95;

        // Apply the multiplier
        histogram[yp * GEN_WIDTH + xp] *= multiplier;

        // Update x and y
        x = nx;
        y = ny;
    }
    
    // Next we render the histogram

    // Go through each x,y position in the histogram
    for(unsigned y = 0; y < GEN_HEIGHT; ++y)
    {
        // Get the screenspace y position 
        unsigned _y = PX_HEIGHT * y;

        for(unsigned x = 0; x < GEN_WIDTH; ++x)
        {
            // Get the screenspace x position
            unsigned _x = PX_WIDTH * x;

            // Get a nice color from the histogram value
            Color c = Color(0xFFFF0000 | (int)((double)0xFFE5 * histogram[y * GEN_WIDTH + x]));

            // Set fill color 
            fill(c);
            
            // Draw a pixel sized ellipse at the x,y position
            ellipse(_x, _y, PX_WIDTH, PX_HEIGHT);
        }
    }
}

int main()
{
    // Create the application object
    Application app(W_WIDTH,W_HEIGHT,"Drawpp example: Peter de Jong Attractor");

    // Run the application
    return app.run(draw,setup);
}