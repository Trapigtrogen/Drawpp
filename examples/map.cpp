#include <drawpp.hpp>
#include <algorithm> // std::min

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

// Animation settings

// One second timer for all animations to sync
// Gives that pixel game feeling
float animationTimer = 0;

// Water animation movement amount
int waterMovement = 0;


// House settings
struct House
{
    Color wallCol;
    int coordX;
    int coordY;
    int stores;
};
int gap = 10;
int defaultBorder = 0; // 0, 3 and 7 give nice different visual
std::vector<House*> houses;
std::vector<House*> houses2;


// Cars
DImage carYellow;
DImage carRed;
DImage carBlue;
DImage carGreen;

// Select random car
DImage* randomCar()
{
    int ri = randomInt(3);
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

    default:
        return &carGreen;
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
DImage* carImg3 = &carBlue;



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

    // Create houses with random coloured walls
    // They need to be created in setup and stored so they kep their colour instead of getting new colour every frame
    // We can store other settigns now as well so all the houses can be drawn with one loop
    
    // Vertical from corner (this is first so it gets drawn before stuff in front)
    for (int i = 0; i < 10; i++)
    {
        House* house = new House;
        house->wallCol = Color(randomInt(255), randomInt(255), randomInt(255));
        house->coordX = 890;
        house->coordY = i * (100 - gap) - 700;
        house->stores = 1;
        houses.push_back(house);
    }
    // Horizontal before the road
    for (int i = 0; i < 29; i++)
    {
        House* house = new House;
        house->wallCol = Color(randomInt(255), randomInt(255), randomInt(255));
        house->coordX = i * (100 + gap) - 2200;
        house->coordY = 190;
        house->stores = randomInt(1, 3);
        // Randomize building size
        // Don't let last few houses be tall so they don't render over the swimming pool
        if (i > 20) house->stores = 1;
        if (house->stores > 1)
        {
            house->coordY -= (house->stores - 1) * 100;
        }

        houses.push_back(house);
    }
    // Horizontal after the road
    for (int i = 0; i < 22; i++)
    {
        House* house = new House;
        house->wallCol = Color(randomInt(255), randomInt(255), randomInt(255));
        house->coordX = i * (100 + gap) + 1130;
        house->coordY = 190;
        // Randomize building size
        house->stores = randomInt(1, 3);
        if (house->stores > 1)
        {
            house->coordY -= (house->stores -1) * 100;
        }

        houses.push_back(house);
    }
    // Big lower area
    // On it's own vector so it can be drawn on top of the cars
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 4; j++) // Rows
        {
            House* house = new House;
            house->wallCol = Color(randomInt(255), randomInt(255), randomInt(255));
            house->coordX = i * (100 + gap) + 1130;
            house->coordY = 490 + j*300;
            // Randomize building size
            house->stores = randomInt(2, std::min(j+3,5));
            if (house->stores > 1)
            {
                house->coordY -= (house->stores - 1) * 100;
            }

            houses2.push_back(house);
        }
    }

    // Generate grassy texture using perlin noise
    // Go through every x,y coordinate of perlin noise data
    for (int y = 0; y < gen_height; ++y)
    {
        for (int x = 0; x < gen_width; ++x)
        {
            // Noise values are normalized meaning they go from 0 to 1 so noise value is multiplied by maximum color value
            unsigned char col = noise(x, y) * 255;

            // Put value to green channel for grass and blue + green channel for water for cyan colour
            grassTex[y * gen_width + x] = Color(0, col, 0, 150);
            waterTex[y * gen_width + x] = Color(0, col, col, 100);
        }
    }
    // Apply the new pixels
    grassTex.apply();
    waterTex.apply();
}

