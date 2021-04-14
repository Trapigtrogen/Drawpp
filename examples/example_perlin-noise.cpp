#include <drawpp.hpp>

// Starting values for the perlin noise generator
// Window will be sized 1000px * 1000px
// We need this information when we are fitting the final texture to fill the whole window
int window_height = 1000;
int window_width = 1000;

// The size of perlin noise will be 100px * 100px
int gen_height = 100;
int gen_width = 100;

// Octaves affect how blurry/smooth the noise is. Can be 1-10
int octaves = 8;

// Seed determines the output of the pseudo-random function
int seed = 1;

// Scale affects the contrast of high and low values
float nscale = 1.3f;

// Create pixeldata and empty texture
unsigned char* pixels = new unsigned char[100 * 100 * 4];
DImage noiseTex;

void setup()
{
    // Set window's title
    setTitle("Perlin noise");

    // Load font from assets folder to show our text with
    textFont(loadFont("assets/Tuffy.ttf", 30));
}

void draw(float)
{
    // Set background to black. This also clears previous frame's renders
    background(0, 0, 0);

        
    // Render perlin noise data to texture

    // Go through every x,y coordinate of perlin noise data
    // multiplier 4 is the amount of channels we need for the image (r,g,b,a)
    for (int y = 0; y < window_height * 4; y += 4)
    {
        for (int x = 0; x < window_width * 4; x += 4)
        {
            // Here we're just going to put same value to each color channel of the pixel to get the grayscaled image

            pixels[y * window_width + x] = noise(x,y) * 255;			// RED
            pixels[y * window_width + x + 1] = noise(x, y) * 255;		// GREEN
            pixels[y * window_width + x + 2] = noise(x, y) * 255;		// BLUE
            pixels[y * window_width + x + 3] = 255;				        // ALPHA
        }
    }
    noiseTex = createImage(pixels, window_width, window_height);
    image(noiseTex, 0, 0, window_width, window_height);


    // Print some helpful text on the screen

    // Set font color to white
    fill(255, 255, 255);

    // Print current values
    text("Seed: " + std::to_string(seed) + "\nOctaves: " + std::to_string(octaves) + "\nScale: " + std::to_string(nscale), 30, 30);
    // Print controls 
    text("Controls:\nR - Random seed\nE - Previous seed\nT - Next seed\nW - Octaves up\nS - Octaves down\nD - Scale up\nA - Scale down", 30, 150);
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
        // Regenerate the noise by setting the same seed
        noiseSeed(seed);
    }

    // Octaves down by 1
    else if(key == VK_S)
    {
        octaves--;
        noiseDetails(octaves);
        noiseSeed(seed);
    }

    // Scale up by 0.1
    else if(key == VK_D)   
    {
        nscale += 0.1f;
        noiseScale(nscale);
        noiseSeed(seed);
    }

    // Scale down by 0.1
    else if(key == VK_A)     
    {
        nscale -= 0.1f;
        noiseScale(nscale);
        noiseSeed(seed);
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