#include <drawpp.hpp>
// perlin noise settings
// The size of perlin noise will be 512px * 512px
int gen_height = 512;
int gen_width = 512;
// Image where we'll draw the noise
DImage grassTex;
DImage waterTex;

// Camera
float zoomlevel = 0.7f;
int cameraX = -200;
int cameraY = -100;
float cameraSpeed = 10;
bool shouldMoveCamera = false;

// House settings
struct House
{
    Color wallCol;
    int coordX;
    int coordY;
    int stores;
};
int gap = 10;
std::vector<House*> houses;


// Cars
DImage carYellow;
DImage carRed;
DImage carBlue;
DImage carGreen;
DImage carSports;

// Select random car
DImage* randomCar()
{
    int ri = randomInt(4);
    switch (ri)
    {
    case 0:
         return &carYellow;
        break;

    case 1:
        return &carBlue;
        break;

    case 2:
        return &carRed;
        break;

    case 3:
        return &carGreen;
        break;

    default:
        return &carSports;
        break;
    }
}

// Car movement settings
int carSpeed = 250;
float carTimer = -100;
float carTimer2 = -1000;

// These image pointers represent the cars on the road
// They are randomily set to point one of the car images
DImage* carImg = &carYellow;
DImage* carImg2 = &carRed;



void setup()
{
    // Limit fps
    frameRate(90); 
    setTitle("Game Map");

    // Grass settings
    noiseSeed( randomInt(1000000) );
    noiseScale(1.1);
    noiseDetails(10);
    grassTex = DImage(gen_width, gen_height);
    waterTex = DImage(gen_width, gen_height);

    // Load car svg images as textures
    carYellow = loadSVGImage("assets/map/carYellow.svg");
    carRed = loadSVGImage("assets/map/carRed.svg");
    carBlue = loadSVGImage("assets/map/carBlue.svg");
    carGreen = loadSVGImage("assets/map/carGreen.svg");
    carSports = loadSVGImage("assets/map/carSports.svg");

    // Create houses with random coloured walls
    // They need to be created in setup and stored so they kep their colour instead of getting new colour every frame
    // We can store other settigns now as well
    
    // Vertical from corner (this is first so it gets drawn before stuff in front)
    for (int i = 0; i < 10; i++)
    {
        House* house = new House;
        house->wallCol = Color(randomInt(255), randomInt(255), randomInt(255));
        house->coordX = 890;
        house->coordY = -i * (100 + gap) + 90;
        house->stores = 1;
        houses.push_back(house);
    }
    // Horizontal
    for (int i = 0; i < 10; i++)
    {
        House* house = new House;
        house->wallCol = Color(randomInt(255), randomInt(255), randomInt(255));
        house->stores = 1;
        house->coordX = i * (100 + gap) - 100;
        house->coordY = 200;

        // One random tall building for the lols
        if (i == 3) 
        {
            house->stores = 2;
            house->coordY = 100;
        }

        houses.push_back(house);
    }
    // Horizontal after the road
    for (int i = 0; i < 10; i++)
    {
        House* house = new House;
        house->wallCol = Color(randomInt(255), randomInt(255), randomInt(255));
        house->stores = 1;
        house->coordX = i * (100 + gap) - 100;
        house->coordY = 200;
        if (i == 3)
        {
            house->stores = 2;
            house->coordY = 100;
        }

        houses.push_back(house);
    }

    // Generate grassy texture using perlin noise
    // Go through every x,y coordinate of perlin noise data
    for (int y = 0; y < gen_height; ++y)
    {
        for (int x = 0; x < gen_width; ++x)
        {
            // Noise values are normalized meaning they go from 0 to 1 so noise value is multiplied by maximum color value
            unsigned char col = noise(x, y) * 255;

            // Put value to green channel for grass and blue channel for water
            grassTex[y * gen_width + x] = Color(0, col, 0, 150);
            waterTex[y * gen_width + x] = Color(0, col/2, col, 100);
        }
    }
    // Apply the new pixels
    grassTex.apply();
    waterTex.apply();
}

