#include <stdio.h>
#include <drawpp.hpp>

int height = 1000;
int width = 1000;
int octaves = 8;
int seed = 1;
float nscale = 1.3f;
DImage img;

void setup()
{
    setTitle("Perlin noise");
    noStroke();
    //size(500, 500);
}

void draw(float)
{
    background(0, 0, 0);
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)    
        {
            Color col((noise(x, y) * 255), (noise(x, y) * 255), (noise(x, y) * 255));
            fill(col);
            //rect(x*5, y*5, 5, 5); // pixel like
            circle(x*5, y*5, 5); // Smoother
        }
    }
    printf("Octaves: %i, Seed: %i, Scale: %f\n", octaves, seed, nscale);
}

void keyPressed()
{
    if(key == VK_I)
    {
        octaves++;
        noiseDetails(octaves);
        noiseSeed(seed);
    }

    else if(key == VK_K)
    {
        octaves--;
        noiseDetails(octaves);
        noiseSeed(seed);
    }

    else if(key == VK_W)   
    {
        nscale += 0.1f;
        noiseScale(nscale);
        noiseSeed(seed);
    }

    else if(key == VK_S)     
    {
        nscale -= 0.1f;
        noiseScale(nscale);
        noiseSeed(seed);
    }


    else if(key == VK_L)   
    {
        seed++;
        noiseSeed(seed);
    }

    else if(key == VK_J)   
    {
        seed--;
        noiseSeed(seed);
    }

    else if(key == VK_R) 
    {
        seed = randomInt(100000);
        noiseSeed(seed);
    }
}

int main()
{
    Application app(width, height);
    app.setKeyPressed(keyPressed);
    return app.run(draw,setup);
}