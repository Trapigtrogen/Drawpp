#include <drawpp.hpp>

DImage img;
DImage emptyImg;
DImage bg_img;

void setup() 
{
	img = loadImage("../../tests/assets/img.jpg");
	bg_img = loadImage("../../tests/assets/bg_img.jpg");
	//emptyImg = loadImage("non-existing imagefile"); // DEBUG: Still crashing the probram

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
	//background(bg_img);
	//imageMode(CORNER);
	//image(img, 0, 0);
	//image(bg_img, 0, 0);
}

int main()
{
	Application app(500, 300);
	return app.run(draw, setup);
}