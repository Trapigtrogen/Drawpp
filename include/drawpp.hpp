#ifndef DPP_H
#define DPP_H
#include <application.hpp>

void draw();
void setup();
void runApp();

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

// Options
void fill(int rgb);
void fill(int rgb, int alpha);
void fill(int r, int g, int b);
void fill(int r, int g, int b, int alpha);

// Transform
void rotate(int rad);
void translate(int x, int y);
void translate(int x, int y, int z);

// Input


#endif