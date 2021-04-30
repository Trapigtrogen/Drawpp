// In this example we will recreate the
// pixelate filter

#include <drawpp.hpp>

// We need glad for OpenGL API calls
#include <glad.h>


DFilter pixelate;

// Location of the scale uniform in our filter
int pixelate_scale_location;

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
            vec2 pos = gl_FragCoord.xy/source_size;
            pos -= mod(pos, vec2(scale) / source_size);
            gl_FragColor = texture2D(source, pos);
        }
    )");

    // Get the location of the scale uniform
    pixelate_scale_location = glGetUniformLocation(pixelate.getProgram(),"scale");
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

    // Apply the filter, with a lambda as the initializer function
    filter(pixelate,[=](unsigned int p){

        // Here we set the scale uniform value
        glUniform1f(pixelate_scale_location,pixel_scale);
    });
}

int main()
{
    // Create the application object
    Application app(1000,1000, "Drawpp example: Pixelate filter");

    // Run the application
    return app.run(draw,setup);
}