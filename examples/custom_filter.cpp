// In this example we will recreate the
// pixelate filter

#include <drawpp.hpp>

// The filter variable
DFilter pixelate;

// Scale of the pixels we want. You can change this in runtime
float pixel_scale = 10;


// setup is called once before the application loop starts
void setup()
{
    // Load the filter from a string source
    pixelate = loadFilter(R"(
        uniform float scale;
        void main()
        {
            // By default, gl_FragCoord has the origin in bottom-left corner
            // Drawpp library has origin in the top-left corner, so we invert the y coordinate
            vec2 fragPos = vec2(gl_FragCoord.x,1.0-gl_FragCoord.y);

            // Get the current pixel coordinate, by dividing the 
            // fragment position by the source image size
            vec2 pos = fragPos/source_size;

            // Clamp the coordinate with scale
            pos -= mod(pos, vec2(scale) / source_size);

            // Set pixel color to be the same as at pos
            gl_FragColor = texture2D(source, pos);
        }
    )");
}

// draw is called once every frame
void draw(float)
{
    // Draw the background
    background(200,255,100);

    // Draw something for the filter to pixelate
    strokeWeight(10);
    rect(100,100,200,300);
    strokeWeight(20);
    circle(500,500,200);


    // Set the pixel scale
    pixelate.setUniform("scale", 10.0f);

    // Apply the filter
    filter(pixelate);
}

int main()
{
    // Create the application object
    Application app(1000,1000, "Drawpp example: Pixelate filter");

    // Run the application
    return app.run(draw,setup);
}