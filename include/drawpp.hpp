#ifndef DPP_H
#define DPP_H
#include <application.hpp>
#include <keys.hpp>
#include <image.hpp>
#include <shader.hpp>
#include <color.hpp>
#include <graphics.hpp>
#include <shape.hpp>
#include <font.hpp>
#include <constants.hpp>

void exit();

// Window
void size(int width, int height);
void setResizable(bool);
void setTitle(const char* title);

// DShape
// Draws given shape
void shape(DShape shape, int x,int  y);
void shape(DShape shape, int x, int y, int w, int h);
DShape loadShape(std::string filename);
DShape createShape();
DShape createShape(DShape::ShapeType type);
//DShape createShape(DShape::ShapeType type, float[] p);

// Shapes 2D
void arc(int x, int y, int width, int height, int start, int stop);
void arc(int x, int y, int width, int height, int start, int stop, int mode);
void circle(float x, float y, float radius);
void ellipse(float x, float y, float width, float height);
void line(float x1, float y1, float x2, float y2);
void line(const DVector& p1,const DVector& p2);
void point(float x, float y);
void point(const DVector& p);
void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void quad(const DVector& p1, const DVector& p2, const DVector& p3, const DVector& p4);
void rect(float x, float y, float w, float h);
void rect(float x, float y, float w, float h, float r);
void rect(float x, float y, float w, float h, float tl, float tr, float br, float bl);
void square(float x, float y, float size);
void triangle(float x1, float y1, float x2, float y2, float x3, float y3);
void triangle(const DVector& p1, const DVector& p2, const DVector& p3);
void bezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2);
void bezier(const DVector& p1, const DVector& p2, const DVector& cp1, const DVector& cp2);
void bezier(float x1, float y1, float x2, float y2, float cx, float cy);
void bezier(const DVector& p1, const DVector& p2, const DVector& cp);

// Shapes 3D
void point(int x, int y, int z);
void line(int x1, int y1, int z1, int x2, int y2, int z2);
void box(int size);
void box(int width, int height, int dimension);
void sphere(int radius);

// Font and text

DFont loadFont(const std::string& filename, int size, float row_spacing = 0.0f, float char_spacing = 0.0f);
DFont loadFont(const std::string& filename, const FontOptions& opt);
void textFont(DFont font);
void text(const std::string& txt, float x, float y);
void text(const std::string& txt, const DVector& p);
void text(const std::wstring& txt, float x, float y);
void text(const std::wstring& txt, const DVector& p);

void rectMode(PosMode m);
void ellipseMode(PosMode m);
void imageMode(PosMode m);
void strokeWeight(float w);
void strokeCap(CapStyle cap);
void clear();
void noFill();
void noStroke();
void noTint();
void bezierDetail(float d);

// Color
void fill(Color col);
void fill(Color rgb, float alpha);
void fill(std::string hexCol);
void fill(float gray);
void fill(float gray, float alpha);
void fill(float v1, float v2, float v3);
void fill(float v1, float v2, float v3, float alpha);

void stroke(Color rgba);
void stroke(Color rgb, float alpha);
void stroke(std::string hexCol);
void stroke(float gray);
void stroke(float gray, float alpha);
void stroke(float v1, float v2, float v3);
void stroke(float v1, float v2, float v3, float alpha);

void background(Color col);
void background(Color rgb, float alpha);
void background(const char* hexCol);
void background(float gray);
void background(float gray, float alpha);
void background(float v1, float v2, float v3);
void background(float v1, float v2, float v3, float alpha);

void tint(Color col);
void tint(Color rgb, float alpha);
void tint(const char* hexCol);
void tint(float gray);
void tint(float gray, float alpha);
void tint(float v1, float v2, float v3);
void tint(float v1, float v2, float v3, float alpha);

void colorMode(ColorMode mode);
void colorMode(ColorMode mode, float max);
void colorMode(ColorMode mode, float max1, float max2, float max3);
void colorMode(ColorMode mode, float max1, float max2, float max3, float maxA);

Color color(float grey);
Color color(float grey, float alpha);
Color color(float v1, float v2, float v3);
Color color(float v1, float v2, float v3, float alpha);

float alpha(Color col);
float red(Color col);
float green(Color col);
float blue(Color col);
float hue(Color col);
float saturation(Color col);
float brightness(Color col);

// Lerps color. Percentage needs to be in range 0.0 - 1.0 or it will be cut to closest point
Color lerpColor(const Color& from, const Color& to, float percentage);
std::string hex(Color col);
std::string hex(Color col, int num);

// Image
DImage loadImage(const std::string& fileName);
void image(const DImage& image, float x, float y);
void image(const DImage& image, float x, float y, float width, float height);
void background(const DImage& image);

// Shader
Shader loadShadersFromFile(const char* vertexShader, const char* fregmentShader);
Shader loadShadersFromString(const char* vertexShader, const char* fregmentShader);
Shader loadShadersDefault();

// Transform
void translate(float x, float y);
void translate(float x, float y, float z);
void translate(const DVector& t);

void rotate(float angle);
void rotateX(float angle);
void rotateY(float angle);
void rotateZ(float angle);

void scale(float s);
void scale(float x, float y);
void scale(float x, float y, float z);
void scale(const DVector& s);

void shearX(float a);
void shearY(float a);

// Input
extern char key;
extern int keyCode;
extern int mouseButton;

extern int mouseX;
extern int mouseY;
extern int pmouseX;
extern int pmouseY;
extern int pfmouseX;
extern int pfmouseY;

// Random
void randomSeed(int seed);
int randomInt(int high);
int randomInt(int low, int high);
//float randomFloat();
float randomFloat(float low, float high);
float randomGaussian();

// Noise
float noise(int x);
float noise(int x, int y);
void noiseSeed(int x);
void noiseScale(float scale);
void noiseDetails(int lod);
void noiseDetails(int lod, float falloff);
void noiseMapSize(int width, int heigth);

// Push Pop
void push();
void pop();
void applyMatrix(const DMatrix4& m);
void pushMatrix();
void popMatrix();
void pushStyle();
void popStyle();

//Time
long long millis();
int second();
int minute();
int hour();
int day();
int month();
int year();
void timeReset();

// Save screenshot
bool save(const std::string& filename, ImageFormat format = ImageFormat::PNG);

#endif