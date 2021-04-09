#ifndef DPP_H
#define DPP_H
#include <application.hpp>
#include <keys.hpp>
#include <image.hpp>
#include <shader.hpp>
#include <color.hpp>
#include <graphics.hpp>
#include <shape.hpp>
#include <font.hpp>
#include <constants.hpp>


///\file
///\defgroup drawpp_function_api Drawpp function API
///\addtogroup drawpp_function_api
///@{

///\defgroup drwapp_misc_api Miscellaneous

///\defgroup drawpp_loaders_api Loaders

///\defgroup drawpp_application_api Application
///\addtogroup drawpp_application_api
///@{

///\copydoc Application::exit()
void exit();


///\copydoc Application::setFrameRate(int)
void frameRate(int fps);


///\copydoc Application::setVSync(bool)
void vSync(bool state);


///\copydoc Application::size(int,int)
void size(int width, int height);


///\copydoc Application::setResizable(bool)
void setResizable(bool);


///\copydoc Application::setTitle(const char*)
void setTitle(const char* title);


// End group drawpp_application_api
///@}


///\defgroup drawpp_drawing_api Drawing
///\addtogroup drawpp_drawing_api
///@{

// DShape
// Draws given shape
//void shape(DShape* _shape);
//void shape(DShape* _shape, float x, float  y);
//void shape(DShape* _shape, float x, float y, float w, float h);

///\brief Draw a shape at the origin
void shape(const DShape& _shape);


///\brief Draw a shape at ( \p x, \p y )
void shape(const DShape& _shape, float x, float  y);


///\copydoc DGraphics::shape(const DShape&,float,float,float,float)
void shape(const DShape& _shape, float x, float y, float w, float h);

// End group drawpp_drawing_api
///@}

///\ingroup drawpp_loaders_api
///\copydoc DShape::loadShape(const std::string&)
DShape loadShape(const std::string& filename);


//DShape createShape();
//DShape createShape(DShape::ShapeType type);
//DShape createShape(DShape::ShapeType type, float[] p);


///\addtogroup drawpp_drawing_api
///@{

// Shapes 2D


//void arc(int x, int y, int width, int height, int start, int stop);
//void arc(int x, int y, int width, int height, int start, int stop, int mode);


///\copydoc DGraphics::circle(float,float,float)
void circle(float x, float y, float radius);


///\copydoc DGraphics::circle(const DVector&,float)
void circle(const DVector& p, float radius);


///\copydoc DGraphics::ellipse(float,float,float,float)
void ellipse(float x, float y, float width, float height);


///\copydoc DGraphics::ellipse(const DVector&,const DVector&)
void ellipse(const DVector& p, const DVector& s);


///\copydoc DGraphics::line(float,float,float,float)
void line(float x1, float y1, float x2, float y2);


///\copydoc DGraphics::line(const DVector&,const DVector&)
void line(const DVector& p1,const DVector& p2);


///\copydoc DGraphics::point(float,float)
void point(float x, float y);


///\copydoc DGraphics::point(const DVector&)
void point(const DVector& p);


///\copydoc DGraphics::quad(float,float,float,float,float,float,float,float)
void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);


///\copydoc DGraphics::quad(const DVector&,const DVector&,const DVector&,const DVector&)
void quad(const DVector& p1, const DVector& p2, const DVector& p3, const DVector& p4);


///\copydoc DGraphics::rect(float,float,float,float)
void rect(float x, float y, float w, float h);


///\copydoc DGraphics::rect(const DVector&,const DVector&)
void rect(const DVector& p, const DVector& s);


///\copydoc DGraphics::rect(float,float,float,float,float)
void rect(float x, float y, float w, float h, float radii);


///\copydoc DGraphics::rect(const DVector&,const DVector&,float)
void rect(const DVector& p, const DVector& s, float radii);


///\copydoc DGraphics::rect(float,float,float,float,float,float,float,float)
void rect(float x, float y, float w, float h, float tl, float tr, float br, float bl);


///\copydoc DGraphics::rect(const DVector&,const DVector&,float,float,float,float)
void rect(const DVector& p, const DVector& s, float tl, float tr, float br, float bl);


///\copydoc DGraphics::square(float,float,float)
void square(float x, float y, float size);


///\copydoc DGraphics::square(const DVector&,float)
void square(const DVector& p, float size);


///\copydoc DGraphics::triangle(float,float,float,float,float,float)
void triangle(float x1, float y1, float x2, float y2, float x3, float y3);


///\copydoc DGraphics::triangle(const DVector&,const DVector&,const DVector&)
void triangle(const DVector& p1, const DVector& p2, const DVector& p3);


