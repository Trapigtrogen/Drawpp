#include <color.hpp>
#include <hsbcolor.hpp>
//#include <application.hpp>
#include <debug.hpp>
#include <algorithm>
//#include <graphics.hpp>
#include <cstring>

Color::Color() 
{
	alpha = 255;
	red = 255;
	green = 255;
	blue = 255;
}

Color::Color(const HSBColor& c)
{
    HSB2RGB(c.hue,c.saturation,c.brightness,c.alpha);
}

Color::Color(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t a)
{
    red = v1;
    green = v2;
    blue = v3;
	alpha = a;
}

Color::Color(unsigned int c)
{
    alpha = c >> 24;
    red = (c & 0x00FF0000) >> 16;
    green = (c & 0x0000FF00) >> 8;
    blue = c & 0x000000FF;
}

Color::Color(const std::string& hexCol) 
{
	*this = HEX2RGB(hexCol.c_str());
}

Color::operator unsigned int () const
{
    return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}   

Color& Color::operator=(const HSBColor& other)
{
    return *this = Color(other);
}

HSBColor Color::hsb() const
{
    return HSBColor(*this);
}

Color Color::lerpColor(const Color& from, const Color& to, float percentage) 
{
	// Ensure that the values are in the range
	if(percentage > 1) percentage = 1.0;
	if(percentage < 0) percentage = 0.0;

	// Lerp values
	uint8_t lerpRed = from.red + percentage * (to.red - from.red);
	uint8_t lerpGreen = from.green + percentage * (to.green - from.green);
	uint8_t lerpBlue = from.blue + percentage * (to.blue - from.blue);
    uint8_t lerpAlpha = from.alpha + percentage * (to.alpha - from.alpha);
	return Color(lerpRed,lerpGreen,lerpBlue,lerpAlpha);
}

void Color::HSB2RGB(float h, float s, float b, float a)
{
	float hh, p, q, t, ff;
	float r, g, bb;
	long i;

	float ss = s / 100; // percentages to 0-1

	
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
		r = b;
		g = t;
		bb = p;
		break;
		case 1:
		r = q;
		g = b;
		bb = p;
		break;
		case 2:
		r = p;
		g = b;
		bb = t;
		break;

		case 3:
		r = p;
		g = q;
		bb = b;
		break;
		case 4:
		r = t;
		g = p;
		bb = b;
		break;
		case 5:
		default:
		r = b;
		g = p;
		bb = q;
		break;
	}

    red   =  r * 2.551;
    green =  g * 2.551;
    blue  = bb * 2.551;
    alpha =  a * 2.551;
}

Color Color::HEX2RGB(const char* hexCol)
{
	bool valid = false;
	int r, g, b;
	int a = 255;

	// Is right format
	if(hexCol[0] == '#')
	{
		// remove '#' from color string
		//hexCol.erase(0, 1);
        ++hexCol;
		//char* hexNum = new char;
		//strcpy(hexNum, hexCol);
        
        //switch(hexCol.size())
		switch(strlen(hexCol))
		{
			// Full hex with alpha
			case 8:
				sscanf(hexCol, "%02x%02x%02x%02x", &r, &g, &b, &a);
				valid = true;
			break;

			// Full hex without alpha
			case 6: 
				sscanf(hexCol, "%02x%02x%02x", &r, &g, &b);
				valid = true;
			break;

			// Compact hex with alpha
			case 4: 
				sscanf(hexCol, "%01x%01x%01x%01x", &r, &g, &b, &a);
				r *= 25;
				g *= 25;
				b *= 25;
				a *= 25;
				valid = true;
			break;

			// Compact hex without alpha
			case 3: 
				sscanf(hexCol, "%01x%01x%01x", &r, &g, &b);
				r *= 25;
				g *= 25;
				b *= 25;
				valid = true;
			break;

			// Invalid
			default:
			break;
		}
	}

	if(valid)
	{
		r = correctValue(r, 0, 255);
		g = correctValue(g, 0, 255);
		b = correctValue(b, 0, 255);
		a = correctValue(a, 0, 255);
		return Color(r, g, b, a);
	}

	dbg::error("Not a hex color. Should be \"#RRGGBB\", \"#RRGGBBAA\" or compact variant of either");
	return Color(0);
}

