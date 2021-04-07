#ifndef DPP_GRAPHICS_H
#define DPP_GRAPHICS_H

#include <stack>
#include <string>
#include <matrix4.hpp>
#include <color.hpp>
#include <font.hpp>
#include <memory>

class DImage;
class Shader;
struct DVector;
class DShape;

enum ColorMode
{
    RGB,
    HSB
};

enum CapStyle
{
    SQUARE = 0,
    ROUND = 1,
};

enum PosMode
{
    CENTRE = 0,
    CORNER = 1,
    //CORNERS,
};

enum ImageFormat
{
    PNG,
    JPG,
    TGA,
    BMP,
};

///\private
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
    CapStyle strokecap = CapStyle::ROUND;
    PosMode rectmode = PosMode::CORNER;
    PosMode ellipsemode = PosMode::CENTRE;
    PosMode imagemode = PosMode::CORNER;
    DFont font;
    float bezier_detail = 20;
};

///\brief Graphics class describes a render target
///
///All drawing will happen through a DGraphics object. \n
///Calling the drawpp api drawing functions will relay the call to an internal instance of DGraphics. \n
///You can create your own instance, and draw to that with the member functions, but make sure to call beginDraw() first, or things will break.
///When you are done drawing to your own target, remember to call endDraw() before drawing to other targets, or things will break.
class DGraphics
{
    friend class Application;
public:

    ~DGraphics();

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


    ///\brief Set fill color to \p rgba
    void fill(Color rgba);


    ///\brief Set fill color to \p rgb using \p alpha
    ///
    ///The alpha component of \p rgb is ignored.
    void fill(Color rgb, float alpha);


    ///\brief Set fill color to \p grey
    void fill(float grey );

    ///\brief Set fill color to \p grey with \p alpha
    void fill(float grey, float alpha);


    ///\brief Set fill color 
    ///
    ///ColorMode determines how the values are interpreted.
    void fill(float v1, float v2, float v3);

    
    ///\brief Set fill color with \p alpha
    ///
    ///ColorMode determines how the values are interpreted.
    void fill(float v1, float v2, float v3, float alpha);
    	

    ///\brief Fill target with \p rgba color
    void background(Color rgba);


    ///\brief Fill target with \p rgb color using \p alpha
    ///
    ///The alpha component of \p rgb is ignored.
    void background(Color rgb, float alpha);


    ///\brief Fill target with \p grey color
    void background(float gray );


    ///\brief Fill target with \p grey color using \p alpha
    void background(float gray, float alpha);


    ///\brief Fill target with \p image
    void background(const DImage& img);


    ///\brief Fill target with color
    ///
    ///ColorMode determines how the values are interpreted.
    void background(float v1, float v2, float v3);


    ///\brief Fill target with color using \p alpha
    ///
    ///ColorMode determines how the values are interpreted.
    void background(float v1, float v2, float v3, float alpha);


    ///\brief Set stroke color to \p rgba
    void stroke(Color rgba);


    ///\brief Set stroke color to \p rgb using \p alpha
    ///
    ///The alpha component of \p rgb is ignored.
    void stroke(Color rgb, float alpha);


    ///\brief Set stroke color to \p grey
    void stroke(float gray );


    ///\brief Set stroke color to \p grey with \p alpha
    void stroke(float gray, float alpha);

    
    ///\brief Set stroke color 
    ///
    ///ColorMode determines how the values are interpreted.
    void stroke(float v1, float v2, float v3);


    ///\brief Set stroke color with \p alpha
    ///
    ///ColorMode determines how the values are interpreted.
    void stroke(float v1, float v2, float v3, float alpha);


    ///\brief Clear target
    void clear();


    ///\brief Set the target color mode
    void colorMode(ColorMode mode);


    ///\brief Set the target color mode, and color range
    ///
    ///All ranges are set to \p max.
    void colorMode(ColorMode mode, float max);


    ///\brief Set the target color mode, and color range
    ///
    ///Alpha range remains unchaged.
    void colorMode(ColorMode mode, float max1, float max2, float max3);


    ///\brief Set the target color mode, and color range
    void colorMode(ColorMode mode, float max1, float max2, float max3, float maxA);


    ///\brief Set tint color to \p rgba
    void tint(Color rgba);


