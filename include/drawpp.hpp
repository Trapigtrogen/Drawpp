#ifndef DPP_H
#define DPP_H
#include <application.hpp>
#include <keys.hpp>
#include <image.hpp>
#include <shader.hpp>
#include <color.hpp>
#include <graphics.hpp>

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

// Shapes 3D
void point(int x, int y, int z);
void line(int x1, int y1, int z1, int x2, int y2, int z2);
void box(int size);
void box(int width, int height, int dimension);
void sphere(int radius);

void rectMode(PosMode m);
void ellipseMode(PosMode m);
void imageMode(PosMode m);
void strokeWeight(float w);
void strokeCap(CapStyle cap);
void clear();
void noFill();
void noStroke();
void noTint();

// Color
void fill(Color col);
void fill(int rgb);
void fill(int rgb, float alpha);
void fill(std::string hexCol);
void fill(float gray);
void fill(float gray, float alpha);
void fill(int v1, int v2, int v3);
void fill(int v1, int v2, int v3, float alpha);

void stroke(Color rgba);
void stroke(Color rgb, float alpha);
void stroke(std::string hexCol);
void stroke(float gray);
void stroke(float gray, float alpha);
void stroke(float v1, float v2, float v3);
void stroke(float v1, float v2, float v3, float alpha);

void background(Color col);
void background(const char* hexCol);
void background(int rgb);
void background(int rgb, float alpha);
void background(float gray);
void background(float gray, float alpha);
void background(int v1, int v2, int v3);
void background(int v1, int v2, int v3, float alpha);

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

// Input
extern char key;
extern int keyCode;
extern int mouseButton;

extern int mouseX;
extern int mouseY;
extern int pmouseX;
extern int pmouseY;

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

// Push Pop
void push();
void pop();
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

#endif