#ifndef DPP_COLOR_H
#define DPP_COLOR_H

#include <string>
#include <debug.hpp>
#include <algorithm>

/// Color API
class Color 
{
public:
    Color();
    // values 1,2,3 are rgb/hsb depending on mode
    Color(float v1, float v2, float v3, float a = 255);
    Color(const Color&) = default;

    Color& operator=(Color& other);

    float alpha() { return alphaVal; };
    uint8_t red() { return redVal; };
    uint8_t green() { return greenVal; };
    uint8_t blue() { return blueVal; };
    float hue() { return hueVal; };
    float saturation() { return saturationVal; };
    float brightness() { return brightnessVal; };

    static Color lerpColor(Color* from, Color* to, float percentage);

private:
    float alphaVal;
    uint8_t redVal;
    uint8_t greenVal;
    uint8_t blueVal;
    float hueVal;
    float saturationVal;
    float brightnessVal;

    void RGB2HSB(uint8_t r, uint8_t g, uint8_t b);
    void HSB2RGB(float h, float s, float b);
};

#endif