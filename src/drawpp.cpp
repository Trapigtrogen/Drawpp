#include <application.hpp>
#include <drawpp.hpp>
#include <time.hpp>
#include <chrono>
#include <thread>

void size(int width, int height)
{
    Application::GetInstance()->size(width,height);
}

void fullScreen(int monitor)
{
    Application::GetInstance()->setFullscreen(monitor);
}

void setTitle(const char* title)
{
    Application::GetInstance()->setTitle(title);
}

void exit()
{
    Application::GetInstance()->exit();
}

void cursor(CursorStyle c)
{
    Application::GetInstance()->setCursor(c);
}

void cursor(const DImage& c, int xorigin, int yorigin)
{
    Application::GetInstance()->setCursor(c,xorigin,yorigin);
}

void noCursor()
{
    Application::GetInstance()->hideCursor();
}

void frameRate(int fps)
{
    Application::GetInstance()->setFrameRate(fps);
}

void vSync(bool state)
{
    Application::GetInstance()->setVSync(state);
}

void delay(unsigned int millis)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}


// Random

void randomSeed(int seed)
{
    Application::GetInstance()->random.randomSeed(seed);
}

int randomInt(int high)
{
    return Application::GetInstance()->random.randomInt(high);
}

int randomInt(int low, int high)
{
    return Application::GetInstance()->random.randomInt(low,high);
}

/*
float randomFloat()
{
    return Application::GetInstance()->random.randomFloat();
}
*/

float randomFloat(float low, float high)
{
    return Application::GetInstance()->random.randomFloat(low,high);
}

float randomGaussian()
{
    return Application::GetInstance()->random.randomGaussian();
}


// Noise

float noise(int x)
{
    return Application::GetInstance()->noise.pNoise(x);
}

float noise(int x, int y)
{
    return Application::GetInstance()->noise.pNoise(x, y);
}

void noiseSeed(int seed)
{
    Application::GetInstance()->noise.noiseSeed(seed);
}

void noiseScale(float scale)
{
    Application::GetInstance()->noise.setScale(scale);
}

void noiseDetails(int lod)
{
    Application::GetInstance()->noise.setOctaves(lod);
}

void noiseDetails(int lod, float falloff)
{
    Application::GetInstance()->noise.setOctaves(lod);
    Application::GetInstance()->noise.setFalloff(falloff);
}

void noiseMapSize(int width, int heigth) 
{
    Application::GetInstance()->noise.resize(width, heigth);
}



void rectMode(PosMode m)
{
    Application::GetInstance()->graphics_object().rectMode(m);
}

void ellipseMode(PosMode m)
{
    Application::GetInstance()->graphics_object().ellipseMode(m);
}

void imageMode(PosMode m)
{
    Application::GetInstance()->graphics_object().imageMode(m);
}

void strokeWeight(float w)
{
    Application::GetInstance()->graphics_object().strokeWeight(w);
}

void strokeCap(CapStyle cap)
{
    Application::GetInstance()->graphics_object().strokeCap(cap);
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

void bezierDetail(float d)
{
    Application::GetInstance()->graphics_object().bezierDetail(d);
}

long long millis()
{
    return Time::millis();
}

int second()
{
    return Time::second();
}

int minute()
{
    return Time::minute();
}

int hour()
{
    return Time::hour();
}

int day()
{
    return Time::day();
}

int month()
{
    return Time::month();
}

int year()
{
    return Time::year();
}

void timeReset()
{
    return Time::Reset();
}

// Color

void fill(Color col) 
{
    // DEBUG TODO: RGB/HSB Modes
    Application::GetInstance()->graphics_object().fill(col);
}

void fill(Color rgb, float alpha)
{
    Application::GetInstance()->graphics_object().fill(rgb,alpha);
}

void fill(float gray)
{
    Application::GetInstance()->graphics_object().fill(gray);
}

void fill(float gray, float alpha)
{
    Application::GetInstance()->graphics_object().fill(gray, alpha);
}

void fill(float v1, float v2, float v3)
{
    Application::GetInstance()->graphics_object().fill(v1, v2, v3);
}

void fill(float v1, float v2, float v3, float alpha)
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
    Application::GetInstance()->graphics_object().background(col);
}

void background(const char* hexCol) 
{
    Application::GetInstance()->graphics_object().background(Color(hexCol));
}

void background(Color rgb, float alpha)
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

void background(float v1, float v2, float v3)
{
    Application::GetInstance()->graphics_object().background(v1, v2, v3);
}

void background(float v1, float v2, float v3, float alpha)
{
    Application::GetInstance()->graphics_object().background(v1, v2, v3, alpha);
}

void tint(Color col)
{
    Application::GetInstance()->graphics_object().tint(col);
}

