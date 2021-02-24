#include <color.hpp>
#include <application.hpp>
#include <graphics.hpp>
#include <sstream>

Color::Color() 
{
	alphaVal = 255;
	redVal = 255;
	greenVal = 255;
	blueVal = 255;
	hueVal = 0;
	saturationVal = 100;
	brightnessVal = 100;
}

Color::Color(float v1, float v2, float v3, float a)
{
	// Use RGB mode when the graphics do not exist yet
	// This is to prevent crashing
	if(!Application::GetInstance()->graphicsExists())
	{
		redVal = v1;
		greenVal = v2;
		blueVal = v3;
		RGB2HSB(v1, v2, v3);
	}
	else if(Application::GetInstance()->graphics_object().getStyle().colormode == RGB)
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

Color::Color(unsigned int c)
{
    alphaVal = c >> 24;
    redVal = (c & 0x00FF0000) >> 16;
    greenVal = (c & 0x0000FF00) >> 8;
    blueVal = c & 0x000000FF;
    RGB2HSB(redVal,greenVal,blueVal);
}

Color::Color(std::string hexCol) 
{
	Color temp = HEX2RGB((char*)hexCol.c_str());
	redVal = temp.red();
	greenVal = temp.green();
	blueVal = temp.blue();
	alphaVal = temp.alpha();
	hueVal = temp.hue();
	saturationVal = temp.saturation();
	brightnessVal = temp.brightness();
}

Color& Color::operator=(const Color& other) 
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

Color::operator unsigned int () const
{
    return ((alphaVal << 24) | (redVal << 16) | (greenVal << 8) | blueVal);
}

Color Color::lerpColor(const Color& from, const Color& to, float percentage) 
{
	// Ensure that the values are in the range
	if(percentage > 1) percentage = 1.0;
	if(percentage < 0) percentage = 0.0;

	// Lerp values
	uint8_t lerpRed = from.redVal + percentage * (to.redVal - from.redVal);
	uint8_t lerpGreen = from.greenVal + percentage * (to.greenVal - from.greenVal);
	uint8_t lerpBlue = from.blueVal + percentage * (to.blueVal - from.blueVal);
    uint8_t lerpAlpha = from.alphaVal + percentage * (to.alphaVal - from.alphaVal);

	return Color(lerpRed,lerpGreen,lerpBlue,lerpAlpha);
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

Color Color::HEX2RGB(char* hexCol) 
{
	bool valid = false;
	int r, g, b;
	int a = 255;

	// Is right format
	if(hexCol[0] == '#')
	{
		// remove '#' from color string
		char* hexNum = hexCol + 1;

		switch(strlen(hexNum)) 
		{
			// Full hex with alpha
			case 8: 
				sscanf(hexNum, "%02x%02x%02x%02x", &r, &g, &b, &a);
				valid = true;
			break;

			// Full hex without alpha
			case 6: 
				sscanf(hexNum, "%02x%02x%02x", &r, &g, &b);
				valid = true;
			break;

			// Compact hex with alpha
			case 4: 
				sscanf(hexNum, "%01x%01x%01x%01x", &r, &g, &b, &a);
				r *= 10;
				g *= 10;
				b *= 10;
				a *= 10;
				valid = true;
			break;

			// Compact hex without alpha
			case 3: 
				sscanf(hexNum, "%01x%01x%01x", &r, &g, &b);
				r *= 10;
				g *= 10;
				b *= 10;
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

std::string Color::hex(Color col, int num)
{
	uint8_t r = col.red();
	uint8_t g = col.green();
	uint8_t b = col.blue();
	uint8_t a = col.alpha();
	char buffer[33]; // temp buffer
	std::string result = "#"; // final result


	printf("Debug originals : %i, %i, %i, %i\n", r, g, b, a);

	switch(num)
	{
		case 3: // Shrink values to fit compact mode
		_itoa_s(r, buffer, 16);
		result += buffer[0];		
		_itoa_s(g, buffer, 16);
		result += buffer[0];
		_itoa_s(b, buffer, 16);
		result += buffer[0];
		break;

		case 4: // Shrink values to fit compact mode
		_itoa_s(r, buffer, 16);
		result += buffer[0];
		_itoa_s(g, buffer, 16);
		result += buffer[0];
		_itoa_s(b, buffer, 16);
		result += buffer[0];
		_itoa_s(a, buffer, 16);
		result += buffer[0];
		break;

		case 6:
		_itoa_s(r, buffer, 16);
		result += buffer;
		_itoa_s(g, buffer, 16);
		result += buffer;
		_itoa_s(b, buffer, 16);
		result += buffer;
		break;

		case 8:
		_itoa_s(r, buffer, 16);
		result += buffer;
		_itoa_s(g, buffer, 16);
		result += buffer;
		_itoa_s(b, buffer, 16);
		result += buffer;
		_itoa_s(a, buffer, 16);
		result += buffer;
		break;

		default:
		dbg::error("Invalid number");
		break;
	}

	_itoa_s(col.red(), buffer, 16);

	// Convert to upper case for fanciness points
	std::transform(result.begin(), result.end(), result.begin(), [] (unsigned char c) { return std::toupper(c); });
	return  result;
}

int Color::correctValue(int value, int min, int max)
{
	if(value < min) value = min;
	if(value > max) value = max;
	return value;
}