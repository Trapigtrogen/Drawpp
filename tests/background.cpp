#include <drawpp.hpp>

void setup()
{
	//colorMode(RGB); // How to make RGB/HSB
	Color colori(0, 250, 181);
	Color col = colori; // Moving to another
	int value = col.red(); // Values assign to int like in processing
	printf("RGB: %d, %d, %d", col.red(), col.green(), col.blue());

	// Lerp color
	//Color newCol(0, 0, 0);
	//Color lerpedColor = lerpColor(col, newCol, .55f);
	//printf("RGB: %d, %d, %d", lerpedColor.red(), lerpedColor.green(), lerpedColor.blue());

	//background(255, 255, 255);

	//background("#AABBCC"); // Should hex code be like this
	//background(51.0f); // Grayscale
}


void draw(float) 
{

}

int main() 
{
	Application app(500, 300);
	return app.run(draw, setup);
}