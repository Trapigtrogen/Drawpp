#ifndef DPP_HSBCOLOR_H
#define DPP_HSBCOLOR_H

#include <color.hpp>
#include <stdint.h>
#include <string>

class Color;
class HSBColor
{
    friend class Color;
public:

    ///\brief Create an empty Color object
    ///
    ///Default color is opaque white
    HSBColor();


    ///\brief Create a HSBColor object from a Color object
    HSBColor(const Color& c);


    ///\brief Create a Color object with \p h, \p s and \p b and optional p alpha value
    ///
    ///Alpha is non-transparent by default
    HSBColor(float h, float s, float b, float alpha = 1.0);


    ///\brief Create a Color object using string containing the hex value
    ///
    ///Correct formats are \#RGB, \#RGBA, \#RRGGBB and \#RRGGBBAA and they must include the '#'
    HSBColor(const std::string& hexCol);


    HSBColor(const HSBColor&) = default;
    HSBColor& operator=(const HSBColor& other) = default;


    ///\brief Convert from Color to HSBColor
    HSBColor& operator=(const Color& other);


    ///\brief Convert to unsigned int
    operator unsigned int () const;


    ///\brief Convert HSBColor to Color
    Color rgb() const;


    ///\copydoc Color::lerpColor(const Color&,const Color&,float)
    static HSBColor lerpColor(const HSBColor& from, const HSBColor& to, float percentage);  


    ///\copydoc Color::hex(const Color&,int)
    static std::string hex(const HSBColor& col, int num = 8);

    float hue = 0;
    float saturation = 0;
    float brightness = 100;
    float alpha = 100;

private:

    void RGB2HSB(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
};


#endif