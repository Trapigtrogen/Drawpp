// In this example we will use a filter to
// render the Mandelbrot set, as a demonstration
// of the fact that you can use the filters as
// normal fragment shader renderers.

#include <drawpp.hpp>

// The filter
DFilter mandelbrot;

// setup is called once before the application loop starts
void setup()
{
    // Load the filter shader from a string source
    mandelbrot = loadFilter(R"(
        void main()
        {
            // Set up c such that the mandelbrot will be drawn in proper size, 
            // and in the middle of the window
            vec2 c = (gl_FragCoord.xy / source_size - vec2(0.7,0.5)) * 3.0;
            vec2 z;

            // Maximum iteration count. Increasing this will create a higher definition
            // render, at the cost of performance. However, at 1000x1000 resolution,
            // increasing it from 100 has little point, as you won't be able to see the detail
            int max_it = 100;
            int it = 0;

            // The mandebrot iteration loop
            while(sqrt(z.x*z.x+z.y*z.y) < 4.0 && it < max_it)
            {
                z = vec2((z.x*z.x)-(z.y*z.y),2.0*z.x*z.y);
                z += c;
                ++it;
            }

            // If position is "outside" of the mandelbrot, do some math
            // to get a nice color for it. Otherwise, just set color to red
            if(it < max_it)
            {
                float a = mod(float(it),80.0)/80.0;

                gl_FragColor = vec4(a,0.0,0.0,1.0);
            }
            else
            {
                gl_FragColor = vec4(1.0,0.0,0.0,1.0);
            }
        }
    )");
}

// draw is called once every frame
void draw(float)
{
    // Draw the mandelbrot using the filter
    filter(mandelbrot);
}

int main()
{
    // Create the application object
    Application app(1000,1000, "Drawpp example: Mandelbrot shader");

    // Run the application
    return app.run(draw,setup);
}