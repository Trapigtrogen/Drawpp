#ifndef DPP_COLOR_H
#define DPP_COLOR_H

#include <string>
#include <debug.hpp>

/// Color API
class Color 
{
public:
    Color();
    // values 1,2,3 are rgb/hsb depending on mode
    Color(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t a = 255);
    Color(const Color& other);
    Color(Color&& other);

    Color& operator=(Color&& other);

    uint8_t alpha() { return alphaVal; };
    uint8_t red() { return redVal; };
    uint8_t green() { return greenVal; };
    uint8_t blue() { return blueVal; };
    uint8_t hue() { return hueVal; };
    uint8_t saturation() { return saturationVal; };
    uint8_t brightness() { return brightnessVal; };

    static Color lerpColor(Color* from, Color* to, float percentage);

private:
    uint8_t alphaVal;
    uint8_t redVal;
    uint8_t greenVal;
    uint8_t blueVal;
    uint8_t hueVal;
    uint8_t saturationVal;
    uint8_t brightnessVal;
};

#endif