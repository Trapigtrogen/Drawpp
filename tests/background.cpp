#include <drawpp.hpp>

void setup()
{
	colorMode(RGB);
	Color colori(10, 0, 0); // Cannot do this in Processing but no point in artificially removing

	Color procCol = Color(0, 250, 181); // Processing style creating
	Color RGBCol = procCol; // Moving to another

	printf("\nRGB mode:\n");
	printf("RGB: %f, %f, %f\n", red(RGBCol), green(RGBCol), blue(RGBCol));
	printf("HSB: %f, %f, %f\n", hue(RGBCol), saturation(RGBCol), brightness(RGBCol));


	colorMode(HSB);
	Color HSBCol(163.4, 100, 250); // Same colour as RGB but in HSB values
	printf("\nHSB mode:\n");
	printf("RGB: %f, %f, %f\n", red(HSBCol), green(HSBCol), blue(HSBCol));
	printf("HSB: %f, %f, %f\n\n", hue(HSBCol), saturation(HSBCol), brightness(HSBCol));

	// Lerp color
	Color lerpedColor = lerpColor(RGBCol, colori, 0.5);
	printf("lerped RGB: %f, %f, %f\n", red(lerpedColor), green(lerpedColor), blue(lerpedColor));


	background(255, 255, 255);
	//background(51); // RGB
	//background(51.0f); // Grayscale

	// Not implemented
	//background("#AABBCC"); // Should hex code be like this
	//background("blue"); // color name
}


void draw(float) 
{

}

int main() 
{
	Application app(500, 300);
	return app.run(draw, setup);
}