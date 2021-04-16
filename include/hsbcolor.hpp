#ifndef DPP_HSBCOLOR_H
#define DPP_HSBCOLOR_H

#include <color.hpp>
#include <string>

class Color;
class HSBColor
{
    friend class Color;
public:

    ///\brief Create an empty Color object
    ///
    /// Values can be loaded later from another one using operator=
    HSBColor();


    ///\brief Create a HSBColor object from a Color object
    HSBColor(const Color& c);


    ///\brief Create a Color object with \p v1, \p v2 and \p v3 and optional p alpha value
    ///
    /// values 1,2,3 are rgb/hsb depending on mode, aplha is non-transparent by default
    HSBColor(float v1, float v2, float v3, float alpha = 1.0);


    ///\brief Create a Color object using string containing the hex value
    ///
    /// Correct formats are \#RGB, \#RGBA, \#RRGGBB and \#RRGGBBAA and they must include the '#'
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

    float hue;
    float saturation;
    float brightness;
    float alpha;

private:

    void RGB2HSB(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
};


#endif