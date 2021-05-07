#include <drawpp.hpp>

// Starting values for the perlin noise generator

// Window will be sized 1000px * 1000px
// We need this information when we are fitting the final texture to fill the whole window
int window_height = 1000;
int window_width = 1000;

// The size of perlin noise will be 512px * 512px
int gen_height = 512;
int gen_width = 512;

// Octaves affect how blurry/smooth the noise is
int octaves = 8;

// Seed determines the output of the pseudo-random function
int seed = 1;

// Scale affects the contrast of high and low values
float nscale = 1.3f;

// Falloff affects the zoom level
float falloff = 0.5;

// Image where we'll draw the noise
DImage noiseTex;

// pixeldata for alt. method
//std::vector<Color> pixels;


void draw()
{
    // Render perlin noise data to texture

    // Go through every x,y coordinate of perlin noise data
    for (int y = 0; y < gen_height; ++y)
    {
        for (int x = 0; x < gen_width; ++x)
        {
            // Noise values are normalized meaning they go from 0 to 1 so noise value is multiplied by maximum color value
            unsigned char col = noise(x,y) * 255;

            // Here we're just going to put same value to each color channel of the pixel to get the grayscaled image
            noiseTex[y * gen_width + x] = Color(col,col,col);
        }
    }

    // Apply the new pixels
    noiseTex.apply();

    // Render said texture to fill whole window
    background(noiseTex);



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

    // Transparent box to see font better
    fill(0,0,0,100);
    rect(20,20,250,483);

    // Back to font colour
    fill(colors::white);
    // Print current values
    text("Seed: " + std::to_string(seed) + "\nOctaves: " + std::to_string(octaves) + "\nScale: " + std::to_string(nscale) + "\nFalloff: " + std::to_string(falloff), 30, 30);
    // Print controls 
    text("Controls:\nR - Random seed\nE - Previous seed\nT - Next seed\nW - Octaves up\nS - Octaves down\nD - Scale up\nA - Scale down\nX - Falloff up\nZ - Falloff down", 30, 170);
}

void setup()
{
    // Set window's title
    setTitle("Perlin noise");

    // Load font from assets folder to show our text with
    textFont(loadFont("assets/Tuffy.ttf", 30));

    // It's important to resize the noise resolution to be the same you want the image to be
    noiseMapSize(gen_width, gen_height);

    // Initialize noise seed to 1
    noiseSeed(1);

    // Initialize the image
    noiseTex = DImage(gen_width, gen_height);

    // Set font color to white
    fill(255, 255, 255);

    // Manually call draw once here in the beginning
    draw();
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

    // Manually call draw here, only when a key is pressed
    draw();
}

int main()
{
    // Create the application object
    Application app(window_width, window_height);

    // Set the key press callback
    app.setKeyPressed(keyPressed);

    // Run the application, without a draw function
    return app.run(nullptr,setup);
}