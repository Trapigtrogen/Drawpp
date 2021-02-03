#include <color.hpp>

Color::Color(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t a) 
{
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

/*
Color Color::lerpColor(Color* from, Color* to, float percentage) 
{
	// Ensure that the values are in the range
	if(percentage > 1.0) percentage = 1.0f;
	if(percentage < 0.0) percentage = 0.0f;

	// Lerp values
	uint8_t lerpRed = 0;
	uint8_t lerpBlue = 0;
	uint8_t lerpGreen = 0;
	uint8_t lerpHue = 0;
	uint8_t lerpSaturation = 0;
	uint8_t lerpBrightness = 0;

	Color tmpColor;
	tmpColor.redVal = lerpRed;
	tmpColor.greenVal = lerpBlue;
	tmpColor.blueVal = lerpGreen;
	tmpColor.hueVal = lerpHue;
	tmpColor.saturationVal = lerpSaturation;
	tmpColor.brightnessVal = lerpBrightness;

	return tmpColor;
}
*/