    ///\brief Set tint color to \p rgb using \p alpha
    ///
    ///The alpha component of \p rgb is ignored.
    void tint(Color rgb, float alpha);


    ///\brief Set tint color to \p grey
    void tint(float grey );


    ///\brief Set tint color to \p grey with \p alpha
    void tint(float grey, float alpha);


    ///\brief Set tint color 
    ///
    ///ColorMode determines how the values are interpreted.
    void tint(float v1, float v2, float v3);

    
    ///\brief Set tint color with \p alpha
    ///
    ///ColorMode determines how the values are interpreted.
    void tint(float v1, float v2, float v3, float alpha);


    ///\brief Get a color from \p grey
    Color color(float grey );


    ///\brief Get a color from \p grey with \p alpha
    Color color(float grey, float alpha);


    ///\brief Get a color from values
    ///
    ///ColorMode determines how the values are interpreted.
    Color color(float v1, float v2, float v3);


    ///\brief Get a color from values
    ///
    ///ColorMode determines how the values are interpreted.
    Color color(float v1, float v2, float v3, float alpha);


    ///\brief Get the red component of \p c
    float red(Color c);


    ///\brief Get the green component of \p c
    float green(Color c);


    ///\brief Get the blue component of \p c
    float blue(Color c);


    ///\brief Get the alpha component of \p c
    float alpha(Color c);


    ///\brief Get the saturation value of \p c
    float saturation(Color c);

    
    ///\brief Get the hue value of \p c
    float hue(Color c);


    ///\brief Get the brightness value of \p c
    float brightness(Color c);


    ///\brief Disable fill
    ///
    ///Any drawing functions which use fill color, will draw transparent fill.
    ///To enable fill again, call fill().
    void noFill();


    ///\brief Disable stroke
    ///
    ///Any drawing functions which use stroke, will not draw stroke.
    ///To enable stroke again, call stroke().
    void noStroke();


    ///\brief Disable tint
    ///
    ///To enable tint again, call tint().
    void noTint();


    ///\brief Set bezier curve detail
    ///
    ///Higher detail will result in smoother lines, but will quickly tank performance. \n
    ///Default detail value is 20.
    void bezierDetail(float d);


    ///\brief Set the font which will be used for drawing text
    void textFont(DFont font);


    ///\brief Set target cap style to \p cap
    void strokeCap(CapStyle cap);


    ///\brief Change stroke width
    ///
    ///Will enable stroke if it is disabled.
    void strokeWeight(float w);


    ///\brief Set the rect mode to \p m
    ///
    ///When rect mode is CENTRE, x and y will be in the center of the rectangle. \n
    ///When rect mode is CORNER, x and y will be in the top-left corner of the rectangle. \n
    ///Default mode is CORNER.
    void rectMode(PosMode m);


    ///\brief Set the ellipse mode to \p m
    ///
    ///When ellipse mode is CENTRE, x and y will be in the center of the ellipse. \n
    ///When ellipse mode is CORNER, x and y will be in the top-left corner of the rectangle around the ellipse. \n
    ///Default mode is CENTRE.
    void ellipseMode(PosMode m);


    ///\brief Set the image mode to \p m
    ///
    ///When image mode is CENTRE, x and y will be in the center of the image. \n
    ///When image mode is CORNER, x and y will be in the top-left corner of the image. \n
    ///Default mode is CORNER.
    void imageMode(PosMode m);


    ///\brief Translate view by \p x and \p y
    void translate(float x, float y );


    ///\brief Translate view by \p x, \p y and \p z
    void translate(float x, float y, float z);


    ///\brief Translate view by \p t
    void translate(const DVector& t);


    ///\brief Rotate view by \p angle
    void rotate(float angle);


    ///\brief Rotate view by \p angle in the x axis
    void rotateX(float angle);


    ///\brief Rotate view by \p angle in the y axis
    void rotateY(float angle);


    ///\brief Rotate view by \p angle in the z axis
    void rotateZ(float angle);


    ///\brief Scale view by \p s
    void scale(float s);


    ///\brief Scale view by \p x and \p y
    void scale(float x, float y );

    
    ///\brief Scale view by \p x, \p y and \p z
    void scale(float x, float y, float z);

    
    ///\brief Scale view by \p s
    void scale(const DVector& s);


