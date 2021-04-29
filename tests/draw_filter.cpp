#include <drawpp.hpp>

DImage img;
DImage emptyImg;
DImage bg_img;

void setup() 
{
	img = loadImage("assets/img.jpg");
	bg_img = loadImage("assets/bg_img.jpg");
}

float s = 0;

void draw(float) 
{
    s += 0.05;

	background(bg_img);
	imageMode(CORNER);
	image(img, 0, 0, 300, 300);
	image(bg_img, 500, 300, 100, 100);

    filter(PIXELATE, s);
}

int main()
{
	Application app(1000, 700);
	return app.run(draw, setup);
}