///\copydoc DGraphics::bezier(float,float,float,float,float,float,float,float)
void bezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2);


///\copydoc DGraphics::bezier(const DVector&,const DVector&,const DVector&,const DVector&)
void bezier(const DVector& p1, const DVector& p2, const DVector& cp1, const DVector& cp2);


///\copydoc DGraphics::bezier(float,float,float,float,float,float)
void bezier(float x1, float y1, float x2, float y2, float cx, float cy);


///\copydoc DGraphics::bezier(const DVector&,const DVector&,const DVector&)
void bezier(const DVector& p1, const DVector& p2, const DVector& cp);


// Shapes 3D

//void point(int x, int y, int z);
//void line(int x1, int y1, int z1, int x2, int y2, int z2);
//void box(int size);
//void box(int width, int height, int dimension);
//void sphere(int radius);


// Font and text

// End group drawpp_drawing_api
///@}


///\ingroup drawpp_loaders_api
///\copydoc DFont::const std::string&, float, float, float)
DFont loadFont(const std::string& filename, int size, float row_spacing = 0.0f, float char_spacing = 0.0f);

///\ingroup drawpp_loaders_api
///\copydoc DFont::load(const std::string&,const FontOptions&)
DFont loadFont(const std::string& filename, const FontOptions& opt);


///\defgroup drawpp_drawing_properties_api Drawing Properties

///\ingroup drawpp_drawing_properties_api
///\copydoc DGraphics::textFont(DFont)
void textFont(DFont font);


///\addtogroup drawpp_drawing_api
///@{

///\copydoc DGraphics::text(const std::string&,float,float)
void text(const std::string& txt, float x, float y);


///\copydoc DGraphics::text(const std::string&,const DVector&)
void text(const std::string& txt, const DVector& p);


///\copydoc DGraphics::text(const std::wstring&,float,float)
void text(const std::wstring& txt, float x, float y);


///\copydoc DGraphics::text(const std::wstring&,const DVector&)
void text(const std::wstring& txt, const DVector& p);


// End group drawpp_drawing_api
///@}


///\addtogroup drawpp_drawing_properties_api
///@{

///\copydoc DGraphics::rectMode(PosMode)
void rectMode(PosMode m);


///\copydoc DGraphics::ellipseMode(PosMode)
void ellipseMode(PosMode m);


///\copydoc DGraphics::imageMode(PosMode)
void imageMode(PosMode m);


///\copydoc DGraphics::strokeWeight(float)
void strokeWeight(float w);


///\copydoc DGraphics::strokeCap(CapStyle)
void strokeCap(CapStyle cap);


///\copydoc DGraphics::noFill()
void noFill();


///\copydoc DGraphics::noStroke()
void noStroke();


///\copydoc DGraphics::noTint();
void noTint();


///\copydoc DGraphics::bezierDetail()
void bezierDetail(float d);


// End group drawpp_drawing_properties_api
///@}


///\ingroup drawpp_drawing_api
///\copydoc DGraphics::clear()
void clear();


// Color


///\addtogroup drawpp_drawing_properties_api
///@{

///\copydoc DGraphics::fill(Color)
void fill(Color col);


///\copydoc DGraphics::fill(Color,float)
void fill(Color rgb, float alpha);


//void fill(std::string hexCol);


///\copydoc DGraphics::fill(float)
void fill(float grey);


///\copydoc DGraphics::fill(float,float)
void fill(float grey, float alpha);


///\copydoc DGraphics::fill(float,float,float)
void fill(float v1, float v2, float v3);


///\copydoc DGraphics::fill(float,float,float,float)
void fill(float v1, float v2, float v3, float alpha);


///\copydoc DGraphics::stroke(Color)
void stroke(Color rgba);


///\copydoc DGraphics::stroke(Color,float)
void stroke(Color rgb, float alpha);


//void stroke(std::string hexCol);


///\copydoc DGraphics::stroke(float)
void stroke(float grey);


///\copydoc DGraphics::stroke(float,float)
void stroke(float grey, float alpha);


///\copydoc DGraphics::stroke(float,float,float)
void stroke(float v1, float v2, float v3);


///\copydoc DGraphics::stroke(float,float,float,float)
void stroke(float v1, float v2, float v3, float alpha);


// End group drawpp_drawing_properties_api
///@}


///\addtogroup drawpp_drawing_api
///@{

///\copydoc DGraphics::background(Color)
void background(Color col);


///\copydoc DGraphics::background(Color,float)
void background(Color rgb, float alpha);


///\brief Fill target with \p hexCol color
void background(const char* hexCol);


///\copydoc DGraphics::background(float)
void background(float grey);


///\copydoc DGraphics::background(float,float)
void background(float grey, float alpha);


