#ifndef DPP_GRAPHICS_H
#define DPP_GRAPHICS_H

#include <vector3.hpp>
#include <matrix4.hpp>

class Image;

enum ColorMode
{
    RGB,
    HSB
};

struct GraphicsProperties
{
    //Color last_background_color;
    ColorMode colormode;
    float color_max1 = 255;
    float color_max2 = 255;
    float color_max3 = 255;
    float color_maxa = 255;
    bool use_stroke = false;
    //Color stroke_color;
    //int stroke_weight;
    bool use_tint = false;
    //Color tint_color;
    bool use_fill = false;
    //Color fill_color;

};

class DGraphics
{
    friend class Application;
public:

    ///\brief Create a DGraphics object with a \p width by \p height frame
    DGraphics(int width, int height);

    ///\brief Set this DGraphics object to be the current render target
    ///
    ///Always call beginDraw when you change the target DGraphics object. Not calling it will result in undefined behaviour.
    void beginDraw();

    ///\brief Explicitly end drawing to this buffer
    ///
    ///This does not need to be called if you call beginDraw() on another DGraphics object.
    void endDraw();

    //void fill(Color rgba);
    //void fill(Color rgb, float alpha);
    //void fill(float grey);
    //void fill(float grey, float alpha);

    //affected by colorMode
    //void fill(float v1, float v2, float v3);
    //void fill(float v1, float v2, float v3, float alpha);
    	
    //void background(Color rgba)
    //void background(Color rgb, float alpha)
    //void background(float gray)
    //void background(float gray, float alpha)
    //void background(const Image* image)
    //void background(const Image& image)

    //affected by colorMode
    //void background(float v1, float v2, float v3)
    //void background(float v1, float v2, float v3, float alpha)

    //void clear();

    void colorMode(ColorMode mode);
    void colorMode(ColorMode mode, float max);
    void colorMode(ColorMode mode, float max1, float max2, float max3);
    void colorMode(ColorMode mode, float max1, float max2, float max3, float maxA);


    //void tint(Color rgba);
    //void tint(Color rgb, float alpha);
    //void tint(float grey);
    //void tint(float grey, float alpha);

    //affected by colorMode
    //void tint(float v1, float v2, float v3);
    //void tint(float v1, float v2, float v3, float alpha);

    void noFill();

    void noStroke();

    void noTint();

    void translate(float x, float y);
    void translate(float x, float y, float z);
    void translate(const DVector& t);

    void rotate(float angle);

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    	
    void scale(float s);
    void scale(float x, float y);
    void scale(float x, float y, float z);
    void scale(const DVector& s);

private:

    ///\brief Get the texture id for this graphics object
    unsigned int get_texture_id();

    void set_current();

    GraphicsProperties properties;
    DMatrix4 transform_mat = DMatrix4::identity();

    unsigned int buffer_id = -1;
    unsigned int texture_id = -1;
    unsigned int buffer_width = 0;
    unsigned int buffer_height = 0;

    //static unsigned int current_bound_buffer;
    //static unsigned int previous_bound_buffer;
};

#endif