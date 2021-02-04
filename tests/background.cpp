#include <drawpp.hpp>

void setup()
{
	//colorMode(RGB); // How to make RGB/HSB
	Color colori(20, 250, 181);
	Color col = colori; // Moving to another
	int value = col.red(); // Values assign to int like in processing
	printf("RGB: %d, %d, %d\n", col.red(), col.green(), col.blue());

	// Lerp color
	Color newCol(10, 0, 0);
	Color lerpedColor = lerpColor(col, newCol, 0.5f);
	printf("lerped RGB: %d, %d, %d\n", lerpedColor.red(), lerpedColor.green(), lerpedColor.blue());

	background(255, 255, 255);

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