std::string Color::hex(const Color& col, int num)
{
	uint8_t r = col.red;
	uint8_t g = col.green;
	uint8_t b = col.blue;
	uint8_t a = col.alpha;

	std::string result = "#"; // final result

	switch(num)
	{
		case 3: // Shrink values to fit compact mode
		result += DItoa(r, 16)[0];
		result += DItoa(g, 16)[0];
		result += DItoa(b, 16)[0];
		break;

		case 4: // Shrink values to fit compact mode
		result += DItoa(r, 16)[0];
		result += DItoa(g, 16)[0];
		result += DItoa(b, 16)[0];
		result += DItoa(a, 16)[0];
		break;

		case 6:
		result += DItoa(r, 16);
		result += DItoa(g, 16);
		result += DItoa(b, 16);
		break;

		case 8:
		result += DItoa(r, 16);
		result += DItoa(g, 16);
		result += DItoa(b, 16);
		result += DItoa(a, 16);
		break;

		default:
		dbg::error("Invalid number");
		break;
	}

	// Convert to upper case for fanciness points
	std::transform(result.begin(), 
                   result.end(), 
                   result.begin(), 
                   [] (unsigned char c) 
                    { 
                       return std::toupper(c); 
                    });
	return  result;
}

int Color::correctValue(int value, int min, int max)
{
	if(value < min) value = min;
	if(value > max) value = max;
	return value;
}

char* Color::DItoa(int val, int base)
{
	static char buf[32] = {0};

	if(val == 0) // if value is 0 no need to do any work
	{ 
		static char result[3] = "00";
		return result;
	}

	int i = 30;
	for(; val && i; --i, val /= base)
	{
		buf[i] = "0123456789abcdef"[val % base];
	}
	return &buf[i + 1];
}


HSBColor::HSBColor() 
{
	hue = 0;
	saturation = 100;
	brightness = 100;
    alpha = 100;
}

HSBColor::HSBColor(const Color& c)
{
    RGB2HSB(c.red,c.green,c.blue,c.alpha);
}

HSBColor::HSBColor(float v1, float v2, float v3, float a)
{
    hue = v1;
    saturation = v2;
    brightness = v3;
	alpha = a;
}

HSBColor::HSBColor(const std::string& hexCol) 
{
	*this = Color::HEX2RGB(hexCol.c_str());
}

HSBColor::operator unsigned int () const
{
    return rgb();
}

HSBColor& HSBColor::operator=(const Color& other)
{
    return *this = HSBColor(other);
}

Color HSBColor::rgb() const
{
    return Color(*this);
}

HSBColor HSBColor::lerpColor(const HSBColor& from, const HSBColor& to, float percentage)
{
    // Ensure that the values are in the range
	if(percentage > 1) percentage = 1.0;
	if(percentage < 0) percentage = 0.0;

	// Lerp values
	float lerpHue = from.hue + percentage * (to.hue - from.hue);
	float lerpSat = from.saturation + percentage * (to.saturation - from.saturation);
	float lerpBr = from.brightness + percentage * (to.brightness - from.brightness);
    float lerpAlpha = from.alpha + percentage * (to.alpha - from.alpha);
	return HSBColor(lerpHue,lerpSat,lerpBr,lerpAlpha);
}

std::string hex(const HSBColor& col, int num)
{
    return Color::hex(col,num);
}

void HSBColor::RGB2HSB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	float themin, themax, delta;

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

	hue = hue;
	saturation = saturation * 100.0f; // to make it percentages
	brightness = brightness/2.55f;
    alpha = a / 2.55f;
}