#include <stdio.h>
#include <drawpp.hpp>

int height = 500;
int width = 500;
float xoff = 0.0;

void setup()
{
    setTitle("Perlin noise");
}

void draw(float)
{
    background(0,0,0);
    xoff += .01;
    float n = noise(xoff) * width;
    line(n, 0, n, height);
}

int main()
{
    Application app(width, height);
    return app.run(draw,setup);
}