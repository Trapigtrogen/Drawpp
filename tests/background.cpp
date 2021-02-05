#include <drawpp.hpp>

void setup()
{
	//colorMode(RGB); // DEBUG TODO
	Color colori(10, 0, 0); // Cannot do this in Processing but no point in artificially removing

	Color procCol = Color(0, 250, 181); // Processing style creating
	Color RGBCol = procCol; // Moving to another

	printf("\nRGB mode:\n");
	printf("RGB: %i, %i, %i\n", red(RGBCol), green(RGBCol), blue(RGBCol));
	printf("HSB: %f, %f, %f\n", hue(RGBCol), saturation(RGBCol), brightness(RGBCol));


	//ColorMode(HSB); // DEBUG TODO	
	Color HSBCol(163.4, 100, 250); // Same colour as RGB but in HSB values
	printf("\nHSB mode: (Color changin not done yet. These values are wrong)\n");
	printf("RGB: %i, %i, %i\n", red(HSBCol), green(HSBCol), blue(HSBCol));
	printf("HSB: %f, %f, %f\n\n", hue(HSBCol), saturation(HSBCol), brightness(HSBCol));

	// Lerp color
	Color lerpedColor = lerpColor(RGBCol, colori, 0.5);
	printf("lerped RGB: %i, %i, %i\n", red(lerpedColor), green(lerpedColor), blue(lerpedColor));


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