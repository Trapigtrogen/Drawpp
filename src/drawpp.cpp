#include <application.hpp>
#include <drawpp.hpp>

void size(int width, int height)
{
    Application::GetInstance()->size(width,height);
}

void setTitle(const char* title)
{
    Application::GetInstance()->setTitle(title);
}

void setResizable(bool state)
{
    Application::GetInstance()->setResizable(state);
}

void exit()
{
    Application::GetInstance()->exit();
}

// Random

void randomSeed(int seed)
{
    Application::GetInstance()->random.randomSeed(seed);
}

int random(int high)
{
    return Application::GetInstance()->random.random(high);
}

int random(int low, int high)
{
    return Application::GetInstance()->random.random(low,high);
}

float random()
{
    return Application::GetInstance()->random.random();
}

float randomf(float low, float high)
{
    return Application::GetInstance()->random.randomf(low,high);
}

float randomGaussian()
{
    return Application::GetInstance()->random.randomGaussian();
}

// Color

void fill(Color col) 
{
    // DEBUG TODO: RGB/HSB Modes
    //Application::GetInstance()->graphics->fill(col.red(), col.green(), col.blue(), col.alpha());
}

void fill(int rgb)
{
    //Application::GetInstance()->graphics->fill(rgb);
}

void fill(int rgb, float alpha)
{
    //Application::GetInstance()->graphics->fill(rgb);
}

void fill(float gray)
{
    //Application::GetInstance()->graphics->fill(gray);
}

void fill(float gray, float alpha)
{
    //Application::GetInstance()->graphics->fill(gray, alpha);
}

void fill(int v1, int v2, int v3)
{
    //Application::GetInstance()->graphics->fill(v1, v2, v3);
}

void fill(int v1, int v2, int v3, float alpha)
{
    //Application::GetInstance()->graphics->fill(v1, v2, v3, alpha);
}


void background(Color col) {
    // DEBUG TODO: RGB/HSB Modes
    //Application::GetInstance()->graphics->background(col.red(), col.green(), col.blue(), col.alpha());
}

void background(int rgb)
{
    //Application::GetInstance()->graphics->background(rgb);
}

void background(int rgb, float alpha)
{
    //Application::GetInstance()->graphics->background(rgb, alpha);
}

void background(float gray)
{
    //Application::GetInstance()->graphics->background(gray);
}

void background(float gray, float alpha)
{
    //Application::GetInstance()->graphics->background(gray, alpha);
}

void background(int v1, int v2, int v3)
{
    //Application::GetInstance()->graphics->background(v1, v2, v3);
}

void background(int v1, int v2, int v3, float alpha)
{
    //Application::GetInstance()->graphics->background(v1, v2, v3, alpha);
}


uint8_t alpha(Color col)
{
    return col.alpha();
}

uint8_t red(Color col)
{
    return col.red();
}

uint8_t green(Color col)
{
    return col.green();
}

uint8_t blue(Color col)
{
    return col.blue();
}

uint8_t hue(Color col)
{
    return col.hue();
}

uint8_t saturation(Color col)
{
    return col.saturation();
}

uint8_t brightness(Color col)
{
    return col.brightness();
}

/*
Color lerpColor(Color from, Color to, float percentage)
{
    return Color::lerpColor(&from, &to, percentage);
}
*/

// Image

DImage loadImage(const std::string& fileName) 
{
    return DImage::loadImage(fileName);
}

void image(DImage image, int x, int y) 
{
    image.drawImage(x, y, image.width, image.height);
}

void image(DImage image, int x, int y, int width, int height) {
    image.drawImage(x, y, width, height);
}

void background(DImage image) 
{
    // DEBUG TODO: Set background to image.pixels
}

// Shapes

void rect(int x, int y, int width, int height)
{

}

// Shader

Shader loadShadersFromFile(const char* vertexShader, const char* fregmentShader)
{
    return Shader::loadShadersFromFile(vertexShader, fregmentShader);
}

Shader loadShadersFromString(const char* vertexShader, const char* fregmentShader)
{
    return Shader::loadShadersFromString(vertexShader, fregmentShader);
}

Shader loadShadersDefault()
{
    return Shader::loadShadersDefault();
}
