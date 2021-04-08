#include <drawpp.hpp>

DImage img;
DImage emptyImg;
DImage bg_img;

unsigned char* pixels = new unsigned char[100 * 100 * 4];

void setup() 
{
	img = loadImage("assets/img.jpg");
	bg_img = loadImage("assets/bg_img.jpg");

	emptyImg = loadImage("non-existing imagefile"); // Error but no crash

	for (int x = 0; x < 100 * 4; x += 4)
	{
		for (int y = 0; y < 100*4; y+=4)
		{
			pixels[y * 100 + x] = randomInt(255);			// RED
			pixels[y * 100 + x + 1] = randomInt(255);		// GREEN
			pixels[y * 100 + x + 2] = randomInt(255);		// BLUE
			pixels[y * 100 + x + 3] = 255;				// ALPHA    
		}
	}
	emptyImg = createImage(pixels, 100, 100);
}

void draw(float) 
{
	background(bg_img);
	imageMode(CORNER);
	image(img, 0, 0, 300, 300);
	image(bg_img, 500, 300, 100, 100);

	image(emptyImg, 400, 400, 200, 200);
}

int main()
{
	Application app(1000, 700);
	return app.run(draw, setup);
}