///\copydoc DGraphics::background(float,float,float)
void background(float v1, float v2, float v3);


///\copydoc DGraphics::background(float,float,float,float)
void background(float v1, float v2, float v3, float alpha);


// End group drawpp_drawing_api
///@}


///\addtogroup drawpp_drawing_properties_api
///@{

///\copydoc DGraphics::tint(Color)
void tint(Color col);


///\copydoc DGraphics::tint(Color,float)
void tint(Color rgb, float alpha);


///\brief Set tint color to \p hexCol
void tint(const char* hexCol);


///\copydoc DGraphics::tint(float)
void tint(float grey);


///\copydoc DGraphics::tint(float,float)
void tint(float grey, float alpha);


///\copydoc DGraphics::tint(float,float,float)
void tint(float v1, float v2, float v3);


///\copydoc DGraphics::tint(float,float,float,float)
void tint(float v1, float v2, float v3, float alpha);


// End group drawpp_drawing_properties_api
///@}


///\defgroup drawpp_color_api Color
///\addtogroup drawpp_color_api
///@{

///\copydoc DGraphics::colorMode(ColorMode)
void colorMode(ColorMode mode);


///\copydoc DGraphics::colorMode(ColorMode,float)
void colorMode(ColorMode mode, float max);


///\copydoc DGraphics::colorMode(ColorMode,float,float,float)
void colorMode(ColorMode mode, float max1, float max2, float max3);


///\copydoc DGraphics::colorMode(ColorMode,float,float,float,float)
void colorMode(ColorMode mode, float max1, float max2, float max3, float maxA);


///\copydoc DGraphics::color(float)
Color color(float grey);


///\copydoc DGraphics::color(float,float)
Color color(float grey, float alpha);


///\copydoc DGraphics::color(float,float,float)
Color color(float v1, float v2, float v3);


///\copydoc DGraphics::color(float,float,float,float)
Color color(float v1, float v2, float v3, float alpha);


///\copydoc DGraphics::alpha(Color)
float alpha(Color col);


///\copydoc DGraphics::red(Color)
float red(Color col);


///\copydoc DGraphics::green(Color)
float green(Color col);


///\copydoc DGraphics::blue(Color)
float blue(Color col);


///\copydoc DGraphics::hue(Color)
float hue(Color col);


///\copydoc DGraphics::saturation(Color)
float saturation(Color col);


///\copydoc DGraphics::brightness(Color)
float brightness(Color col);


///\copydoc Color::lerpColor(const Color&,const Color&,float)
// Lerps color. Percentage needs to be in range 0.0 - 1.0 or it will be cut to closest point
Color lerpColor(const Color& from, const Color& to, float percentage);


///\brief Get the given Color's value converted to HEX format
///\returns Given Color's value as string containing the HEX
std::string hex(Color col);


///\copydoc Color::hex(Color,int)
std::string hex(Color col, int num);


// End group drawpp_color_api
///@}


// Image

///\ingroup drawpp_loaders_api
///\copydoc DImage::loadImage(const std::string&)
DImage loadImage(const std::string& fileName);

///\ingroup drawpp_loaders_api
///\copydoc DImage::loadSVGImage(const std::string&,float)
DImage loadSVGImage(const std::string& filename, float scale = 1.0f);


///\addtogroup drawpp_drawing_api
///@{

///\copydoc DGraphics::image(const DImage&,float,float)
void image(const DImage& image, float x, float y);


///\copydoc DGraphics::image(const DImage&,const DVector&)
void image(const DImage& image, const DVector& p);


///\copydoc DGraphics::image(const DImage&,float,float,float,float)
void image(const DImage& image, float x, float y, float width, float height);


///\copydoc DGraphics::image(const DImage&,const DVector&,const DVector&)
void image(const DImage& image, const DVector& p, const DVector s);


///\copydoc DGraphics::background(const DImage&)
void background(const DImage& image);


// End group drawpp_drawing_api
///@}


// Shader
Shader loadShadersFromFile(const char* vertexShader, const char* fregmentShader);
Shader loadShadersFromString(const char* vertexShader, const char* fregmentShader);
Shader loadShadersDefault();


///\defgroup drawpp_transform_api Transform
///\addtogroup drawpp_transform_api
///@{

// Transform

///\copydoc DGraphics::translate(float,float)
void translate(float x, float y);


///\copydoc DGraphics::translate(float,float,float
void translate(float x, float y, float z);


///\copydoc DGraphics::translate(const DVector&)
void translate(const DVector& t);


///\copydoc DGraphics::rotate(float)
void rotate(float angle);


///\copydoc DGraphics::rotateX(float)
void rotateX(float angle);