    ///\brief Shear in the X direction by \p a
    void shearX(float a);


    ///\brief Shear in the Y direction by \p a
    void shearY(float a);


    ///\brief Push current transformations, and style properties to the stack
    void push();


    ///\brief Pop transformations, and style properties from the stack
    void pop();


    ///\brief Multiply the transform matrix by \p m
    void applyMatrix(const DMatrix4& m);


    ///\brief Push current transformations to the stack
    void pushMatrix();


    ///\brief Pop transformations from the stack
    void popMatrix();


    ///\brief Push current style properties to the stack
    void pushStyle();


    ///\brief Pop style properties from the stack
    void popStyle();


    ///\brief Draw an ellipse at ( \p x, \p y ), with size ( \p sizex, \p sizey )
    void ellipse(float x, float y, float sizex, float sizey );


    ///\brief Draw a circle at ( \p x, \p y ), with radius \p size
    void circle(float x, float y, float size);


    ///\brief Draw a rectangle at ( \p x, \p y ), with size ( \p sizex, \p sizey )
    void rect(float x, float y, float sizex, float sizey );


    ///\brief Draw a rectangle at ( \p x, \p y ), with size ( \p sizex, \p sizey ), and with corners rounded by \p radii
    void rect(float x, float y, float sizex, float sizey, float radii);


    ///\brief Draw a rectangle at ( \p x, \p y ), with size ( \p sizex, \p sizey ), and with corners rounded by \p tl, \p tr, \p br and \p bl
    void rect(float x, float y, float sizex, float sizey, float tl, float tr, float br, float bl);


    ///\brief Draw a square at ( \p x, \p y ), with \p size
    void square(float x, float y, float size);


    ///\brief Draw a triangle from points ( \p x1, \p y1), ( \p x2, \p y2) and ( \p x3, \p y3)
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3);


    ///\brief Draw a triangle from points \p p1, \p p2 and \p p3
    void triangle(const DVector& p1,const DVector& p2,const DVector& p3);


    ///\brief Draw a line from ( \p x1, \p y1) to ( \p x2, \p y2)
    ///
    ///Line cap style is determined by target cap style.
    void line(float x1, float y1, float x2, float y2);


    ///\brief Draw a line from \p p1 to \p p2
    ///
    ///Line cap style is determined by target cap style.
    void line(const DVector& p1,const DVector& p2);


    ///\brief Draw a point at ( \p x, \p y )
    ///
    ///Target cap style must be ROUND for the point to be visible.
    void point(float x, float y );


    ///\brief Draw a point at \p p
    ///
    ///Target cap style must be ROUND for the point to be visible.
    void point(const DVector& p);


    ///\brief Draw image \p img at ( \p x, \p y )
    void image(const DImage& img, float x, float y );


    ///\brief Draw image \p img at ( \p x, \p y ), resized to ( \p w, \p h)
    void image(const DImage& img, float x, float y, float w, float h);


    ///\brief Draw shape \p s at ( \p x, \p y ), resized to ( \p w, \p h)
    void shape(const DShape& s, float x, float y, float w, float h);


    ///\brief Draw a quad from points ( \p x1, \p y1 ), ( \p x2, \p y2 ), ( \p x3, \p y3 ) and ( \p x4, \p y4 )
    void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);


    ///\brief Draw a quad from points \p p1, \p p2, \p p3 and \p p4
    void quad(const DVector& p1, const DVector& p2, const DVector& p3, const DVector& p4);


    ///\brief Save target pixels to a file as an image
    ///
    ///\p filename should not include the extenstion, as it will be added according to \p format.
    ///\return success
    bool save(const std::string& filename, ImageFormat format = ImageFormat::PNG) const;


    ///\brief Draw text at ( \p x, \p y )
    ///
    ///A font must be set with textFont() before drawing any text.
    void text(const std::string& txt, float x, float y);


    ///\copydoc text(const std::string&,float,float);
    void text(const std::wstring& txt, float x, float y);


    ///\brief Draw a cubic bezier curve from 4 points.
    void bezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2);


    ///\brief Draw a cubic bezier curve from 4 points.
    void bezier(const DVector& p1, const DVector& p2, const DVector& cp1, const DVector& cp2);


    ///\brief Draw a quadratic bezier curve from 3 points
    void bezier(float x1, float y1, float x2, float y2, float cx, float cy);


    ///\brief Draw a quadratic bezier curve from 3 points
    void bezier(const DVector& p1, const DVector& p2, const DVector& cp);


    GraphicsProperties getStyle();

