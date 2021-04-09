#include <drawpp.hpp>

int height = 1000;
int width = 1000;
int octaves = 8;
int seed = 1;
float nscale = 1.3f;

bool updateNoise = true;

unsigned char pixels[100 * 100 * 4];
DImage noiseTex;

void setup()
{
    setTitle("Perlin noise");
    noStroke();

    textFont(loadFont("assets/Tuffy.ttf", 30));
}

void draw(float)
{
    // Limit redrawing the whole noise until something has changed
    if (updateNoise) 
    {
        background(0, 0, 0);
        /* 
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                fill((noise(x, y) * 255));
                circle(x * 5, y * 5, 5);       
            }
        }
        */

        for (int x = 0; x < 100 * 4; x += 4)
        {
            for (int y = 0; y < 100 * 4; y += 4)
            {
                pixels[y * 100 + x] = noise(x,y) * 255;			    // RED
                pixels[y * 100 + x + 1] = noise(x, y) * 255;		// GREEN
                pixels[y * 100 + x + 2] = noise(x, y) * 255;		// BLUE
                pixels[y * 100 + x + 3] = 255;				        // ALPHA
            }
        }
        noiseTex = createImage(pixels, 100, 100);
        image(noiseTex, 0, 0, width, height);

        fill(255, 255, 255);
        text("Seed: " + std::to_string(seed) + "\nOctaves: " + std::to_string(octaves) + "\nScale: " + std::to_string(nscale), 30, 30);
        text("Controls:\nR - Random seed\nE - Previous seed\nT - Next seed\nW - Octaves up\nS - Octaves down\nD - Scale up\nA - Scale down", 30, 150);

        updateNoise = false;
    }

}

void keyPressed()
{
    if(key == VK_W)
    {
        octaves++;
        noiseDetails(octaves);
        noiseSeed(seed);
    }

    else if(key == VK_S)
    {
        octaves--;
        noiseDetails(octaves);
        noiseSeed(seed);
    }

    else if(key == VK_D)   
    {
        nscale += 0.1f;
        noiseScale(nscale);
        noiseSeed(seed);
    }

    else if(key == VK_A)     
    {
        nscale -= 0.1f;
        noiseScale(nscale);
        noiseSeed(seed);
    }


    else if(key == VK_T)   
    {
        seed++;
        noiseSeed(seed);
    }

    else if(key == VK_E)   
    {
        seed--;
        noiseSeed(seed);
    }

    else if(key == VK_R) 
    {
        seed = randomInt(100000);
        noiseSeed(seed);
    }

    updateNoise = true;
}

int main()
{
    Application app(width, height);
    app.setKeyPressed(keyPressed);
    return app.run(draw,setup);
}