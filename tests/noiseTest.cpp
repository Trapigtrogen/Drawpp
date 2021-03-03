#include <stdio.h>
#include <drawpp.hpp>

int height = 500;
int width = 500;
float noiseScale = 0.02;

void setup()
{
    setTitle("Perlin noise");

    background(0, 0, 0);
    noiseDetails(32, 0.5f); // Debug lod does nothing
    for(int x = 0; x < width; x++)    
    {
        for(int y = 0; y < height; y++)       
        {
            Color col((noise(x, y) * 255),(noise(x, y) * 255),(noise(x, y) * 255));
            fill(col);
            rect(x*3, y*3, 3, 3);
        }
    }
}

void draw(float)
{
    /* 
    background(0, 0, 0);
    //Application::GetInstance()->noise.resize();
    for(int x = 0; x < width; x++)     {
        for(int y = 0; y < height; y++)         {
            Color col((noise(x, y) * 255), (noise(x, y) * 255), (noise(x, y) * 255));
            fill(col);
            rect(x * 3, y * 3, 3, 3);
        }
    }
    */
}

int main()
{
    Application app(width, height);
    return app.run(draw,setup);
}