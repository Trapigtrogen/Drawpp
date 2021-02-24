#ifndef DPP_GRAPHICS_H
#define DPP_GRAPHICS_H

#include <stack>
#include <matrix4.hpp>
#include <color.hpp>

class DImage;
class Shader;
class DVector;

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
    bool use_stroke = true;
    Color stroke_color = {0,0,0};
    float stroke_weight = 1.0f;
    bool use_tint = false;
    Color tint_color = {0,0,0};
    bool use_fill = true;
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

    void stroke(Color rgba);
    void stroke(Color rgb, float alpha);
    void stroke(float gray);
    void stroke(float gray, float alpha);

    //affected by colormode
    void stroke(float v1, float v2, float v3);
    void stroke(float v1, float v2, float v3, float alpha);

    ///\brief Change stroke width
    ///
    ///Will enable stroke if it is disabled.
    void strokeWeight(float w);

    void clear();

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

    void ellipse(float x, float y, float sizex, float sizey);
    void circle(float x, float y, float size);

    void rect(float x, float y, float sizex, float sizey);
    void rect(float x, float y, float sizex, float sizey, float radii);
    void rect(float x, float y, float sizex, float sizey, float tl, float tr, float br, float bl);
    void square(float x, float y, float size);

private:

    ///\brief Get the texture id for this graphics object
    unsigned int get_texture_id();

    Color get_rgba(float r, float g, float b, float a);
    Color get_hsba(float h, float s, float b, float a);
    Color get_color(float v1, float v2, float v3, float a);

    void set_current();

    void init_shaders();

    GraphicsProperties properties;

    //is this needed?
    //DMatrix4 transform_mat = DMatrix4::identity();

    DMatrix4 view_mat;

    unsigned int render_id = -1;
    unsigned int buffer_id = -1;
    unsigned int texture_id = -1;
    unsigned int buffer_width = 0;
    unsigned int buffer_height = 0;
    int type;
    int format;

    std::stack<DMatrix4> matrix_stack;
    std::stack<GraphicsProperties> property_stack;

    Shader* ellipse_shader = nullptr;

    int ellipse_shader_offset_loc;
    int ellipse_shader_strokeWeight_loc;
    int ellipse_shader_strokeColor_loc;
    int ellipse_shader_fillColor_loc;
    //int ellipse_shader_transform_loc;
    int ellipse_shader_view_loc;
    int ellipse_shader_vpos_loc;
    int ellipse_shader_tpos_loc;

    Shader* rect_shader = nullptr;

    int rect_shader_offset_loc;
    int rect_shader_strokeWeight_loc;
    int rect_shader_strokeColor_loc;
    int rect_shader_fillColor_loc;
    //int rect_shader_transform_loc;
    int rect_shader_view_loc;
    int rect_shader_radii_loc;
    int rect_shader_vpos_loc;
    int rect_shader_tpos_loc;

    //static unsigned int current_bound_buffer;
    //static unsigned int previous_bound_buffer;
};

#endif