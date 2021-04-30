#include <drawpp.hpp>

// Starting values for the perlin noise generator

// Window will be sized 1000px * 1000px
// We need this information when we are fitting the final texture to fill the whole window
int window_height = 1000;
int window_width = 1000;

// The size of perlin noise will be 512px * 512px
int gen_height = 512;
int gen_width = 512;

// Octaves affect how blurry/smooth the noise is. Can be 1-10
int octaves = 8;

// Seed determines the output of the pseudo-random function
int seed = 1;

// Scale affects the contrast of high and low values
float nscale = 1.3f;

float falloff = 0.5;

// Create pixeldata and empty texture remember to multiply by amount of channels per pixel (r,g,b,a) = 4
unsigned char* pixeldata = new unsigned char[gen_width * gen_height * 4];
DImage noiseTex;

// pixeldata for alt. method
std::vector<Color> pixels;

void setup()
{
    // Set window's title
    setTitle("Perlin noise");

    // Load font from assets folder to show our text with
    textFont(loadFont("assets/Tuffy.ttf", 30));

    // It's important to resize the noise resolution to be the same you want the image to be
    noiseMapSize(gen_width, gen_height);
}

void draw(float)
{
    // Render perlin noise data to texture

    // Go through every x,y coordinate of perlin noise data
    for (int y = 0; y < gen_height; y++)
    {
        for (int x = 0; x < gen_width; x++)
        {
            // Here we're just going to put same value to each color channel of the pixel to get the grayscaled image
            // Multiplier 4 is added to both coordinates because as said previously the image has 4 channels per pixel
            // Noise values are normalized meaning they go from 0 to 1 so noise value is multiplied by maximum color value

            pixeldata[y * 4 * gen_width + x * 4] = noise(x,y) * 255;			// RED
            pixeldata[y * 4 * gen_width + x * 4  + 1] = noise(x, y) * 255;		// GREEN
            pixeldata[y * 4 * gen_width + x * 4  + 2] = noise(x, y) * 255;		// BLUE
            pixeldata[y * 4 * gen_width + x * 4  + 3] = 255;				    // ALPHA
        }
    }
    // Create texture with pixel data
    noiseTex = createImage(pixeldata, gen_width, gen_height);
    // Render said texture to fill whole window
    image(noiseTex, 0, 0, window_width, window_height);



    // Alternative but much slower way to render custom data to image (better suitable for setup)
    /*
    for (int y = 0; y < gen_height; y++)
    {
        for (int x = 0; x < gen_width; x++)
        {
            Color col(noise(x, y) * 255, noise(x, y) * 255, noise(x, y) * 255, 255);
            pixels.push_back(col);
        }
    }
    noiseTex = createImage(pixels, gen_width, gen_height);
    image(noiseTex, 0, 0, window_width, window_height);
    // Remember to remove pixels if you plan to reuse the same vector
    pixels.clear();
    */



    // Print some helpful text on the screen

    // Set font color to white
    fill(255, 255, 255);

    // Print current values
    text("Seed: " + std::to_string(seed) + "\nOctaves: " + std::to_string(octaves) + "\nScale: " + std::to_string(nscale) + "\nFalloff: " + std::to_string(falloff), 30, 30);
    // Print controls 
    text("Controls:\nR - Random seed\nE - Previous seed\nT - Next seed\nW - Octaves up\nS - Octaves down\nD - Scale up\nA - Scale down\nX - Falloff up\nZ - Falloff down", 30, 170);
}

// Key press events
void keyPressed()
{
    // Changing the basic settings
    
    // Octaves up by 1
    if(key == VK_W) 
    {
        // add 1 to our placeholder octaves variable
        octaves++; 
        // Set the new value to the noise generator
        noiseDetails(octaves);
    }

    // Octaves down by 1
    else if(key == VK_S)
    {
        octaves--;
        noiseDetails(octaves);
    }

    // Scale up by 0.1
    else if(key == VK_D)   
    {
        nscale += 0.1f;
        noiseScale(nscale);
    }

    // Scale down by 0.1
    else if(key == VK_A)     
    {
        nscale -= 0.1f;
        noiseScale(nscale);
    }

    // falloff up by 0.1
    else if (key == VK_X)
    {
        falloff += 0.1f;
        noiseDetails(octaves, falloff);
    }

    // Scale down by 0.1
    else if (key == VK_Z)
    {
        falloff -= 0.1f;
        noiseDetails(octaves, falloff);
    }

    // Seed settings

    // Next seed
    else if(key == VK_T)   
    {
        seed++;
        noiseSeed(seed);
    }

    // Previous seed
    else if(key == VK_E)   
    {
        seed--;
        noiseSeed(seed);
    }

    // Random seed
    else if(key == VK_R) 
    {
        // get random number between 0-100000
        seed = randomInt(100000);
        // Regenerate the noise by setting the new seed
        noiseSeed(seed);
    }
}

int main()
{
    // Create the application object
    Application app(window_width, window_height);

    // Set the key press callback
    app.setKeyPressed(keyPressed);

    // Run the application
    return app.run(draw,setup);
}