void tint(Color rgb, float alpha)
{
    Application::GetInstance()->graphics_object().tint(rgb, alpha);
}

void tint(const char* hexCol)
{
    Application::GetInstance()->graphics_object().tint(Color(hexCol));
}

void tint(float gray)
{
    Application::GetInstance()->graphics_object().tint(gray);
}

void tint(float gray, float alpha)
{
    Application::GetInstance()->graphics_object().tint(gray, alpha);
}

void tint(float v1, float v2, float v3)
{
    Application::GetInstance()->graphics_object().tint(v1, v2, v3);
}

void tint(float v1, float v2, float v3, float alpha)
{
    Application::GetInstance()->graphics_object().tint(v1, v2, v3, alpha);
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

std::string hex(Color col)
{
    return Color::hex(col, 8);
}

std::string hex(Color col, int num) 
{
    return Color::hex(col, num);
}


// Image

DImage loadImage(const std::string& fileName)
{
    return DImage::loadImage(fileName);
}

DImage createImage(unsigned char* pixelData, int width, int height)
{
	unsigned char* pixels = new unsigned char[width*height*4];
	for(int i = 0; i < width*height*4; i++)
	{
		pixels[i] = pixelData[i];
	}

    return DImage::createImage(pixels, width, height);
}

DImage createImage(std::vector<Color> pixelData, int width, int height)
{
    unsigned char* pixels = new unsigned char[width*height*4];
    for (size_t i = 0; i < pixelData.size(); i++)
    {
        pixels[4 * i] = pixelData.at(i).red();
        pixels[4 * i + 1] = pixelData.at(i).green();
        pixels[4 * i + 2] = pixelData.at(i).blue();
        pixels[4 * i + 3] = pixelData.at(i).alpha();
    }

    return DImage::createImage(pixels, width, height);
}

DImage loadSVGImage(const std::string& filename, float scale)
{
    return DImage::loadSVGImage(filename,scale);
}

void image(const DImage& image, float x, float y)
{
    Application::GetInstance()->graphics_object().image(image,x,y);
}

void image(const DImage& image, const DVector& p)
{
    Application::GetInstance()->graphics_object().image(image,p);
}

void image(const DImage& image, float x, float y, float width, float height)
{
    Application::GetInstance()->graphics_object().image(image,x,y,width,height);
}

void image(const DImage& image, const DVector& p, const DVector s)
{
    Application::GetInstance()->graphics_object().image(image,p,s);
}

void image(const DGraphics& target, float x, float y )
{
    Application::GetInstance()->graphics_object().image(target,x,y);
}

void image(const DGraphics& target, const DVector& p)
{
    Application::GetInstance()->graphics_object().image(target,p);
}

void image(const DGraphics& target, float x, float y, float w, float h)
{
    Application::GetInstance()->graphics_object().image(target,x,y,w,h);
}

void image(const DGraphics& target, const DVector& p, const DVector& s)
{
    Application::GetInstance()->graphics_object().image(target,p,s);
}

void background(const DImage& image)
{
    Application::GetInstance()->graphics_object().background(image);
}

void filter(const DFilter& f, std::function<void(unsigned int)> initializer)
{
    Application::GetInstance()->graphics_object().filter(f,initializer);
}

void filter(filters f, float param)
{
    Application::GetInstance()->graphics_object().filter(f,param);
}


DFilter loadFilter(const std::string& filterSource)
{
    return DFilter::loadFilter(filterSource);
}

DFilter loadFilterFromFile(const std::string& filename)
{
    return DFilter::loadFile(filename);
}


// Shapes
void shape(const DShape& _shape) 
{
    Application::GetInstance()->graphics_object().shape(_shape, 0, 0, 1, 1);
}

void shape(const DShape& _shape, float x, float  y)
{
    //shape(_shape, 0, 0, x, y);
    Application::GetInstance()->graphics_object().shape(_shape, x,y,1,1);
}

void shape(const DShape& _shape, float x, float y, float w, float h)
{
    Application::GetInstance()->graphics_object().shape(_shape, x, y, w, h);
}

DShape loadShape(const std::string& filename) 
{
    return DShape::loadShape(filename);
}

/*
DShape createShape()
{
    return DShape::createShape();
}

DShape createShape(DShape::ShapeType type)
{
    return DShape::createShape(type);
}
*/
//DShape createShape(DShape::ShapeType type, float[] p){}



void rect(float x, float y, float w, float h)
{
    Application::GetInstance()->graphics_object().rect(x,y,w,h);
}

void rect(const DVector& p, const DVector& s)
{
    Application::GetInstance()->graphics_object().rect(p,s);
}

void rect(float x, float y, float w, float h, float r)
{
    Application::GetInstance()->graphics_object().rect(x,y,w,h,r);
}

void rect(const DVector& p, const DVector& s, float radii)
{
    Application::GetInstance()->graphics_object().rect(p,s,radii);
}

void rect(float x, float y, float w, float h, float tl, float tr, float br, float bl)
{
    Application::GetInstance()->graphics_object().rect(x,y,w,h,tl,tr,br,bl);
}

void rect(const DVector& p, const DVector& s, float tl, float tr, float br, float bl)
{
    Application::GetInstance()->graphics_object().rect(p,s,tl,tr,br,bl);
}

void square(float x, float y, float size)
{
    Application::GetInstance()->graphics_object().square(x,y,size);
}

void square(const DVector& p, float size)
{
    Application::GetInstance()->graphics_object().square(p,size);
}

void circle(float x, float y, float radius)
{
    Application::GetInstance()->graphics_object().circle(x,y,radius);
}

void circle(const DVector& p, float radius)
{
    Application::GetInstance()->graphics_object().circle(p,radius);
}

void ellipse(float x, float y, float width, float height)
{
    Application::GetInstance()->graphics_object().ellipse(x,y,width,height);
}

void ellipse(const DVector& p, const DVector& s)
{
    Application::GetInstance()->graphics_object().ellipse(p,s);
}

void line(float x1, float y1, float x2, float y2)
{
    Application::GetInstance()->graphics_object().line(x1,y1,x2,y2);
}

void line(const DVector& p1,const DVector& p2)
{
    Application::GetInstance()->graphics_object().line(p1,p2);
}

void point(float x, float y)
{
    Application::GetInstance()->graphics_object().point(x,y);
}

void point(const DVector& p)
{
    Application::GetInstance()->graphics_object().point(p);
}

void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    Application::GetInstance()->graphics_object().quad(x1,y1,x2,y2,x3,y3,x4,y4);
}

