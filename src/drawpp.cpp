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


void strokeWeight(float w)
{
    Application::GetInstance()->graphics_object().strokeWeight(w);
}

void clear()
{
    Application::GetInstance()->graphics_object().clear();
}

void noFill()
{
    Application::GetInstance()->graphics_object().noFill();
}

void noStroke()
{
    Application::GetInstance()->graphics_object().noStroke();
}

void noTint()
{
    Application::GetInstance()->graphics_object().noTint();
}



// Color

void fill(Color col) 
{
    // DEBUG TODO: RGB/HSB Modes
    Application::GetInstance()->graphics_object().fill(col.red(), col.green(), col.blue(), col.alpha());
}

void fill(int rgb)
{
    Application::GetInstance()->graphics_object().fill(rgb);
}

void fill(int rgb, float alpha)
{
    Application::GetInstance()->graphics_object().fill(rgb);
}

void fill(float gray)
{
    Application::GetInstance()->graphics_object().fill(gray);
}

void fill(float gray, float alpha)
{
    Application::GetInstance()->graphics_object().fill(gray, alpha);
}

void fill(int v1, int v2, int v3)
{
    Application::GetInstance()->graphics_object().fill(v1, v2, v3);
}

void fill(int v1, int v2, int v3, float alpha)
{
    Application::GetInstance()->graphics_object().fill(v1, v2, v3, alpha);
}

void stroke(Color rgba)
{
    Application::GetInstance()->graphics_object().stroke(rgba);
}

void stroke(Color rgb, float alpha)
{
    Application::GetInstance()->graphics_object().stroke(rgb,alpha);
}

void stroke(float gray)
{
    Application::GetInstance()->graphics_object().stroke(gray);
}

void stroke(float gray, float alpha)
{
    Application::GetInstance()->graphics_object().stroke(gray,alpha);
}

void stroke(float v1, float v2, float v3)
{
    Application::GetInstance()->graphics_object().stroke(v1,v2,v3);
}

void stroke(float v1, float v2, float v3, float alpha)
{
    Application::GetInstance()->graphics_object().stroke(v1,v2,v3,alpha);
}


void background(Color col) {
    // DEBUG TODO: RGB/HSB Modes
    Application::GetInstance()->graphics_object().background(col.red(), col.green(), col.blue(), col.alpha());
}

void background(int rgb)
{
    Application::GetInstance()->graphics_object().background(rgb);
}

void background(int rgb, float alpha)
{
    Application::GetInstance()->graphics_object().background(rgb, alpha);
}

void background(float gray)
{
    Application::GetInstance()->graphics_object().background(gray);
}

void background(float gray, float alpha)
{
    Application::GetInstance()->graphics_object().background(gray, alpha);
}

void background(int v1, int v2, int v3)
{
    Application::GetInstance()->graphics_object().background(v1, v2, v3);
}

void background(int v1, int v2, int v3, float alpha)
{
    Application::GetInstance()->graphics_object().background(v1, v2, v3, alpha);
}

void colorMode(ColorMode mode)
{
    Application::GetInstance()->graphics_object().colorMode(mode);
}

void colorMode(ColorMode mode, float max)
{
    Application::GetInstance()->graphics_object().colorMode(mode,max);
}

void colorMode(ColorMode mode, float max1, float max2, float max3)
{
    Application::GetInstance()->graphics_object().colorMode(mode,max1,max2,max3);
}

void colorMode(ColorMode mode, float max1, float max2, float max3, float maxA)
{
    Application::GetInstance()->graphics_object().colorMode(mode,max1,max2,max3,maxA);
}

Color color(float grey)
{
    return Application::GetInstance()->graphics_object().color(grey);
}

Color color(float grey, float alpha)
{
    return Application::GetInstance()->graphics_object().color(grey,alpha);
}

Color color(float v1, float v2, float v3)
{
    return Application::GetInstance()->graphics_object().color(v1,v2,v3);
}

Color color(float v1, float v2, float v3, float alpha)
{
    return Application::GetInstance()->graphics_object().color(v1,v2,v3,alpha);
}


float alpha(Color col)
{
    return Application::GetInstance()->graphics_object().alpha(col);
}

float red(Color col)
{
    return Application::GetInstance()->graphics_object().red(col);
}

float green(Color col)
{
    return Application::GetInstance()->graphics_object().green(col);
}

float blue(Color col)
{
    return Application::GetInstance()->graphics_object().blue(col);
}

float hue(Color col)
{
    return Application::GetInstance()->graphics_object().hue(col);
}

float saturation(Color col)
{
    return Application::GetInstance()->graphics_object().saturation(col);
}

float brightness(Color col)
{
    return Application::GetInstance()->graphics_object().brightness(col);
}

Color lerpColor(const Color &from, const Color& to, float percentage)
{
    return Color::lerpColor(from, to, percentage);
}

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
    Application::GetInstance()->graphics_object().rect(x,y,width,height);
}

void rect(float x, float y, float w, float h, float r)
{
    Application::GetInstance()->graphics_object().rect(x,y,w,h,r);
}

void rect(float x, float y, float w, float h, float tl, float tr, float br, float bl)
{
    Application::GetInstance()->graphics_object().rect(x,y,w,h,tl,tr,br,bl);
}


void circle(float x, float y, float radius)
{
    Application::GetInstance()->graphics_object().circle(x,y,radius);
}

void ellipse(float x, float y, float width, float height)
{
    Application::GetInstance()->graphics_object().ellipse(x,y,width,height);
}

void rect(float x, float y, float w, float h)
{
    Application::GetInstance()->graphics_object().rect(x,y,w,h);
}

void square(float x, float y, float size)
{
    Application::GetInstance()->graphics_object().square(x,y,size);
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


// Transform

void translate(float x, float y)
{
    Application::GetInstance()->graphics_object().translate(x,y);
}

void translate(float x, float y, float z)
{
    Application::GetInstance()->graphics_object().translate(x,y,z);
}

void translate(const DVector& t)
{
    Application::GetInstance()->graphics_object().translate(t);
}

void rotate(float angle)
{
    Application::GetInstance()->graphics_object().rotate(angle);
}

void rotateX(float angle)
{
    Application::GetInstance()->graphics_object().rotateX(angle);
}

void rotateY(float angle)
{
    Application::GetInstance()->graphics_object().rotateY(angle);
}

void rotateZ(float angle)
{
    Application::GetInstance()->graphics_object().rotateZ(angle);
}

void scale(float s)
{
    Application::GetInstance()->graphics_object().scale(s);
}

void scale(float x, float y)
{
    Application::GetInstance()->graphics_object().scale(x,y);
}

void scale(float x, float y, float z)
{
    Application::GetInstance()->graphics_object().scale(x,y,z);
}

void scale(const DVector& s)
{
    Application::GetInstance()->graphics_object().scale(s);
}


// Push Pop

void push()
{
    Application::GetInstance()->graphics_object().push();
}

void pop()
{
    Application::GetInstance()->graphics_object().pop();
}

void pushMatrix()
{
    Application::GetInstance()->graphics_object().pushMatrix();
}

void popMatrix()
{
    Application::GetInstance()->graphics_object().popMatrix();
}

void pushStyle()
{
    Application::GetInstance()->graphics_object().pushStyle();
}

void popStyle()
{
    Application::GetInstance()->graphics_object().popStyle();
}