private:

    //Get the texture id for this graphics object
    unsigned int get_texture_id();

    //Get rgba color from rgba components
    Color get_rgba(float r, float g, float b, float a);

    //Get rgba color from hsba components
    Color get_hsba(float h, float s, float b, float a);

    //Get rgba color from the components
    Color get_color(float v1, float v2, float v3, float a);

    //void set_current();

    //Initialize the shaders used by this graphics object
    void init_shaders();


    //Style properties 
    GraphicsProperties properties;

    //is this needed?
    DMatrix4 transform_mat = DMatrix4::identity();

    //View transformations
    DMatrix4 view_mat;

    //View transformations stack
    std::stack<DMatrix4> matrix_stack;

    //Style properties stack
    std::stack<GraphicsProperties> property_stack;

    //Target framebuffer info
    unsigned int buffer_id = static_cast<unsigned int>(-1);
    unsigned int texture_id = 0;
    unsigned int buffer_width = 0;
    unsigned int buffer_height = 0;
    int type = -1;
    int format = -1;

    //Shader used to draw ellipses
    std::unique_ptr<Shader> ellipse_shader;
    int ellipse_shader_offset_loc;
    int ellipse_shader_strokeWeight_loc;
    int ellipse_shader_strokeColor_loc;
    int ellipse_shader_fillColor_loc;
    int ellipse_shader_transform_loc;
    int ellipse_shader_view_loc;
    int ellipse_shader_posmode_loc;
    int ellipse_shader_vpos_loc;
    int ellipse_shader_tpos_loc;

    //Shader used to draw rectangles
    std::unique_ptr<Shader> rect_shader;
    int rect_shader_offset_loc;
    int rect_shader_strokeWeight_loc;
    int rect_shader_strokeColor_loc;
    int rect_shader_fillColor_loc;
    int rect_shader_transform_loc;
    int rect_shader_view_loc;
    int rect_shader_posmode_loc;
    int rect_shader_radii_loc;
    int rect_shader_vpos_loc;
    int rect_shader_tpos_loc;

    //Shader used to draw triangles
    std::unique_ptr<Shader> triangle_shader;
    int triangle_shader_strokeWeight_loc;
    int triangle_shader_strokeColor_loc;
    int triangle_shader_fillColor_loc;
    int triangle_shader_bpos_loc;
    int triangle_shader_transform_loc;
    int triangle_shader_view_loc;
    int triangle_shader_vpos_loc;

    //Shader used to draw lines
    std::unique_ptr<Shader> line_shader;
    int line_shader_points_loc;
    int line_shader_strokeWeight_loc;
    int line_shader_strokeColor_loc;
    int line_shader_transform_loc;
    int line_shader_view_loc;
    int line_shader_cap_loc;
    int line_shader_vpos_loc;
    int line_shader_tpos_loc;

    //Shader used to draw images
    std::unique_ptr<Shader> image_shader;
    int image_shader_offset_loc;
    int image_shader_tint_loc;
    int image_shader_use_tint_loc;
    int image_shader_posmode_loc;
    int image_shader_tex_loc;
    int image_shader_transform_loc;
    int image_shader_view_loc;
    int image_shader_vpos_loc;
    int image_shader_tpos_loc;

    //Shader used to draw quads
    std::unique_ptr<Shader> quad_shader;
    int quad_shader_strokeWeight_loc;
    int quad_shader_strokeColor_loc;
    int quad_shader_fillColor_loc;
    int quad_shader_bpos_loc;
    int quad_shader_transform_loc;
    int quad_shader_view_loc;
    int quad_shader_vpos_loc;

    //Shader used to draw text
    std::unique_ptr<Shader> text_shader;
    int text_shader_texture_loc;
    int text_shader_posmode_loc;
    int text_shader_fillColor_loc;
    int text_shader_transform_loc;
    int text_shader_view_loc;
    int text_shader_vpos_loc;
    int text_shader_tpos_loc;
};

#endif