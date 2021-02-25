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
	// Print as HEX
	printf("HEX: %s\n", hex(lerpedColor, 3).c_str());
	printf("HEX: %s\n", hex(lerpedColor, 4).c_str());
	printf("HEX: %s\n", hex(lerpedColor, 6).c_str());
	printf("HEX: %s\n", hex(lerpedColor, 8).c_str());

	colorMode(RGB);

	background(255, 100, 100);
	background(51); // RGB
	background(51.0f); // Grayscale

	// Hex not case sensitive
	Color hexCol("#00FAB5");
	background(hexCol); // full hex color used from object
	background("#1f5"); // compact hex color
	// Invalid hex colors i.e. "#RAY" give random results (usually white) but won't break the program

	// Not implemented
	//background("blue"); // color by name
}


void draw(float) 
{
	background(randomInt(255),randomInt(255),randomInt(255));
}

int main() 
{
	Application app(500, 300);
	return app.run(draw, setup);
}