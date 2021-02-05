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

// Shapes 2D
void arc(int x, int y, int width, int height, int start, int stop);
void arc(int x, int y, int width, int height, int start, int stop, int mode);
void circle(int x, int y, int radius);
void ellipse(int x, int y, int width, int height);
void line(int x1, int y1, int x2, int y2);
void point(int x, int y);
void quad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void rect(int x, int y, int w, int h);
void square(int x, int y, int size);
void triangle(int x1, int y1, int x2, int y2, int x3, int y3);

// Shapes 3D
void point(int x, int y, int z);
void line(int x1, int y1, int z1, int x2, int y2, int z2);
void box(int size);
void box(int width, int height, int dimension);
void sphere(int radius);

// Color
void fill(Color col);
void fill(int rgb);
void fill(int rgb, float alpha);
void fill(float gray);
void fill(float gray, float alpha);
void fill(int v1, int v2, int v3);
void fill(int v1, int v2, int v3, float alpha);

void background(Color col);
void background(int rgb);
void background(int rgb, float alpha);
void background(float gray);
void background(float gray, float alpha);
void background(int v1, int v2, int v3);
void background(int v1, int v2, int v3, float alpha);

float alpha(Color col);
float red(Color col);
float green(Color col);
float blue(Color col);
float hue(Color col);
float saturation(Color col);
float brightness(Color col);

// Lerps color. Percentage needs to be in range 0.0 - 1.0 or it will be cut to closest point
Color lerpColor(Color from, Color to, float percentage);

// Image
DImage loadImage(const std::string& fileName);
void image(DImage image, int x, int y);
void image(DImage image, int x, int y, int width, int height);
void background(DImage image);

// Shader
Shader loadShadersFromFile(const char* vertexShader, const char* fregmentShader);
Shader loadShadersFromString(const char* vertexShader, const char* fregmentShader);
Shader loadShadersDefault();

// Transform
void rotate(int rad);
void translate(int x, int y);
void translate(int x, int y, int z);

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
int random(int high);
int random(int low, int high);
float random();
float randomf(float low, float high);
float randomGaussian();

#endif