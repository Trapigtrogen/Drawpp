#include <drawpp.hpp>

DImage bg_img;
DImage img;

void setup() {
	bg_img = loadImage("D:/Projects/CPP/graphics-library/tests/assets/bg_img.jpg");
	img = loadImage("D:/Projects/CPP/graphics-library/tests/assets/img.jpg");
}

void draw(float) {
	//background(bg_img);
	//image(img, 0, 0);
}

int main() {
	Application app(500, 300);
	return app.run(draw, setup);
}