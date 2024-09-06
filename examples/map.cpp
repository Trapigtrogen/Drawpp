#include <drawpp.hpp>
#include <algorithm> // std::min

// Window settings
constexpr int Wwidth = 1500;
constexpr int Wheight = 1000;

// perlin noise settings
// The size of perlin noise will be 512px * 512px
constexpr int gen_height = 1024;
constexpr int gen_width = 1024;

// Camera
float zoomlevel = 0.0f;
int cameraX = -200;
int cameraY = -100;
constexpr float cameraSpeed = 10;
float visibleAreaX;
float visibleAreaY;

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
constexpr int gap = 10;
int defaultBorder = 0; // 0, 3 and 7 give nice different visual
std::vector<House*> houses;
std::vector<House*> houses2;


// Textures

// Environment
DImage grassTex;
DImage waterTex;
DImage bushTex;
DImage treeTex;
DImage gatewayTex;
// Water
DImage water0; // Empty state. No need to load texture. Otherwise treated as normal image
DImage water1; // State 1
DImage water2; // State 2
DImage water3; // State 3
std::vector<DImage*> waterAnimation; // Vector for all water animation images to push in
int currentWater = 0; // Select correct animation state image with this index in animation loop
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
constexpr int carSpeed = 250;
float carTimer = -100;
float carTimer2 = -1000;
float carTimer3 = -500;

// These image pointers represent the cars on the road
// They are randomily set to point one of the car images
DImage* carImg = &carYellow;
DImage* carImg2 = &carRed;
DImage* carImg3 = &carBlue;


// setup is called once before the application loop starts
void setup()
{
    // Limit fps
    frameRate(90);
    setTitle("Drawpp example: Game map");

    // Grass settings
    noiseSeed( randomInt(1000000) );
    noiseScale(1.1);
    noiseDetails(10);
    grassTex = DImage(gen_width, gen_height);
    waterTex = DImage(gen_width, gen_height);

    // Load car svg images as textures
    carYellow = loadImage("assets/map/carYellow.png");
    carRed = loadImage("assets/map/carRed.png");
    carBlue = loadImage("assets/map/carBlue.png");
    carGreen = loadImage("assets/map/carGreen.png");

    // Load bush and tree textures
    bushTex = loadImage("assets/map/bush.png");
    treeTex = loadImage("assets/map/tree.png");
    gatewayTex = loadImage("assets/map/gateway.png");

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
    // Apply new pixels
    grassTex.apply();
    waterTex.apply();

    // Push fountain animation textures in vector
    waterAnimation.push_back(&water0);
    water1 = loadImage("assets/map/water1.png");
    waterAnimation.push_back(&water1);
    water2 = loadImage("assets/map/water2.png");
    waterAnimation.push_back(&water2);
    water3 = loadImage("assets/map/water3.png");
    waterAnimation.push_back(&water3);
}