///\copydoc DGraphics::rotateY(float)
void rotateY(float angle);


///\copydoc DGraphics::rotateZ(float)
void rotateZ(float angle);


///\copydoc DGraphics::scale(float)
void scale(float s);


///\copydoc DGraphics::scale(float,float)
void scale(float x, float y);


///\copydoc DGraphics::scale(float,float,float)
void scale(float x, float y, float z);


///\copydoc DGraphics::scale(const DVector&)
void scale(const DVector& s);


///\copydoc DGraphics::shearX(float)
void shearX(float a);


///\copydoc DGraphics::shearY(float)
void shearY(float a);


// End group drawpp_transform_api
///@}


///\defgroup drawpp_input_api Input
///\addtogroup drawpp_input_api
///@{


// Input

///\brief \p key will be the last key that was pressed
///
///If the last key was not within ascii range, \p key will be VK_CODED, 
///and the actual keycode will be in \p keyCode. \n
///As the type of \p key is char, it can be compared with characters, but also with KeyID values.
extern char key;


///\brief \p keyCode has the keycode of the last key that was pressed
extern int keyCode;


///\brief \p mouseButton has the id of the last mouse button to be pressed or released
extern int mouseButton;


///\brief \p mouseX has the latest mouse x position
extern int mouseX;


///\brief \p mouseY has the latest mouse y position
extern int mouseY;


///\brief \p pmouseX has the previous mouse x position
///
///This is updated at the same time as \p mouseX
extern int pmouseX;


///\brief \p pmouseY has the previous mouse Y position
///
///This is updated at the same time as \p mouseY
extern int pmouseY;


///\brief \p pfmouseX has the last mouse x position of the last frame
///
///This is updated once per frame
extern int pfmouseX;


///\brief \p pfmouseY has the last mouse y position of the last frame
///
///This is updated once per frame
extern int pfmouseY;


// End group drawpp_input_api
///@}


// Random

///\defgroup drawpp_random_api Random
///\addtogroup drawpp_random_api
///@{


///\brief Set the seed for the default random number generator
void randomSeed(int seed);


///\copydoc Random::randomInt(int)
int randomInt(int high);


///\copydoc Random::randomInt(int,int)
int randomInt(int low, int high);


//float randomFloat();


///\copydoc Random::randomFloat(float,float)
float randomFloat(float low, float high);


///\copydoc Random::randomGaussian()
float randomGaussian();


// End group drawpp_random_api
///@}


///\defgroup drawpp_noise_api Noise
///\addtogroup drawpp_noise_api
///@{

// Noise

///\copydoc Noise::pNoise(unsigned int)
float noise(int x);


///\copydoc Noise::pNoise(unsigned int,unsigned int)
float noise(int x, int y);


///\copydoc Noise::noiseSeed(int)
void noiseSeed(int x);


///\copydoc Noise::setScale(float)
void noiseScale(float scale);


///\copydoc Noise::setOctaves(int)
void noiseDetails(int lod);


///\copydoc Noise::setOctaves(int)
///\copydoc Noise::setFalloff(float)
void noiseDetails(int lod, float falloff);


///\copydoc Noise::resize(int,int)
void noiseMapSize(int width, int heigth);


// End group drawpp_noise_api
///@}



// Push Pop

///\ingroup drwapp_misc_api
///\copydoc DGraphics::push()
void push();


///\ingroup drwapp_misc_api
///\copydoc DGraphics::pop()
void pop();


///\addtogroup drawpp_transform_api
///@{

///\copydoc DGraphics::applyMatrix(const DMatrix4&)
void applyMatrix(const DMatrix4& m);


///\copydoc DGraphics::pushMatrix()
void pushMatrix();


///\copydoc DGraphics::popMatrix()
void popMatrix();


///\copydoc DGraphics::pushStyle()
void pushStyle();


///\copydoc DGraphics::popStyle()
void popStyle();


// End group drawpp_transform_api
///@}


///\defgroup drawpp_time_api Time
///\addtogroup drawpp_time_api
///@{

//Time

///\copydoc Time::millis()
long long millis();


///\copydoc Time::second()
int second();


///\copydoc Time::minute()
int minute();


///\copydoc Time::hour()
int hour();


///\copydoc Time::day()
int day();


///\copydoc Time::month()
int month();


///\copydoc Time::year()
int year();


///\copydoc Time::Reset()
void timeReset();


// End group drawpp_time_api
///@}


///\ingroup drwapp_misc_api
///\copydoc DGraphics::save(const std::string&,ImageFormat)const
bool save(const std::string& filename, ImageFormat format = ImageFormat::PNG);


// End group drawpp_function_api
///@}

#endif