#ifndef DPP_COLOR_H
#define DPP_COLOR_H

#include <string>

/// Color API
class Color 
{
public:
    Color();
    // values 1,2,3 are rgb/hsb depending on mode
    Color(float v1, float v2, float v3, float a = 255);
    Color(unsigned int);
    Color(const Color&) = default;

    Color& operator=(const Color& other);

    operator unsigned int () const;

    uint8_t alpha() const { return alphaVal; };
    uint8_t red() const { return redVal; };
    uint8_t green() const { return greenVal; };
    uint8_t blue() const { return blueVal; };
    float hue() const { return hueVal; };
    float saturation() const { return saturationVal; };
    float brightness() const { return brightnessVal; };

    static Color lerpColor(const Color& from, const Color& to, float percentage);

private:
    uint8_t alphaVal;
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