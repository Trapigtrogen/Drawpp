#include <drawpp.hpp>

DImage img;
DImage emptyImg;
DImage bg_img;

void setup() 
{
	img = loadImage("assets/img.jpg");
	bg_img = loadImage("assets/bg_img.jpg");
	emptyImg = loadImage("non-existing imagefile");

/*
	// DEGUB
	for(int i = 0; i < img.height*img.width*img.channels; i++) 
	{
		printf("%d ", img.pixels[i]);
	};
*/
}

void draw(float) 
{
	background(bg_img);
	imageMode(CORNER);
	image(img, 0, 0, 300, 300);
	image(bg_img, 500, 300, 100, 100);
}

int main()
{
	Application app(1000, 700);
	return app.run(draw, setup);
}