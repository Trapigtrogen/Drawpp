#ifndef DPP_COLOR_H
#define DPP_COLOR_H

#include <string>

/// Color API
class Color 
{
public:
    ///\brief Create an empty Color object
    ///
    /// Values can be loaded later from another one using operator=
    Color();

    ///\brief Create a Color object with \p v1, \p v2 and \p v3 and optional p alpha value
    ///
    /// values 1,2,3 are rgb/hsb depending on mode, aplha is non-transparent by default
    Color(float v1, float v2, float v3, float alpha = 255);

    ///\brief Create a Color object only one value
    Color(unsigned int);

    ///\brief Create a Color object using string containing the hex value
    ///
    /// Correct formats are #RGB, #RGBA, #RRGGBB and #RRGGBBAA and they must include the '#'
    Color(std::string hexCol);

    Color(const Color&) = default;
    Color& operator=(const Color& other);
    operator unsigned int () const;

    ///\brief Get Color's alpha value
    ///
    ///\returns \p alphaVal
    uint8_t alpha() const { return alphaVal; };

    ///\brief Get Color's red value
    ///
    ///\returns \p redVal
    uint8_t red() const { return redVal; };

    ///\brief Get Color's green value
    ///
    ///\returns \p greenVal
    uint8_t green() const { return greenVal; };

    ///\brief Get Color's blue value
    ///
    ///\returns \p blueaVal
    uint8_t blue() const { return blueVal; };

    ///\brief Get Color's hue value
    ///
    ///\returns \p hueVal
    float hue() const { return hueVal; };

    ///\brief Get Color's saturation value
    ///
    ///\returns \p saturationVal
    float saturation() const { return saturationVal; };

    ///\brief Get Color's brightness value
    ///
    ///\returns \p brightnessVal  brightnessVal
    float brightness() const { return brightnessVal; };

    ///\brief lerp color from two given colors
    /// 
    /// Lerps the color between two given colors by given percentage
    ///\returns New Color lerped between \p from and \p to Colors
    static Color lerpColor(const Color& from, const Color& to, float percentage);

    ///\brief Get the given Color's value converted to HEX format
    ///
    /// \p num tells if the result should include alpha and if there's one or two numbers per color value
    ///\returns Given Color's value as string containing the HEX
    static std::string hex(Color col, int num);


    ///\brief Convert color values from HEX to RGB format
    ///
    ///\returns New Color made from the given HEX color
    static Color HEX2RGB(char* hexCol);
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

    static int correctValue(int value, int min, int max);
};

#endif