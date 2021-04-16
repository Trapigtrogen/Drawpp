#ifndef DPP_COLOR_H
#define DPP_COLOR_H

#include <hsbcolor.hpp>
#include <string>

class HSBColor;

/// Color API
class Color 
{
    friend class DGraphics;
    friend class HSBColor;
public:

    ///\brief Create an empty Color object
    ///
    /// Values can be loaded later from another one using operator=
    Color();


    ///\brief Create a Color object from a HSBColor object
    Color(const HSBColor& c);


    ///\brief Create a Color object with \p v1, \p v2 and \p v3 and optional p alpha value
    ///
    /// values 1,2,3 are rgb/hsb depending on mode, aplha is non-transparent by default
    Color(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t alpha = 255);


    ///\brief Create a Color object only one value
    Color(unsigned int);


    ///\brief Create a Color object using string containing the hex value
    ///
    /// Correct formats are \#RGB, \#RGBA, \#RRGGBB and \#RRGGBBAA and they must include the '#'
    Color(const std::string& hexCol);


    Color(const Color&) = default;
    Color& operator=(const Color& other) = default;


    ///\brief Convert from HSBColor to Color
    Color& operator=(const HSBColor& other);


    ///\brief Convert to unsigned int
    operator unsigned int () const;


    ///\brief Convert Color to HSBColor
    HSBColor hsb() const;


    ///\brief lerp color from two given colors
    /// 
    /// Lerps the color between two given colors by given percentage
    ///\returns New Color lerped between \p from and \p to Colors
    static Color lerpColor(const Color& from, const Color& to, float percentage);


    ///\brief Get the given Color's value converted to HEX format
    ///
    /// \p num tells if the result should include alpha and if there's one or two numbers per color value
    ///\returns Given Color's value as string containing the HEX
    static std::string hex(const Color& col, int num = 8);


    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

private:
    
    void HSB2RGB(float h, float s, float b, float a);

    static Color HEX2RGB(const char* hexCol);
    static char* DItoa(int val, int base);
    static int correctValue(int value, int min, int max);
};


#endif