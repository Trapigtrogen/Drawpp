#include <drawpp.hpp>

DImage img;
DImage bg_img;

void setup() 
{
	img = loadImage("D:/Projects/CPP/graphics-library/tests/assets/img.jpg");
	bg_img = loadImage("D:/Projects/CPP/graphics-library/tests/assets/bg_img.jpg");

	// DEGUB
	/*
	for(int i = 0; i < strlen((char*)img.pixels); i++) {
		printf("%d ", img.pixels[i]);
	};
	*/

}

void draw(float) 
{
	//background(bg_img);
	//imageMode(CORNER);
	image(img, 0, 0);
	//image(bg_img, 0, 0);
}

int main()
{
	Application app(500, 300);
	return app.run(draw, setup);
}