void draw(float deltaTime)
{
    // Animations

    // 1sec animation timer
    animationTimer += deltaTime;
    if (animationTimer > 1)
    {
        waterMovement = randomInt(0, 10);
        animationTimer = 0;
    }
    // Car movement
    carTimer += deltaTime * carSpeed;
    if (carTimer > 1900)
    {
        carTimer = -1900;
        carImg = randomCar();
        carImg3 = randomCar();
    }
    carTimer2 += deltaTime * carSpeed;
    if (carTimer > 1900)
    {
        carTimer = -1900;
        carImg2 = randomCar();
    }


    // Camera zoom and position

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

    // Move the world on the opposite direction to camera movement
    translate(-cameraX, -cameraY);


    // Drawing elements

    background(200, 255, 100);
    // Grass texture over background
    image(grassTex, -4000, -4000, 8000, 8000);


    // Roads
    noStroke();
    fill(colors::grey);
    // Intersecting roads. Width = 100
    rect(1000, -2000, 100, 8000); // Vertical
    rect(-2000, 300, 8000, 100); // Horizontal
    rect(1000, 1500, 3000, 100); // Horizontal under the houses


    // Swimming pool
    fill(colors::cyan);
    rect(400, 70, 200, 100);
    // Shadow
    fill(0, 200, 200);
    rect(400, 70, 200, 20);
    quad(400, 70, 420, 70, 400, 170, 410, 170);
    // Texture with some random movment to resemble water moving
    image(waterTex, 390 + waterMovement, 70, 210, 100);
    // Stone areas to hide the texture going over
    fill(colors::grey);
    rect(600, 70, 70, 100);
    rect(330, 70, 70, 100);

    // Houses
    for (House* house : houses)
    {
        strokeWeight(defaultBorder);
        fill(house->wallCol);
        rect(house->coordX, house->coordY, 100, house->stores * 100);
        // Shadow
        noStroke();
        fill(0, 0, 0, 50);
        rect(house->coordX + defaultBorder, house->coordY, 20, house->stores * 100 - defaultBorder);
        // Door
        fill(colors::brown);
        rect(house->coordX + 40, house->coordY + 60 + (house->stores - 1) * 100 - 5, 20, 40);
        // Windows
        fill(colors::cyan);
        rect(house->coordX + 30, house->coordY + (house->stores - 1) * 100 + 30, 15, 15);
        rect(house->coordX + 60, house->coordY + (house->stores - 1) * 100 + 30, 15, 15);
        // Extra windows for higher houses
        if (house->stores > 1)
        {
            for (int i = 0; i < house->stores - 1; i++)
            {
                rect(house->coordX + 30, house->coordY + i * 100 + 30, 15, 15);
                rect(house->coordX + 30, house->coordY + i * 100 + 70, 15, 15);
                rect(house->coordX + 60, house->coordY + i * 100 + 30, 15, 15);
                rect(house->coordX + 60, house->coordY + i * 100 + 70, 15, 15);
            }
        }
    }
    // Roofs 
    // This is separate to get all the roofs drawn on top of the houses
    for (House* house : houses)
    {
        strokeWeight(defaultBorder);
        fill(150,0,0); // Dark red
        triangle(house->coordX -20, house->coordY + 20,
                 house->coordX + 50, house->coordY - 40,
                 house->coordX + 120, house->coordY + 20);
    }


    // Cars
    // Car going to left
    image(*carImg3, -carTimer + 1000, 250, -carImg->width() / 3, carImg->height() / 3);
    // Car going to right
    image(*carImg, carTimer, 300, carImg->width() / 3, carImg->height() / 3);
    // rotate one car 90 degrees
    rotate(1.570796);
    image(*carImg2, carTimer, -1090, carImg->width() / 3, carImg->height() / 3);
    // Rotate back
    rotate(-1.570796);


    // Houses that go over the cars
    for (House* house : houses2)
    {
        strokeWeight(defaultBorder);
        fill(house->wallCol);
        rect(house->coordX, house->coordY, 100, house->stores * 100);
        // Shadow
        noStroke();
        fill(0, 0, 0, 50);
        rect(house->coordX + defaultBorder, house->coordY, 20, house->stores * 100 - defaultBorder);
        // Door
        fill(colors::brown);
        rect(house->coordX + 40, house->coordY + 60 + (house->stores - 1) * 100 - 5, 20, 40);
        // Windows
        fill(colors::cyan);
        rect(house->coordX + 30, house->coordY + (house->stores - 1) * 100 + 30, 15, 15);
        rect(house->coordX + 60, house->coordY + (house->stores - 1) * 100 + 30, 15, 15);
        // Extra windows for higher houses
        if (house->stores > 1)
        {
            for (int i = 0; i < house->stores - 1; i++)
            {
                rect(house->coordX + 30, house->coordY + i * 100 + 30, 15, 15);
                rect(house->coordX + 30, house->coordY + i * 100 + 70, 15, 15);
                rect(house->coordX + 60, house->coordY + i * 100 + 30, 15, 15);
                rect(house->coordX + 60, house->coordY + i * 100 + 70, 15, 15);
            }
        }
    }
    // Roofs 
    for (House* house : houses2)
    {
        strokeWeight(defaultBorder);
        fill(150, 0, 0); // Dark red
        triangle(house->coordX - 20, house->coordY + 20,
            house->coordX + 50, house->coordY - 40,
            house->coordX + 120, house->coordY + 20);
    }

    // Park
    fill(0,255,0,100);
    noStroke();
    rect(-1500, 500, 2000, 2000);

}


// Zoom with mouse scroll
void mouseWheel(float t)
{
    zoomlevel += t * 0.1f;
}

// Mouse click & drag camera movement
void mouseDragged()
{
    cursor(HAND);
    cameraX += (pmouseX - mouseX);
    cameraY += (pmouseY - mouseY);
}

void mouseReleased()
{
    cursor(ARROW);
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

    case VK_1: // Artstyle 1
        defaultBorder = 0;
    break;

    case VK_2: // Artstyle 2
        defaultBorder = 3;
    break;

    case VK_3: // Artstyle 3
        defaultBorder = 7;
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

    app.setMouseDragged(mouseDragged);
    app.setMouseReleased(mouseReleased);
    app.setMouseWheel(mouseWheel);
    app.setKeyPressed(keyPressed);

    return app.run(draw, setup);
}