// draw is called once every frame
// deltaTime is the spent in the last frame
void draw(float deltaTime)
{
    // Animations

    // 1sec animation timer using the deltaTime as measurement
    animationTimer += deltaTime;
    if (animationTimer > 1)
    {
        // Pool water animation
        waterMovement = randomInt(0, 10); 

        // Fountain water animation
        currentWater++;
        if (currentWater == 4) currentWater = 0;

        // Animation timer reset
        animationTimer = 0;
    }

    // Car movement
    // Horizontal left to right
    carTimer += deltaTime * carSpeed; 
    if (carTimer > 3500)
    {
        carTimer = -3000;
        carImg = randomCar();
    }
    // Vertical
    carTimer2 += deltaTime * carSpeed;
    if (carTimer2 > 3500)
    {
        carTimer2 = -2300;
        carImg2 = randomCar();
    }
    // Horizontal right to left 
    carTimer3 += deltaTime * carSpeed;
    if (carTimer3 > 3500)
    {
        carTimer3 = -2700;
        carImg3 = randomCar();
    }


    // Camera zoom and position

    // Limit zoom level
    if (zoomlevel > 1) zoomlevel = 1;
    else if (zoomlevel < -1.0) zoomlevel = -1.0;
    
    // Apply zoom level
    // Calculate scale level so that the limit can be used in same scale
    // Since if we just use zoomlevel while going down and back up -> 100% * 90% * 110% = 99%
    scale(1.0f / (1.0f + (1.0f - zoomlevel)));

    // Limit camera movement area
    // Visible area relative to zoomlevel
    visibleAreaX = (1 + (1 - zoomlevel)) * Wwidth;
    visibleAreaY = (1 + (1 - zoomlevel)) * Wheight;
    // Min
    if (cameraX < -2000) cameraX = -2000;
    if (cameraY < -1000) cameraY = -1000;
    // Max
    if (cameraX > 3500 - visibleAreaX) cameraX = 3500 - visibleAreaX;
    if (cameraY > 2700 - visibleAreaY) cameraY = 2700 - visibleAreaY;

    // Move the world on the opposite direction to camera movement
    translate(-cameraX, -cameraY);


    // Drawing elements

    background(200, 255, 100);
    // Grass texture over background
    image(grassTex, -4000, -4000, 8000, 8000);


    // Roads
    noStroke();
    fill(colors::grey);
    rect(1000, -2000, 100, 8000);   // Vertical across the map
    rect(-2000, 300, 8000, 100);    // Horizontal across the map
    rect(1000, 1500, 3000, 100);    // Horizontal under the houses


    // Swimming pool
    fill(colors::cyan);
    rect(400, 70, 200, 100);
    // Shadow
    fill(0, 200, 200);
    rect(400, 70, 200, 20);
    quad(400, 70, 420, 70, 400, 170, 410, 170);
    // Texture with some random movment to resemble water moving
    image(waterTex, 380 + waterMovement * 2, 70, 220, 100);
    // Stone areas to hide the texture going over
    fill(colors::grey);
    rect(600, 70, 70, 100);
    rect(330, 70, 70, 100);

    // Houses
    stroke(colors::black);
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
    image(*carImg3, -carTimer3 + 1000, 250, -carImg->width() / 3, carImg->height() / 3);
    // Car going to right
    image(*carImg, carTimer, 300, carImg->width() / 3, carImg->height() / 3);
    // rotate one car 90 degrees
    rotate(HALF_PI);
    image(*carImg2, carTimer2, -1090, carImg->width() / 3, carImg->height() / 3);
    // Rotate back
    rotate(-HALF_PI);


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
    //noStroke();
    stroke(colors::grey);
    strokeWeight(10);
    rect(-1500, 500, 2000, 2000);

    // Pathways
    noStroke();
    fill(150, 75, 50, 100);
    rect(-540, 400, 80, 870);   // Above fountain
    rect(-540, 1730, 80, 770);  // Below fountain
    circle(-500, 1500, 230);    // Around fountain

    // Fountain
    fill(colors::grey);
    circle(-500, 1500, 150);
    fill(0, 150, 150);
    circle(-500, 1490, 135);
    fill(colors::lightgrey);
    circle(-500, 1490, 30);
    fill(colors::grey);
    circle(-500, 1490, 10);
    // Set the image x,y to mean the center of image
    // Moving the image to centre of fountain is now easier
    imageMode(CENTER); 
    image(*waterAnimation[currentWater], -500, 1490, waterAnimation[currentWater]->width()*3, waterAnimation[currentWater]->height()*3);
    // Set image coordinates back to up-left corner
    imageMode(CORNER);

    // Outline the park area with bushes
    for (int y = 515; y < 2450; y += bushTex.height()) 
    {
        image(bushTex, -1500, y, bushTex.width() / 2, bushTex.height());    // Left
        image(bushTex, 420, y, bushTex.width() / 2, bushTex.height());      // Right
    }
    for (int x = -1430; x < 410; x += bushTex.width())
    {
        // leave gateway
        if (x < -700 || x > -550)
        {
            image(bushTex, x, 480, bushTex.width(), bushTex.height());      // Top
        }
        else
        {
            image(gatewayTex, x - 20, 400, bushTex.width() + 40, gatewayTex.height());
        }
        image(bushTex, x, 2400, bushTex.width(), bushTex.height());         // Bottom
    }

    // Trees
    image(treeTex, 0, 1000, -treeTex.width() / 2, treeTex.height());

    image(treeTex, -1000, 700, treeTex.width(), treeTex.height());
    image(treeTex, -1200, 1200, -treeTex.width() / 2, treeTex.height());

    image(treeTex, -900, 2000, treeTex.width(), treeTex.height());
    image(treeTex, -1100, 1700, treeTex.width() / 2, treeTex.height() / 1.5);

    image(treeTex, -200, 1900, treeTex.width(), treeTex.height());
    image(treeTex, 50, 1800, treeTex.width() / 2, treeTex.height());

    // Bushes
    image(bushTex, -920, 1450, bushTex.width(), bushTex.height());
    image(bushTex, -250, 1450, bushTex.width(), bushTex.height());


    // Sea
    // Sand around the sea
    fill(200, 175, 50);
    rect(1100, 1600, 2300, 1200);
    // Sunbathing chairs + umbrellas
    for (int i = 0; i < 5; i++) 
    {
        fill(colors::brown);
        rect(1300 + i * 300, 1605, 20, 50);
        fill(150, 0, 50);
        ellipse(1300 + i*300 + 20, 1615, 35, 25);
    }
    // Dark sea bottom
    fill(100, 100, 50);
    rect(1300, 1750, 2000, 1000);
    // Texture with some random movment to resemble water moving
    image(waterTex, 1300, 1710 + waterMovement * 4, 2000, 1040);
}

// mouseWheel is called every time a mouse wheel is scrolled
// 't' indicates the distance and direction of the scroll
void mouseWheel(float t)
{
    // Zoom with mouse scroll
    zoomlevel += t * 0.1f;
}

// mouseDragged is called every time a mouse button is pressed
// down, and the mouse is moved
void mouseDragged()
{
    // Mouse click & drag camera movement
    cursor(HAND);

              //previous mouse position - current mouse position (both got from the engine)
    cameraX += (pmouseX - mouseX);
    cameraY += (pmouseY - mouseY);
}

// mouseReleased is called every time a mouse button is released
void mouseReleased()
{
    cursor(ARROW);
}

// keyPressed is called every time a keyboard key is pressed
// 'key' is the keycode of the last keyboard key to be pressed
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
            exit();
        break;
    }
}

int main()
{
    Application app(Wwidth, Wheight);

    app.setMouseDragged(mouseDragged);
    app.setMouseReleased(mouseReleased);
    app.setMouseWheel(mouseWheel);
    app.setKeyPressed(keyPressed);

    return app.run(draw, setup);
}