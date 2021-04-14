#include <drawpp.hpp>

DImage img;
DImage emptyImg;
DImage bg_img;

int imageW = 100;
int imageH = 100;
unsigned char* pixels = new unsigned char[imageW * imageH * 4];
std::vector<Color> pixelsVec;

void setup() 
{
	img = loadImage("assets/img.jpg");
	bg_img = loadImage("assets/bg_img.jpg");

	emptyImg = loadImage("non-existing imagefile"); // Error but no crash
}

void draw(float) 
{
	background(bg_img);
	imageMode(CORNER);
	image(img, 0, 0, 300, 300);
	image(bg_img, 500, 300, 100, 100);


	for (int y = 0; y < imageW; y++)
	{
		for (int x = 0; x < imageH; x++)
		{
			pixels[y * 4 * imageW + x * 4] = randomInt(255);			// RED
			pixels[y * 4 * imageW + x * 4 + 1] = randomInt(255);		// GREEN
			pixels[y * 4 * imageW + x * 4 + 2] = randomInt(255);		// BLUE
			pixels[y * 4 * imageW + x * 4 + 3] = 255;					// ALPHA

			Color col(randomInt(255), randomInt(255), randomInt(255), 255);
			pixelsVec.push_back(col);
		}
	}
	//emptyImg = createImage(pixels, imageW, imageH); // Create from char* pixel data
	emptyImg = createImage(pixelsVec, imageW, imageH); // Create from vector of Colors
	image(emptyImg, 400, 400, 200, 200);
	pixelsVec.clear();
}

int main()
{
	Application app(1000, 700);
	return app.run(draw, setup);
}