#include <drawpp.hpp>

void setup()
{
	colorMode(RGB);
	Color colori(10, 0, 0); // Cannot do this in Processing but no point in artificially removing

	Color procCol = color(0, 250, 181); // Processing style creating
	Color RGBCol = procCol; // Copying to another
	HSBColor RGBCol_hsb = RGBCol;

	printf("\nRGB mode:\n");
	printf("RGB: %d, %d, %d\n", RGBCol.red, RGBCol.green, RGBCol.blue);
	printf("HSB: %f, %f, %f\n", RGBCol_hsb.hue, RGBCol_hsb.saturation, RGBCol_hsb.brightness);

	colorMode(HSB,360,100,100);
	Color HSBCol = color(163.4, 100, 98); // Same color as RGB but in HSB values
	HSBColor HSBCol_hsb = HSBCol;

	printf("\nHSB mode:\n");
	printf("RGB: %d, %d, %d\n", HSBCol.red, HSBCol.green, HSBCol.blue);
	printf("HSB: %f, %f, %f\n", HSBCol_hsb.hue, HSBCol_hsb.saturation, HSBCol_hsb.brightness);

	// Lerp color
	Color lerpedColor = lerpColor(RGBCol, colori, 0.5);
	printf("lerped RGB: %d, %d, %d\n", lerpedColor.red, lerpedColor.green, lerpedColor.blue);

	colorMode(RGB,255,255,255);

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