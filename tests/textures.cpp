#include <drawpp.hpp>

DImage img;
DImage emptyImg;
DImage bg_img;

int imageW = 100;
int imageH = 100;
int channels = 4;
unsigned char* pixels = new unsigned char[imageW * imageH * channels];
std::vector<Color> pixelsVec;

void setup() 
{
	img = loadImage("assets/img.jpg");
	bg_img = loadImage("assets/bg_img.jpg");

	emptyImg = loadImage("non-existing imagefile"); // Error but no crash

	for (int x = 0; x < imageW * channels; x += channels)
	{
		for (int y = 0; y < imageH * channels; y += channels)
		{
			pixels[y * imageW + x] = randomInt(255);			// RED
			pixels[y * imageW + x + 1] = randomInt(255);		// GREEN
			pixels[y * imageW + x + 2] = randomInt(255);		// BLUE
			pixels[y * imageW + x + 3] = 255;					// ALPHA

			Color col(randomInt(255), randomInt(255), randomInt(255), 255);
			pixelsVec.push_back(col);
		}
	}
	//emptyImg = createImage(pixels, imageW, imageH); // Create from char* pixel data
	emptyImg = createImage(pixelsVec, imageW, imageH); // Create from vector of Colors
	pixelsVec.clear();
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