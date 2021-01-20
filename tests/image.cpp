#include <drawpp.hpp>

DImage bg_img;
DImage img;

void setup() {
	bg_img = loadImage("assets/bg_img.jpg");
	img = loadImage("assets/img.jpg");
}

void draw() {
	background(bg_img);
	image(img, 0, 0);
}