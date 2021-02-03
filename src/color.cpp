#include <color.hpp>

Color::Color() 
{
	alphaVal = 255;
	redVal = 255;
	greenVal = 255;
	blueVal = 255;
	hueVal = 255;
	saturationVal = 255;
	brightnessVal = 255;
}

Color::Color(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t a) 
{
	hueVal = v1; // DEBUG TEMP
	saturationVal = v2; // DEBUG TEMP
	brightnessVal = v3; // DEBUG TEMP

	// if(mode==rgb) // DEBUG TODO: RGB/HSB Mode change
	//{
		redVal = v1;
		greenVal = v2;
		blueVal = v3;
	//}
	//else 
	//{
		//hueVal = v1;
		//saturationVal = v2;
		//brightnessVal = v3;
	//}
		alphaVal = a;
}

Color::Color(const Color& other)
{
	alphaVal = other.alphaVal;
	redVal = other.redVal;
	greenVal = other.greenVal;
	blueVal = other.blueVal;
	hueVal = other.hueVal;
	saturationVal = other.saturationVal;
	brightnessVal = other.brightnessVal;
}

Color::Color(Color&& other)
{
	alphaVal = other.alphaVal;
	redVal = other.redVal;
	greenVal = other.greenVal;
	blueVal = other.blueVal;
	hueVal = other.hueVal;
	saturationVal = other.saturationVal;
	brightnessVal = other.brightnessVal;
}

Color& Color::operator=(Color&& other) 
{
	if(this != &other)
	{
		alphaVal = other.alphaVal;
		redVal = other.redVal;
		greenVal = other.greenVal;
		blueVal = other.blueVal;
		hueVal = other.hueVal;
		saturationVal = other.saturationVal;
		brightnessVal = other.brightnessVal;
	}

	return *this;
}

Color Color::lerpColor(Color* from, Color* to, float percentage) 
{
	// Ensure that the values are in the range
	if(percentage > 1) percentage = 1.0;
	if(percentage < 0) percentage = 0.0;

	// Lerp values
	uint8_t lerpRed = from->red() + percentage * (to->red() - from->red());
	uint8_t lerpGreen = from->green() + percentage * (to->green() - from->green());
	uint8_t lerpBlue = from->blue() + percentage * (to->blue() - from->blue());
	uint8_t lerpHue = from->hue() + percentage * (to->hue() - from->hue());
	uint8_t lerpSaturation = from->saturation() + percentage * (to->saturation() - from->saturation());
	uint8_t lerpBrightness = from->brightness() + percentage * (to->brightness() - from->brightness());

	Color tmpColor;
	tmpColor.redVal = lerpRed;
	tmpColor.greenVal = lerpGreen;
	tmpColor.blueVal = lerpBlue;
	tmpColor.hueVal = lerpHue;
	tmpColor.saturationVal = lerpSaturation;
	tmpColor.brightnessVal = lerpBrightness;

	return tmpColor;
}