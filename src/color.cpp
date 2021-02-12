#include <color.hpp>
#include <application.hpp>

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

Color::Color(float v1, float v2, float v3, float a)
{
	//if(Application::GetInstance()->graphics.ColorMode == RGB) // DEBUG TODO: RGB/HSB Mode change
	int mode = 0; // DEBUG TEMP
	if(mode == 0)
	{
		redVal = v1;
		greenVal = v2;
		blueVal = v3;
		RGB2HSB(v1, v2, v3);
	}
	else 
	{
		hueVal = v1;
		saturationVal = v2;
		brightnessVal = v3;
		HSB2RGB(v1, v2, v3);
	}
		alphaVal = a;
}

Color& Color::operator=(Color& other) 
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

void Color::RGB2HSB(uint8_t r, uint8_t g, uint8_t b)
{
	double themin, themax, delta;
	float hue, saturation, brightness;

	themin = std::min(r, std::min(g, b));
	themax = std::max(r, std::max(g, b));
	delta = themax - themin;
	brightness = themax;
	saturation = 0;
	if(themax > 0)
		saturation = delta / themax;
	hue = 0;
	if(delta > 0) {
		if(themax == r && themax != g)
			hue += (g - b) / delta;
		if(themax == g && themax != b)
			hue += (2 + (b - r) / delta);
		if(themax == b && themax != r)
			hue += (4 + (r - g) / delta);
		hue *= 60;
	}

	hueVal = hue;
	saturationVal = saturation * 100; // to make it percentages
	brightnessVal = brightness;
}

void Color::HSB2RGB(float h, float s, float b)
{
	double hh, p, q, t, ff;
	long i;
	uint8_t red, green, blue;

	float ss = s / 100; // percentages to 0-1

	if(ss <= 0.0)  // < is bogus, just shuts up warnings
	{
		redVal = b;
		greenVal = b;
		blueVal = b;
		return;
	}
	hh = h;
	if(hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = b * (1.0 - ss);
	q = b * (1.0 - (ss * ff));
	t = b * (1.0 - (ss * (1.0 - ff)));

	switch(i) {
		case 0:
		red = b;
		green = t;
		blue = p;
		break;
		case 1:
		red = q;
		green = b;
		blue = p;
		break;
		case 2:
		red = p;
		green = b;
		blue = t;
		break;

		case 3:
		red = p;
		green = q;
		blue = b;
		break;
		case 4:
		red = t;
		green = p;
		blue = b;
		break;
		case 5:
		default:
		red = b;
		green = p;
		blue = q;
		break;
	}

	redVal = red;
	greenVal = green;
	blueVal = blue;
}