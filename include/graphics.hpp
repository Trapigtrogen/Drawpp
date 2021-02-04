#ifndef DPP_GRAPHICS_H
#define DPP_GRAPHICS_H

#include <stack>
#include <vector3.hpp>
#include <matrix4.hpp>
#include <color.hpp>

class DImage;

enum ColorMode
{
    RGB,
    HSB
};

struct GraphicsProperties
{
    Color last_background_color = {0,0,0};
    ColorMode colormode = ColorMode::RGB;
    float color_max1 = 255;
    float color_max2 = 255;
    float color_max3 = 255;
    float color_maxa = 255;
    bool use_stroke = false;
    Color stroke_color = {0,0,0};
    int stroke_weight;
    bool use_tint = false;
    Color tint_color = {0,0,0};
    bool use_fill = false;
    Color fill_color = {255,255,255};

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

    void fill(Color rgba);
    void fill(Color rgb, float alpha);
    void fill(float grey);
    void fill(float grey, float alpha);

    //affected by colorMode
    void fill(float v1, float v2, float v3);
    void fill(float v1, float v2, float v3, float alpha);
    	
    void background(Color rgba);
    void background(Color rgb, float alpha);
    void background(float gray);
    void background(float gray, float alpha);
    //void background(const Image* image)
    //void background(const Image& image)

    //affected by colorMode
    void background(float v1, float v2, float v3);
    void background(float v1, float v2, float v3, float alpha);

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


    Color color(float grey);
    Color color(float grey, float alpha);

    //affected by colorMode
    Color color(float v1, float v2, float v3);
    Color color(float v1, float v2, float v3, float alpha);

    float red(Color c);
    float green(Color c);
    float blue(Color c);
    float alpha(Color c);
    float saturation(Color c);
    float hue(Color c);
    float brightness(Color c);

    //void image(DImage* img, float x, float y);
    //void image(DImage* img, float x, float y, float w, float h);

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

    void push();
    void pop();

    void pushMatrix();
    void popMatrix();

    void pushStyle();
    void popStyle();

private:

    ///\brief Get the texture id for this graphics object
    unsigned int get_texture_id();

    Color get_rgba(float r, float g, float b, float a);
    Color get_hsba(float h, float s, float b, float a);
    Color get_color(float v1, float v2, float v3, float a);

    void set_current();

    GraphicsProperties properties;
    DMatrix4 transform_mat = DMatrix4::identity();

    unsigned int buffer_id = -1;
    unsigned int texture_id = -1;
    unsigned int buffer_width = 0;
    unsigned int buffer_height = 0;

    std::stack<DMatrix4> matrix_stack;
    std::stack<GraphicsProperties> property_stack;

    //static unsigned int current_bound_buffer;
    //static unsigned int previous_bound_buffer;
};

#endif