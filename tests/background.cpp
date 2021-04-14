#include <drawpp.hpp>

void setup()
{
	colorMode(RGB);
	Color colori(10, 0, 0); // Cannot do this in Processing but no point in artificially removing

	Color procCol = Color(0, 250, 181); // Processing style creating
	Color RGBCol = procCol; // Copying to another

	printf("\nRGB mode:\n");
	printf("RGB: %f, %f, %f\n", red(RGBCol), green(RGBCol), blue(RGBCol));
	printf("HSB: %f, %f, %f\n", hue(RGBCol), saturation(RGBCol), brightness(RGBCol));

	colorMode(HSB);
	Color HSBCol(163.4, 100, 250); // Same color as RGB but in HSB values
	printf("\nHSB mode:\n");
	printf("RGB: %f, %f, %f\n", red(HSBCol), green(HSBCol), blue(HSBCol));
	printf("HSB: %f, %f, %f\n\n", hue(HSBCol), saturation(HSBCol), brightness(HSBCol));

	colorMode(HSB);
	// Lerp color
	Color lerpedColor = lerpColor(RGBCol, colori, 0.5);
	printf("lerped RGB: %f, %f, %f\n", red(lerpedColor), green(lerpedColor), blue(lerpedColor));

	colorMode(RGB);

	background(255, 100, 100);
	background(51); // RGB
	background(51.0f); // Grayscale


	// Hex not case sensitive
	Color hexCol("#00FAB5");
	background(hexCol); // full hex color used from object
	
	background("#1f5"); // compact hex color
	background("#10f050"); // full hex color
	background("#1f5f"); // compact hex color with alpha
	background("#10f050ff"); // full hex color with alpha
	// Invalid hex colors i.e. "#RAY" give random results (usually white) but won't break the program

	// Not implemented
	//background("blue"); // color by name

	// Print Color as HEX
	Color hextest(250, 0, 181);
	printf( "\n\nHex values from %f, %f, %f:\n", red(hextest), green(hextest), blue(hextest) );
	printf("HEX3: %s\n", hex(hextest, 3).c_str());
	printf("HEX4: %s\n", hex(hextest, 4).c_str());
	printf("HEX6: %s\n", hex(hextest, 6).c_str());
	printf("HEX8: %s\n", hex(hextest, 8).c_str());
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