void draw(float deltaTime)
{
    background(200, 255, 100);

    // Zoom and movement

    // Limit zoom level
    if (zoomlevel > 1) zoomlevel = 1;
    else if (zoomlevel < 0.4) zoomlevel = 0.4;
    // Apply zoom level
    scale(zoomlevel);

    // Limit camera movement area
    if (cameraX > 1000) cameraX = 1000;
    if (cameraX < -2000) cameraX = -2000;
    if (cameraY > 700) cameraY = 700;
    if (cameraY < -1000) cameraY = -1000;

    // Mouse camera. Click & drag
    if (shouldMoveCamera)
    {
        if ((pmouseX - mouseX) > 1 || (pmouseX - mouseX) < -1) // Reduce sliding
            cameraX += (pmouseX - mouseX);
        if ((pmouseY - mouseY) > 1 || (pmouseY - mouseY) < -1) // Reduce sliding
            cameraY += (pmouseY - mouseY);
    }

    // Move the world on the opposite direction to camera movement
    translate(-cameraX, -cameraY);

    // Render gras texture
    image(grassTex, -4000, -4000, 8000, 8000);

    // Draw Roads
    noStroke();
    fill(colors::grey);
    // Intersecting roads. Width = 100
    rect(1000, -2000, 100, 8000); // Horizontal
    rect(-2000, 300, 8000, 100); // Vertical

    // Draw Swimming pool
    fill(colors::cyan);
    noStroke();
    rect(400, 70, 200, 100);
    // Shadow
    fill(0, 200, 200);
    rect(400, 70, 200, 20);
    //quad();
    quad(400, 70, 420, 70, 400, 170, 410, 170);
    // Texture with some random movment to resemble water moving
    image(waterTex, 400, 70, 200, 100);
    // Stone areas to hide the texture going over
    fill(colors::grey);
    rect(600, 70, 70, 100);
    rect(600, 70, 70, 100);
    
    // Draw houses
    for (House* house : houses)
    {
        strokeWeight(7);
        fill(house->wallCol);
        rect(house->coordX, house->coordY, 100, house->stores * 100);

        // Shadow
        noStroke();
        fill(0, 0, 0, 50);
        rect(house->coordX + 7, house->coordY, 20, house->stores * 100 - 7);

        // Door
        fill(colors::brown);
        rect(house->coordX + 40, house->coordY + 60 + (house->stores - 1) * 100 - 5, 20, 40);

        // Windows
        fill(colors::cyan);
        rect(house->coordX + 20, house->coordY + 25 + (house->stores - 1) * 100, 15, 15);
        // Extra windows for higher houses
        if (house->stores > 1)  
        {
            rect(house->coordX + 30, house->coordY + 30, 15, 15);
            rect(house->coordX + 60, house->coordY + 30, 15, 15);
            rect(house->coordX + 60, house->coordY + 70, 15, 15);
        }
    }
    // Draw roofs 
    // This is separate to get all the roofs drawn on top of the houses
    for (House* house : houses)
    {
        strokeWeight(7);
        fill(200,0,0);
        triangle(house->coordX -20, house->coordY + 20,
                 house->coordX + 50, house->coordY - 40,
                 house->coordX + 120, house->coordY + 20);
    }

    // Custom house
    fill(colors::blue);
    rect(1100, 400, 100, 200);
    rect(1100, 500, 200, 100);


    // Cars
    image(*carImg, carTimer, 300, carImg->width() / 3, carImg->height() / 3);
    // rotate other car 90 degrees
    rotate(1.570796);
    image(*carImg2, carTimer, -1090, carImg->width() / 3, carImg->height() / 3);

    // Car movement
    carTimer += deltaTime * carSpeed;
    if (carTimer > 1900)
    {
        carTimer = -1900;
        carImg = randomCar();
    }

    carTimer2 += deltaTime * carSpeed;
    if (carTimer > 1900)
    {
        carTimer = -1900;
        carImg2 = randomCar();
    }
}


// Zoom with mouse scroll
void mouseWheel(float t)
{
    zoomlevel += t * 0.1f;
}

// Enable cameramovement on mouse when clicked
// (Click & Drag to move)
void mousePressed()
{
    shouldMoveCamera = true;
}

// Disable camera movement on mouse when not clicked
void mouseReleased() 
{
    shouldMoveCamera = false;
}

// Key input
void keyPressed()
{
    switch (key)
    {
    case VK_W: // move camera up
        cameraY -= cameraSpeed;
    break;

    case VK_A: // move camera left
        cameraX -= cameraSpeed;
    break;

    case VK_S: // move camera right
        cameraY += cameraSpeed;
    break;

    case VK_D: // move camera down
        cameraX += cameraSpeed;
    break;

    case VK_ESC:
        exit(1);
    break;

    default:
        break;
    }
}

int main()
{
    Application app(1000, 800);

    app.setMousePressed(mousePressed);
    app.setMouseReleased(mouseReleased);

    app.setMouseWheel(mouseWheel);

    app.setKeyPressed(keyPressed);

    return app.run(draw, setup);
}