void quad(const DVector& p1, const DVector& p2, const DVector& p3, const DVector& p4)
{
    Application::GetInstance()->graphics_object().quad(p1,p2,p3,p4);
}


void triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    Application::GetInstance()->graphics_object().triangle(x1,y1,x2,y2,x3,y3);
}

void triangle(const DVector& p1, const DVector& p2, const DVector& p3)
{
    Application::GetInstance()->graphics_object().triangle(p1,p2,p3);
}

void bezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2)
{
    Application::GetInstance()->graphics_object().bezier(x1,y1,x2,y2,cx1,cy1,cx2,cy2);
}

void bezier(const DVector& p1, const DVector& p2, const DVector& cp1, const DVector& cp2)
{
    Application::GetInstance()->graphics_object().bezier(p1,p2,cp1,cp2);
}

void bezier(float x1, float y1, float x2, float y2, float cx, float cy)
{
    Application::GetInstance()->graphics_object().bezier(x1,y1,x2,y2,cx,cy);
}

void bezier(const DVector& p1, const DVector& p2, const DVector& cp)
{
    Application::GetInstance()->graphics_object().bezier(p1,p2,cp);
}


// Shader

//Shader loadShadersFromFile(const char* vertexShader, const char* fregmentShader)
//{
//    return Shader::loadShadersFromFile(vertexShader, fregmentShader);
//}
//
//Shader loadShadersFromString(const char* vertexShader, const char* fregmentShader)
//{
//    return Shader::loadShadersFromString(vertexShader, fregmentShader);
//}
//
//Shader loadShadersDefault()
//{
//    return Shader::loadShadersDefault();
//}


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

void shearX(float a)
{
    Application::GetInstance()->graphics_object().shearX(a);
}

void shearY(float a)
{
    Application::GetInstance()->graphics_object().shearY(a);
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

void applyMatrix(const DMatrix4& m)
{
    Application::GetInstance()->graphics_object().applyMatrix(m);
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

bool save(const std::string& filename, ImageFormat format)
{
    return Application::GetInstance()->graphics_object().save(filename,format);
}

// Font and text

DFont loadFont(const std::string& filename, int size, float row_spacing, float char_spacing)
{
    return DFont::load(filename,size,row_spacing,char_spacing);
}

DFont loadFont(const std::string& filename, const FontOptions& opt)
{
    return DFont::load(filename,opt);
}

void textFont(DFont font)
{
    Application::GetInstance()->graphics_object().textFont(font);
}

void text(const std::string& txt, float x, float y)
{
    Application::GetInstance()->graphics_object().text(txt,x,y);
}

void text(const std::string& txt, const DVector& p)
{
    text(txt,p.x,p.y);
}

void text(const std::wstring& txt, float x, float y)
{
    Application::GetInstance()->graphics_object().text(txt,x,y);
}

void text(const std::wstring& txt, const DVector& p)
{
    text(txt,p.x,p.y);
}
