#include <algorithm>
#include <graphics.hpp>
#include <shader.hpp>
#include <glad.h>
#include <debug.hpp>
#include <vector2.hpp>
#include <vector3.hpp>
#include <font.hpp>
#include <font_impl.hpp>
#include <cstring>
#include <locale>
#include <codecvt>
#include <shape.hpp>
#include <shape_impl.hpp>
#include <constants.hpp>
#include <application.hpp>
#include <filter.hpp>
#include <filter_impl.hpp>
#include <sstream>
#include <iomanip>
#include <vectormath.hpp>

#include "stb_image_write.h"

#pragma warning(push,1)
#include "nanosvg.h"
#include "nanosvgrast.h"
#pragma warning(pop)

static const float primitive_square[] = 
{
    0.0f, -1.0f,
    1.0f, -1.0f,
    1.0f,  0.0f,
    0.0f, -1.0f,
    1.0f,  0.0f,
    0.0f,  0.0f,
};

static const float primitive_square_flipped[] = 
{
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, -1.0f,
    0.0f, 0.0f,
    1.0f, -1.0f,
    0.0f, -1.0f,
};

static const float view_vertex[] = 
{
    -1.0f,  1.0f,
     1.0f,  1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f, -1.0f,
    -1.0f, -1.0f,
};

static const float coords_view[] = 
{
    0.0f, 1.0f,
    1.0f, 1.0f, 
    1.0f, 0.0f, 
    0.0f, 1.0f, 
    1.0f, 0.0f, 
    0.0f, 0.0f, 
};

static const float primitive_square_line[] = 
{
    -0.5f,-0.5f,
    0.5f, -0.5f,
    0.5f,  0.5f,
    -0.5f,-0.5f,
    0.5f,  0.5f,
    -0.5f, 0.5f,
};

static const float coords_quad[] = 
{
    0.0f, 0.0f,
    1.0f, 0.0f, 
    1.0f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 1.0f, 
    0.0f, 1.0f, 
};

static const float coords_img[] = 
{
    0.0f, 1.0f,
    1.0f, 1.0f, 
    1.0f, 0.0f, 
    0.0f, 1.0f, 
    1.0f, 0.0f, 
    0.0f, 0.0f, 
};

static float triangle_verts[] = 
{
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
};

static float quad_verts[] = 
{
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
};

static std::vector<float> txt_vert_buffer;
static std::vector<float> txt_texc_buffer;
static std::vector<Vector2> bezier_buffer;

extern unsigned long long frameCount;

#include <shaders/generic_vert.ipp>
#include <shaders/ellipse_frag.ipp>
#include <shaders/rect_frag.ipp>
#include <shaders/triangle_vert.ipp>
#include <shaders/triangle_frag.ipp>
#include <shaders/line_vert.ipp>
#include <shaders/line_frag.ipp>
#include <shaders/image_frag.ipp>
#include <shaders/quad_frag.ipp>
#include <shaders/text_vert.ipp>
#include <shaders/text_frag.ipp>
#include <shaders/generic_colored_vert.ipp>
#include <shaders/generic_colored_frag.ipp>

DGraphics::DGraphics(int width, int height)
{
    buffer_width = static_cast<unsigned int>(width);
    buffer_height = static_cast<unsigned int>(height);

    GLint prev_buffer = (GLint)-1;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_buffer);

    //create primary buffer
    glGenFramebuffers(1,&buffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_id);
    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,buffer_width,buffer_height,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture_id,0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        dbg::error("Failed to create primary framebuffer");
    }

    //create secondary buffer for filter rendering
    glGenFramebuffers(1,&filter_buffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, filter_buffer_id);
    glGenTextures(1,&filter_texture_id);
    glBindTexture(GL_TEXTURE_2D,filter_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,buffer_width,buffer_height,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,filter_texture_id,0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        dbg::error("Failed to create secondary framebuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, prev_buffer);

    init_shaders();
    view_mat = Matrix4::identity().translate(Vector3(-1.0f,1.0f,0.0f)).scale(Vector3(2.0f/buffer_width,2.0f/buffer_height,1.0f));
}

DGraphics::~DGraphics()
{
    if(buffer_id != static_cast<unsigned int>(-1))
    {
        glDeleteFramebuffers(1,&buffer_id);
    }

    if(texture_id != 0)
    {
        glDeleteTextures(1,&texture_id);
    }

    if(filter_buffer_id != static_cast<unsigned int >(-1))
    {
        glDeleteFramebuffers(1,&filter_buffer_id);
    }

    if(filter_texture_id != 0)
    {
        glDeleteTextures(1,&filter_texture_id);
    }
}

void DGraphics::init_shaders()
{
    ellipse_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(generic_shader_v,ellipse_shader_f)));
    
    ellipse_shader_offset_loc = glGetUniformLocation(ellipse_shader->getId(),"offset");
    ellipse_shader_strokeWeight_loc = glGetUniformLocation(ellipse_shader->getId(),"strokeWeight");
    ellipse_shader_strokeColor_loc = glGetUniformLocation(ellipse_shader->getId(),"strokeColor");                                             
    ellipse_shader_fillColor_loc = glGetUniformLocation(ellipse_shader->getId(),"fillColor");
    ellipse_shader_transform_loc = glGetUniformLocation(ellipse_shader->getId(),"transform");
    ellipse_shader_view_loc = glGetUniformLocation(ellipse_shader->getId(),"view");
    ellipse_shader_posmode_loc = glGetUniformLocation(ellipse_shader->getId(),"posmode");
    ellipse_shader_vpos_loc = glGetAttribLocation(ellipse_shader->getId(),"pos");
    ellipse_shader_tpos_loc = glGetAttribLocation(ellipse_shader->getId(),"texpos");

    rect_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(generic_shader_v,rect_shader_f)));
    
    rect_shader_offset_loc = glGetUniformLocation(rect_shader->getId(),"offset");
    rect_shader_strokeWeight_loc = glGetUniformLocation(rect_shader->getId(),"strokeWeight");
    rect_shader_strokeColor_loc = glGetUniformLocation(rect_shader->getId(),"strokeColor");                                             
    rect_shader_fillColor_loc = glGetUniformLocation(rect_shader->getId(),"fillColor");                                           
    rect_shader_radii_loc = glGetUniformLocation(rect_shader->getId(),"radii");
    rect_shader_view_loc = glGetUniformLocation(rect_shader->getId(),"view");
    rect_shader_transform_loc = glGetUniformLocation(rect_shader->getId(),"transform");
    rect_shader_posmode_loc = glGetUniformLocation(rect_shader->getId(),"posmode");
    rect_shader_vpos_loc = glGetAttribLocation(rect_shader->getId(),"pos");
    rect_shader_tpos_loc = glGetAttribLocation(rect_shader->getId(),"texpos");

    triangle_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(triangle_shader_v,triangle_shader_f)));

    triangle_shader_strokeWeight_loc = glGetUniformLocation(triangle_shader->getId(),"strokeWeight");
    triangle_shader_strokeColor_loc = glGetUniformLocation(triangle_shader->getId(),"strokeColor");                                             
    triangle_shader_fillColor_loc = glGetUniformLocation(triangle_shader->getId(),"fillColor");
    triangle_shader_transform_loc = glGetUniformLocation(triangle_shader->getId(),"transform");
    triangle_shader_view_loc = glGetUniformLocation(triangle_shader->getId(),"view");
    triangle_shader_bpos_loc = glGetUniformLocation(triangle_shader->getId(),"bpos");
    triangle_shader_vpos_loc = glGetAttribLocation(triangle_shader->getId(),"pos");

    line_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(line_shader_v,line_shader_f)));

    line_shader_points_loc = glGetUniformLocation(line_shader->getId(),"points");
    line_shader_strokeWeight_loc = glGetUniformLocation(line_shader->getId(),"strokeWeight");
    line_shader_strokeColor_loc = glGetUniformLocation(line_shader->getId(),"strokeColor"); 
    line_shader_transform_loc = glGetUniformLocation(line_shader->getId(),"transform");  
    line_shader_view_loc = glGetUniformLocation(line_shader->getId(),"view");
    line_shader_tpos_loc = glGetAttribLocation(line_shader->getId(),"texpos");
    line_shader_vpos_loc = glGetAttribLocation(line_shader->getId(),"pos");

    image_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(generic_shader_v,image_shader_f)));
 
    image_shader_offset_loc = glGetUniformLocation(image_shader->getId(),"offset");
    image_shader_tint_loc = glGetUniformLocation(image_shader->getId(),"tint");
    image_shader_use_tint_loc = glGetUniformLocation(image_shader->getId(),"useTint");
    image_shader_posmode_loc = glGetUniformLocation(image_shader->getId(),"posmode");
    image_shader_transform_loc = glGetUniformLocation(image_shader->getId(),"transform");  
    image_shader_view_loc = glGetUniformLocation(image_shader->getId(),"view");
    image_shader_tex_loc = glGetUniformLocation(image_shader->getId(),"tex");
    image_shader_tpos_loc = glGetAttribLocation(image_shader->getId(),"texpos");
    image_shader_vpos_loc = glGetAttribLocation(image_shader->getId(),"pos");

    quad_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(triangle_shader_v,quad_shader_f)));

    quad_shader_strokeWeight_loc = glGetUniformLocation(quad_shader->getId(),"strokeWeight");
    quad_shader_strokeColor_loc = glGetUniformLocation(quad_shader->getId(),"strokeColor");                                             
    quad_shader_fillColor_loc = glGetUniformLocation(quad_shader->getId(),"fillColor");
    quad_shader_transform_loc = glGetUniformLocation(quad_shader->getId(),"transform");  
    quad_shader_view_loc = glGetUniformLocation(quad_shader->getId(),"view");
    quad_shader_bpos_loc = glGetUniformLocation(quad_shader->getId(),"bpos");
    quad_shader_vpos_loc = glGetAttribLocation(quad_shader->getId(),"pos");

    text_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(text_shader_v,text_shader_f)));
                                      
    text_shader_fillColor_loc = glGetUniformLocation(text_shader->getId(),"fillColor");
    text_shader_transform_loc = glGetUniformLocation(text_shader->getId(),"transform");
    text_shader_view_loc = glGetUniformLocation(text_shader->getId(),"view");
    text_shader_texture_loc = glGetUniformLocation(image_shader->getId(),"texture");
    text_shader_posmode_loc = glGetUniformLocation(text_shader->getId(),"posmode");
    text_shader_vpos_loc = glGetAttribLocation(text_shader->getId(),"pos");
    text_shader_tpos_loc = glGetAttribLocation(text_shader->getId(),"texpos");

    generic_colored_shader = std::shared_ptr<Shader>(new Shader(Shader::loadShadersFromString(generic_colored_shader_v,generic_colored_shader_f)));
                                      
    generic_colored_shader_color_loc = glGetUniformLocation(generic_colored_shader->getId(),"color");
    generic_colored_shader_transform_loc = glGetUniformLocation(generic_colored_shader->getId(),"transform");
    generic_colored_shader_view_loc = glGetUniformLocation(generic_colored_shader->getId(),"view");
    generic_colored_shader_vpos_loc = glGetAttribLocation(generic_colored_shader->getId(),"pos");
}

void DGraphics::beginDraw()
{
    transform_mat = Matrix4::identity();
    glBindFramebuffer(GL_FRAMEBUFFER,buffer_id);
    glViewport(0,0,buffer_width,buffer_height);

    if(properties.use_clip)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(properties.clip_x1,
                buffer_height-properties.clip_y1-properties.clip_y2,
                properties.clip_x2,
                properties.clip_y2);
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void DGraphics::endDraw()
{
    glDisable(GL_SCISSOR_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER,Application::GetInstance()->graphics_object().buffer_id);
}

void DGraphics::fill(Color rgba)
{
    properties.fill_color = rgba;
    properties.use_fill = true;
}

void DGraphics::fill(Color rgb, float alpha)
{
    properties.fill_color = Color(rgb.red,rgb.green,rgb.blue,static_cast<uint8_t>(alpha / properties.color_maxa));
    properties.use_fill = true;
}

void DGraphics::fill(float gray)
{
    fill(gray,properties.color_maxa);
}

void DGraphics::fill(float gray, float alpha)
{
    properties.fill_color = color(gray, alpha);
    properties.use_fill = true;
}

void DGraphics::fill(float v1, float v2, float v3)
{
    properties.fill_color = get_color(v1,v2,v3,properties.color_maxa);
    properties.use_fill = true;
}

void DGraphics::fill(float v1, float v2, float v3, float alpha)
{
    properties.fill_color = get_color(v1,v2,v3,alpha);
    properties.use_fill = true;
}

void DGraphics::stroke(Color rgba)
{
    properties.stroke_color = rgba;
    properties.use_stroke = true;
}

void DGraphics::stroke(Color rgb, float alpha)
{
    properties.stroke_color = Color(rgb.red,rgb.green,rgb.blue,static_cast<uint8_t>(alpha/properties.color_maxa));
    properties.use_stroke = true;
}

void DGraphics::stroke(float gray)
{
    stroke(gray,properties.color_maxa);
}

void DGraphics::stroke(float gray, float alpha)
{
    properties.stroke_color = color(gray, alpha);
    properties.use_stroke = true;
}

void DGraphics::stroke(float v1, float v2, float v3)
{
    properties.stroke_color = get_color(v1,v2,v3,properties.color_maxa);
    properties.use_stroke = true;
}

void DGraphics::stroke(float v1, float v2, float v3, float alpha)
{
    properties.stroke_color = get_color(v1,v2,v3,alpha);
    properties.use_stroke = true;
}

void DGraphics::clear()
{
    glDisable(GL_BLEND);
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
}

void DGraphics::background(Color rgba)
{
    glClearColor(rgba.red / 255.0f,
                rgba.green / 255.0f,
                rgba.blue / 255.0f,
                rgba.alpha / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DGraphics::background(Color rgb, float alpha)
{
    background(Color(rgb.red,rgb.green,rgb.blue,static_cast<uint8_t>(alpha/properties.color_maxa)));
}

void DGraphics::background(float gray)
{
    background(color(gray,properties.color_maxa));
}

void DGraphics::background(float gray, float alpha)
{
    background(color(gray,alpha));
}

void DGraphics::background(float v1, float v2, float v3)
{
    background(get_color(v1,v2,v3,properties.color_maxa));
}

void DGraphics::background(float v1, float v2, float v3, float alpha)
{
    background(get_color(v1,v2,v3,alpha));
}

void DGraphics::background(const DImage& img)
{
    PosMode imgm = properties.imagemode;
    properties.imagemode = PosMode::CORNER;
    image(img,0.0f,0.0f,static_cast<float>(buffer_width),static_cast<float>(buffer_height));
    properties.imagemode = imgm;
}

void DGraphics::colorMode(ColorMode mode)
{
    properties.colormode = mode;
}

void DGraphics::colorMode(ColorMode mode, float max)
{
    properties.colormode = mode;
    properties.color_max1 = max;
    properties.color_max2 = max;
    properties.color_max3 = max;
    properties.color_maxa = max;
}

void DGraphics::colorMode(ColorMode mode, float max1, float max2, float max3)
{
    properties.colormode = mode;
    properties.color_max1 = max1;
    properties.color_max2 = max2;
    properties.color_max3 = max3;
}

void DGraphics::colorMode(ColorMode mode, float max1, float max2, float max3, float maxA)
{
    properties.colormode = mode;
    properties.color_max1 = max1;
    properties.color_max2 = max2;
    properties.color_max3 = max3;
    properties.color_maxa = maxA;
}

void DGraphics::tint(Color rgba)
{
    properties.tint_color = rgba;
    properties.use_tint = true;
}

void DGraphics::tint(Color rgb, float alpha)
{
    properties.tint_color = Color(rgb.red,rgb.green,rgb.blue,static_cast<uint8_t>(alpha/properties.color_maxa));
    properties.use_tint = true;
}

void DGraphics::tint(float gray )
{
    tint(gray,properties.color_maxa);
}

void DGraphics::tint(float gray, float alpha)
{
    properties.tint_color = color(gray, alpha);
    properties.use_tint = true;
}

void DGraphics::tint(float v1, float v2, float v3)
{
    properties.tint_color = get_color(v1,v2,v3,properties.color_maxa);
    properties.use_tint = true;
}

void DGraphics::tint(float v1, float v2, float v3, float alpha)
{
    properties.tint_color = get_color(v1,v2,v3,alpha);
    properties.use_tint = true;
}


Color DGraphics::color(float grey)
{
    return color(grey,properties.color_maxa);
}

Color DGraphics::color(float grey, float alpha)
{
    uint8_t v = static_cast<uint8_t>((grey / properties.color_max1) * 255.0f);
    uint8_t a = static_cast<uint8_t>((alpha / properties.color_maxa) * 255.0f);

    Color r(v, v, v, a);

    return r;
}

Color DGraphics::color(float v1, float v2, float v3)
{
    return get_color(v1,v2,v3,properties.color_maxa);
}

Color DGraphics::color(float v1, float v2, float v3, float alpha)
{
    return get_color(v1,v2,v3,alpha);
}

float DGraphics::red(Color c)
{
    return (c.red / 255.0f) * properties.color_max1;
}

float DGraphics::green(Color c)
{
    return (c.green / 255.0f) * properties.color_max2;
}

float DGraphics::blue(Color c)
{
    return (c.blue / 255.0f) * properties.color_max3;
}

float DGraphics::alpha(Color c)
{
    return (c.alpha / 255.0f) * properties.color_maxa;
}

float DGraphics::hue(Color c)
{
    return (c.hsb().hue / 255.0f) * properties.color_max1;
}

float DGraphics::saturation(Color c)
{
    return (c.hsb().saturation / 255.0f) * properties.color_max2;
}

float DGraphics::brightness(Color c)
{
    return (c.hsb().brightness / 255.0f) * properties.color_max3;
}

void DGraphics::bezierDetail(float d)
{
    if(d > 0.0)
    {
        properties.bezier_detail = d;
    }
}

void DGraphics::noFill()
{
    properties.use_fill = false;
}

void DGraphics::noStroke()
{
    properties.use_stroke = false;
}

void DGraphics::noTint()
{
    properties.use_tint = false;
}

void DGraphics::textFont(DFont font)
{
    properties.font = font;
}

void DGraphics::strokeCap(CapStyle cap)
{
    properties.strokecap = cap;
}

void DGraphics::strokeWeight(float w)
{
    properties.stroke_weight = std::abs(w);
    properties.use_stroke = true;
}

void DGraphics::rectMode(PosMode m)
{
    properties.rectmode = m;
}

void DGraphics::ellipseMode(PosMode m)
{
    properties.ellipsemode = m;
}

void DGraphics::imageMode(PosMode m)
{
    properties.imagemode = m;
}

void DGraphics::translate(float x, float y)
{
    translate(Vector2(x,y));
}

void DGraphics::translate(const Vector2& t)
{
    transform_mat = transform_mat.translate(Vector3(t.x,-t.y,0.0f));
}

void DGraphics::rotate(float angle)
{
    rotateZ(angle);
}

void DGraphics::rotateX(float angle)
{
    transform_mat = transform_mat.rotate<Axis::X>(-angle);
}

void DGraphics::rotateY(float angle)
{
    transform_mat = transform_mat.rotate<Axis::Y>(-angle);
}

void DGraphics::rotateZ(float angle)
{
    transform_mat = transform_mat.rotate<Axis::Z>(-angle);
}

void DGraphics::scale(float s)
{
    scale(Vector2(s));
}

void DGraphics::scale(float x, float y)
{
    scale(Vector2(x,y));
}

void DGraphics::scale(const Vector2& s)
{
    transform_mat = transform_mat.scale(Vector3(s.x,s.y,1.0f));
}

void DGraphics::shearX(float a)
{
    Matrix4 m;
    m(0,1) = a;
    transform_mat = transform_mat * m;
}

void DGraphics::shearY(float a)
{
    Matrix4 m;
    m(1,0) = a;
    transform_mat = transform_mat * m;
}


void DGraphics::push()
{
    pushMatrix();
    pushStyle();
}

void DGraphics::pop()
{
    popMatrix();
    popStyle();
}

void DGraphics::applyMatrix(const Matrix4& m)
{
    transform_mat = transform_mat * m;
}

void DGraphics::pushMatrix()
{
    matrix_stack.push(transform_mat);
}

void DGraphics::popMatrix()
{
    if(matrix_stack.empty())
    {
        return;
    }

    transform_mat = matrix_stack.top();
    matrix_stack.pop();
}

void DGraphics::pushStyle()
{
    property_stack.push(properties);
}

void DGraphics::popStyle()
{
    if(property_stack.empty())
    {
        return;
    }

    properties = property_stack.top();
    property_stack.pop();
}

void DGraphics::ellipse(float x, float y, float sizex, float sizey)
{
    glUseProgram(ellipse_shader->getId());
    glUniform4f(ellipse_shader_offset_loc,x,y,sizex,sizey);
    glUniform1f(ellipse_shader_strokeWeight_loc,properties.use_stroke?properties.stroke_weight:0.0f);
    glUniform4f(ellipse_shader_strokeColor_loc,properties.stroke_color.red/255.0f,
                                                                    properties.stroke_color.green/255.0f,
                                                                    properties.stroke_color.blue/255.0f,
                                                                    properties.stroke_color.alpha/255.0f);
    glUniform4f(ellipse_shader_fillColor_loc,properties.fill_color.red/255.0f,
                                                                    properties.fill_color.green/255.0f,
                                                                    properties.fill_color.blue/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha/255.0f:0.0f);
    glUniformMatrix4fv(ellipse_shader_transform_loc,1,GL_FALSE,transform_mat.values);
    glUniformMatrix4fv(ellipse_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniform1i(ellipse_shader_posmode_loc,properties.ellipsemode);

    glEnableVertexAttribArray(ellipse_shader_vpos_loc);
    glEnableVertexAttribArray(ellipse_shader_tpos_loc);

    glVertexAttribPointer(ellipse_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(ellipse_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(ellipse_shader_vpos_loc);
    glDisableVertexAttribArray(ellipse_shader_tpos_loc);
}

void DGraphics::ellipse(const Vector2& p, const Vector2& s)
{
    ellipse(p.x,p.y,s.x,s.y);
}

void DGraphics::circle(float x, float y, float size)
{
    ellipse(x,y,size*2,size*2);
}

void DGraphics::circle(const Vector2& p, float size)
{
    circle(p.x,p.y,size);
}

void DGraphics::rect(float x, float y, float sizex, float sizey)
{
    rect(x,y,sizex,sizey,0,0,0,0);
}

void DGraphics::rect(const Vector2& p, const Vector2& s)
{
    rect(p.x,p.y,s.x,s.y);
}

void DGraphics::rect(float x, float y, float sizex, float sizey, float radii)
{
    rect(x,y,sizex,sizey,radii,radii,radii,radii);
}

void DGraphics::rect(const Vector2& p, const Vector2& s, float radii)
{
    rect(p.x,p.y,s.x,s.y,radii);
}

void DGraphics::rect(float x, float y, float sizex, float sizey, float tl, float tr, float br, float bl)
{
    glUseProgram(rect_shader->getId());
    glUniform4f(rect_shader_offset_loc,x,y,sizex,sizey);
    glUniform4f(rect_shader_radii_loc,tl,tr,br,bl);
    glUniform1f(rect_shader_strokeWeight_loc,properties.use_stroke?properties.stroke_weight:0.0f);
    glUniform4f(rect_shader_strokeColor_loc,properties.stroke_color.red/255.0f,
                                                                    properties.stroke_color.green/255.0f,
                                                                    properties.stroke_color.blue/255.0f,
                                                                    properties.stroke_color.alpha/255.0f);
    glUniform4f(rect_shader_fillColor_loc,properties.fill_color.red/255.0f,
                                                                    properties.fill_color.green/255.0f,
                                                                    properties.fill_color.blue/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha/255.0f:0.0f);
    glUniformMatrix4fv(rect_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniformMatrix4fv(rect_shader_transform_loc,1,GL_FALSE,transform_mat.values);
    glUniform1i(rect_shader_posmode_loc,properties.rectmode);

    glEnableVertexAttribArray(rect_shader_vpos_loc);
    glEnableVertexAttribArray(rect_shader_tpos_loc);

    glVertexAttribPointer(rect_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(rect_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(rect_shader_vpos_loc);
    glDisableVertexAttribArray(rect_shader_tpos_loc);
}

void DGraphics::rect(const Vector2& p, const Vector2& s, float tl, float tr, float br, float bl)
{
    rect(p.x,p.y,s.x,s.y,tl,tr,br,bl);
}

void DGraphics::square(float x, float y, float size)
{
    rect(x,y,size,size);
}

void DGraphics::square(const Vector2& p, float size)
{
    square(p.x,p.y,size);
}

void DGraphics::triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    triangle_verts[0] = x1;
    triangle_verts[1] = -y1;
    triangle_verts[2] = x2;
    triangle_verts[3] = -y2;
    triangle_verts[4] = x3;
    triangle_verts[5] = -y3;

    glUseProgram(triangle_shader->getId());
    glUniform1f(triangle_shader_strokeWeight_loc,properties.use_stroke?properties.stroke_weight:0.0f);
    glUniform1fv(triangle_shader_bpos_loc,6,triangle_verts);
    glUniform4f(triangle_shader_strokeColor_loc,properties.stroke_color.red/255.0f,
                                                                    properties.stroke_color.green/255.0f,
                                                                    properties.stroke_color.blue/255.0f,
                                                                    properties.stroke_color.alpha/255.0f);
    glUniform4f(triangle_shader_fillColor_loc,properties.fill_color.red/255.0f,
                                                                    properties.fill_color.green/255.0f,
                                                                    properties.fill_color.blue/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha/255.0f:0.0f);
                                                                    
    glUniformMatrix4fv(triangle_shader_transform_loc,1,GL_FALSE,transform_mat.values);
    glUniformMatrix4fv(triangle_shader_view_loc,1,GL_FALSE,view_mat.values);

    glEnableVertexAttribArray(triangle_shader_vpos_loc);


    glVertexAttribPointer(triangle_shader_vpos_loc,2,GL_FLOAT,false,0, triangle_verts);

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableVertexAttribArray(triangle_shader_vpos_loc);
}

void DGraphics::triangle(const Vector2& p1,const Vector2& p2,const Vector2& p3)
{
    triangle(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y);
}

void DGraphics::line(float x1, float y1, float x2, float y2)
{
    glUseProgram(line_shader->getId());
    glUniform4f(line_shader_points_loc,x1,y1,x2,y2);
    glUniform4f(line_shader_strokeColor_loc,properties.stroke_color.red/255.0f,
                                                                    properties.stroke_color.green/255.0f,
                                                                    properties.stroke_color.blue/255.0f,
                                                                    properties.stroke_color.alpha/255.0f);
    glUniformMatrix4fv(line_shader_transform_loc,1,GL_FALSE,transform_mat.values);
    glUniformMatrix4fv(line_shader_view_loc,1,GL_FALSE,view_mat.values);
    
    glUniform2f(line_shader_strokeWeight_loc,
        properties.use_stroke?properties.stroke_weight:0.0f,
        float(properties.strokecap));

    glEnableVertexAttribArray(line_shader_vpos_loc);
    glEnableVertexAttribArray(line_shader_tpos_loc);


    glVertexAttribPointer(line_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(line_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square_line);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(line_shader_tpos_loc);
    glDisableVertexAttribArray(line_shader_vpos_loc);
}

void DGraphics::line(const Vector2& p1,const Vector2& p2)
{
    line(p1.x,p1.y,p2.x,p2.y);
}

void DGraphics::point(float x, float y)
{
    line(x,y,x,y);
}

void DGraphics::point(const Vector2& p)
{
    line(p,p);
}

void DGraphics::render_texture(unsigned int texture, float x, float y, float width, float height, bool flip)
{
    glUseProgram(image_shader->getId());
    glUniform4f(image_shader_offset_loc,x,y,width,height);
   
    glUniformMatrix4fv(image_shader_transform_loc,1,GL_FALSE,transform_mat.values);
    glUniformMatrix4fv(image_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniform1i(image_shader_posmode_loc,properties.imagemode);

    glUniform1i(image_shader_use_tint_loc,properties.use_tint);
    if(properties.use_tint)
    {
        glUniform4f(image_shader_tint_loc,properties.tint_color.red/255.0f,
                                          properties.tint_color.green/255.0f,
                                          properties.tint_color.blue/255.0f,
                                          properties.tint_color.alpha/255.0f);
    }

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(image_shader_tex_loc,0);

    glEnableVertexAttribArray(image_shader_vpos_loc);
    glEnableVertexAttribArray(image_shader_tpos_loc);

    glVertexAttribPointer(image_shader_tpos_loc,2,GL_FLOAT,false,0, coords_img);

    if(!flip)
    {
        glVertexAttribPointer(image_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square);
    }
    else
    {
        glVertexAttribPointer(image_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square_flipped);
    }

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(image_shader_vpos_loc);
    glDisableVertexAttribArray(image_shader_tpos_loc);
}

void DGraphics::image(const DImage& img, float x, float y)
{
    image(img,x,y,static_cast<float>(img.m_width),static_cast<float>(img.m_height));
}

void DGraphics::image(const DImage& img, const Vector2& p)
{
    image(img,p.x,p.y);
}

void DGraphics::image(const DImage& img, float x, float y, float w, float h)
{
    render_texture(img.m_texture,x,y,w,h);
}

void DGraphics::image(const DImage& img, const Vector2& p, const Vector2& s)
{
    image(img,p.x,p.y,s.x,s.y);
}

void DGraphics::image(const DGraphics& target, float x, float y )
{
    image(target,x,y,static_cast<float>(target.buffer_width),static_cast<float>(target.buffer_height));
}

void DGraphics::image(const DGraphics& target, const Vector2& p)
{
    image(target,p.x,p.y,static_cast<float>(target.buffer_width),static_cast<float>(target.buffer_height));
}

void DGraphics::image(const DGraphics& target, float x, float y, float w, float h)
{
    render_texture(target.texture_id,x,y,w,h,true);
}

void DGraphics::image(const DGraphics& target, const Vector2& p, const Vector2& s)
{
    image(target,p.x,p.y,s.x,s.y);
}

void DGraphics::quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    float t_abc = (y1-y2)*x3 + (x2-x1)*y3 + (x1*y2 - x2*y1);
    float t_abd = (y1-y2)*x4 + (x2-x1)*y4 + (x1*y2 - x2*y1);
    float t_bcd = (y2-y3)*x4 + (x3-x2)*y4 + (x2*y3 - x3*y2);
    float t_cad = (y3-y1)*x4 + (x1-x3)*y4 + (x3*y1 - x1*y3);

    bool sig = t_abc > 0;
    bool a;
    bool b;
    bool c;

    if(sig)
    {
        a = t_abd > 0;
        b = t_bcd > 0;
        c = t_cad > 0;

    }
    else
    {
        a = t_abd < 0;
        b = t_bcd < 0;
        c = t_cad < 0;
    }
    
    if(a + b + c == 2)
    {
        if(a && b)
        {
            //convex 1
            
            quad_verts[0] = x2;
            quad_verts[1] = -y2;
            quad_verts[6] = x4;
            quad_verts[7] = -y4;

            quad_verts[2] = x1;
            quad_verts[3] = -y1;
            quad_verts[4] = x3;
            quad_verts[5] = -y3;

            quad_verts[8]  = x3;
            quad_verts[9]  = -y3;
            quad_verts[10] = x1;
            quad_verts[11] = -y1;
        }
        else if(a && c)
        {
            //convex 2

            quad_verts[0] = x2;
            quad_verts[1] = -y2;
            quad_verts[6] = x3;
            quad_verts[7] = -y3;

            quad_verts[2] = x1;
            quad_verts[3] = -y1;
            quad_verts[4] = x4;
            quad_verts[5] = -y4;
            
            quad_verts[8]  = x4;
            quad_verts[9]  = -y4;
            quad_verts[10] = x1;
            quad_verts[11] = -y1;
        }
        else
        {
            //convex 3

            quad_verts[0] = x4;
            quad_verts[1] = -y4;
            quad_verts[6] = x3;
            quad_verts[7] = -y3;

            quad_verts[2] = x1;
            quad_verts[3] = -y1;
            quad_verts[4] = x2;
            quad_verts[5] = -y2;
            
            quad_verts[8]  = x1;
            quad_verts[9]  = -y1;
            quad_verts[10] = x2;
            quad_verts[11] = -y2;
        }
    }
    else
    {
        if((a && b && c) || (!a && !b && c))
        {
            //concave 1

            quad_verts[0] = x1;
            quad_verts[1] = -y1;
            quad_verts[2] = x4;
            quad_verts[3] = -y4;
            quad_verts[4] = x2;
            quad_verts[5] = -y2;

            quad_verts[6]  = x3;
            quad_verts[7]  = -y3;
            quad_verts[8]  = x2;
            quad_verts[9]  = -y2;
            quad_verts[10] = x4;
            quad_verts[11] = -y4;
        }
        else if(a || b)
        {
            //concave 2

            quad_verts[0] = x2;
            quad_verts[1] = -y2;
            quad_verts[2] = x3;
            quad_verts[3] = -y3;
            quad_verts[4] = x1;
            quad_verts[5] = -y1;

            quad_verts[6]  = x4;
            quad_verts[7]  = -y4;
            quad_verts[8]  = x3;
            quad_verts[9]  = -y3;
            quad_verts[10] = x1;
            quad_verts[11] = -y1;
        }
    }


    glUseProgram(quad_shader->getId());
    glUniform1f(quad_shader_strokeWeight_loc,properties.use_stroke?properties.stroke_weight:0.0f);
    glUniform1fv(quad_shader_bpos_loc,12,quad_verts);
    glUniform4f(quad_shader_strokeColor_loc,properties.stroke_color.red/255.0f,
                                                                    properties.stroke_color.green/255.0f,
                                                                    properties.stroke_color.blue/255.0f,
                                                                    properties.stroke_color.alpha/255.0f);
    glUniform4f(quad_shader_fillColor_loc,properties.fill_color.red/255.0f,
                                                                    properties.fill_color.green/255.0f,
                                                                    properties.fill_color.blue/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha/255.0f:0.0f);
    glUniformMatrix4fv(quad_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniformMatrix4fv(quad_shader_transform_loc, 1, GL_FALSE, transform_mat.values);

    glEnableVertexAttribArray(quad_shader_vpos_loc);

    glVertexAttribPointer(quad_shader_vpos_loc,2,GL_FLOAT,false,0, quad_verts);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(quad_shader_vpos_loc);
}

void DGraphics::quad(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4)
{
    quad(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y);
}

void DGraphics::shape(const DShape& s, float x, float y, float w, float h)
{
    float we = properties.stroke_weight;
    Color c = properties.stroke_color;

    properties.stroke_weight = s.impl->strokeWeight;
    properties.stroke_color = s.impl->strokeColor;
    Vector2 posv = {x,y};
    Vector2 scalev = {w,h};

    for(const Path& pt : s.impl->paths)
    {
        //This is supposed to be faster, since there is only a single draw call per path
        //but instead it can be many times slower.
        //Need more testing, but problem seems to be with the draw call.
        #if 1
        
        generate_cubic_bezier_path(reinterpret_cast<const Vector2*>(pt.points.data()),pt.points.size(),x,-y,w,h,4);
        render_bezier_buffer();

        #else

        for (int i = 0; i < pt.points.size()-1; i += 3) 
        {
            const Vector2* p = &pt.points[i];
            bezier(p[0]*scalev+posv,p[3]*scalev+posv,p[1]*scalev+posv,p[2]*scalev+posv);
        }

        #endif
    }

    properties.stroke_weight = we;
    properties.stroke_color = c;

    for(const DShape& ss : s.impl->children)
    {
        shape(ss,x,y,w,h);
    }
}

bool DGraphics::save(const std::string& filename, ImageFormat format) const
{
    if(buffer_id == static_cast<unsigned int>(-1) || buffer_height == 0 || buffer_width == 0) return false;

    unsigned char* data = new unsigned char[buffer_width*buffer_height*4];
    glBindTexture(GL_TEXTURE_2D,texture_id);

    glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

    int result = 0;

    stbi_flip_vertically_on_write(1);

    switch (format)
    {
        case ImageFormat::PNG:
        {
            std::string name = filename + ".png";
            result = stbi_write_png(name.data(),buffer_width,buffer_height,4,data,buffer_width*4);
            break;
        }
        case ImageFormat::JPG:
        {
            std::string name = filename + ".jpg";
            result = stbi_write_jpg(name.data(),buffer_width,buffer_height,4,data,100);
            break;
        }
        case ImageFormat::TGA:
        {
            std::string name = filename + ".tga";
            result = stbi_write_tga(name.data(),buffer_width,buffer_height,4,data);
            break;
        }
        case ImageFormat::BMP:
        {
            std::string name = filename + ".bmp";
            result = stbi_write_bmp(name.data(),buffer_width,buffer_height,4,data);
            break;
        }
    }

    delete[] data;

    return result == 1;
}

bool DGraphics::saveFrame(const std::string& basename, ImageFormat format) const
{
    bool custom = false;
    unsigned i = 0;
    for(; i < basename.size(); ++i)
    {
        if(basename[i] == '#')
        {
            custom = true;
            break;
        }
    }

    std::stringstream ns;

    if(!custom)
    {
        ns << basename;
        ns << '_';
        ns << std::setfill('0') << std::setw(5);
        ns << frameCount;
    }
    else
    {
        unsigned st = i;

        for(; i < basename.size(); ++i)
        {
            if(basename[i] != '#')
            {
                break;
            }
        }

        unsigned long long frameN = frameCount;
        unsigned int d = 0;
        while (frameN) {
            frameN /= 10;
            d++;
        }

        unsigned count = i - st;

        if(d > count)
        {
            return false;
        }

        ns << std::string(basename.begin(),basename.begin()+st);
        ns << std::setfill('0') << std::setw(count);
        ns << frameCount;
        ns << std::string(basename.begin()+st+count,basename.end());
    }

    return save(ns.str(),format);
}

void DGraphics::text(const std::string& txt, float x, float y)
{
    text(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(txt),x,y);
}

void DGraphics::text(const std::string& txt, const Vector2& p)
{
    text(txt,p.x,p.y);
}

void DGraphics::text(const std::wstring& txt, float x, float y)
{
    if(!properties.font.valid())
    {
        dbg::error("No valid font set!");
        return;
    }

    if(!txt.size())
    {
        return;
    }

    txt_vert_buffer.clear();
    txt_texc_buffer.clear();

    auto& chars = properties.font.impl->chars;

    float height = -properties.font.impl->char_height;
    float row_s = properties.font.impl->row_spacing;
    float char_s = properties.font.impl->char_spacing;
    float bl = properties.font.impl->baseline;

    //Assume 'missing character' to always be present
    auto* _c = &(chars[L'\0']);

    const auto* first = _c;

    auto f = chars.find(txt[0]);

    if(f != chars.end())
    {
        first = &f->second;
    }

    //align such that origin is the top-left corner of the 1st characater
    float xloc = x - first->bearing_x;
    float yloc = -y + height + bl;

    for(unsigned i = 0; i < txt.length(); ++i)
    {   
        const auto* c = _c;

        bool nl = false;

        if(txt[i] == '\n')
        {
            nl = true;

            ++i;

            if(i >= txt.length())
            {
                break;
            }
        }
        
        f = chars.find(txt[i]);

        if(f != chars.end())
        {
            c = &f->second;
        }
        else
        {
            if(properties.font.impl->load_additional_char(txt[i]))
            {
                properties.font.impl->apply_texture();
            }

            auto& nc = chars[txt[i]];
            c = &nc;
        }
        
        if(nl)
        {
            xloc = x - c->bearing_x;
            yloc += height - row_s + bl;
        }

        //calculate vertex positions from character metrics
        float x1 = xloc + c->bearing_x;
        float y1 = yloc - c->bearing_y + bl;
        float x2 = xloc + c->bearing_x + c->width;
        float y2 = yloc - c->bearing_y - c->height + bl;

        txt_vert_buffer.insert(txt_vert_buffer.end(),
        {
            x1, y2,
            x2, y2,
            x1, y1,

            x2, y2,
            x2, y1,
            x1, y1,
        });

        //calculate texture coordinates from character metrics
        float tx1 = c->tx_pos_x;
        float ty1 = c->tx_pos_y;
        float tx2 = c->tx_pos_x + c->tx_width;
        float ty2 = c->tx_pos_y + c->tx_height;

        txt_texc_buffer.insert(txt_texc_buffer.end(),
        {
            tx1,ty2,
            tx2,ty2,
            tx1,ty1,

            tx2,ty2,
            tx2,ty1,
            tx1,ty1,
        });

        //move cursor
        xloc += c->advance_x/64.0f + char_s;
    }

    glUseProgram(text_shader->getId());
    glUniform4f(text_shader_fillColor_loc,properties.fill_color.red/255.0f,
                                                                    properties.fill_color.green/255.0f,
                                                                    properties.fill_color.blue/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha/255.0f:0.0f);
    glUniformMatrix4fv(text_shader_transform_loc,1,GL_FALSE,transform_mat.values);
    glUniformMatrix4fv(text_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniform1i(text_shader_posmode_loc,properties.rectmode);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, properties.font.impl->texture_id);
    glUniform1i(text_shader_texture_loc,0);

    glEnableVertexAttribArray(text_shader_vpos_loc);
    glEnableVertexAttribArray(text_shader_tpos_loc);

    glVertexAttribPointer(rect_shader_tpos_loc,2,GL_FLOAT,false,0, txt_texc_buffer.data());
    glVertexAttribPointer(rect_shader_vpos_loc,2,GL_FLOAT,false,0, txt_vert_buffer.data());

    glDrawArrays(GL_TRIANGLES,0,static_cast<int>(txt_vert_buffer.size())/2);

    glDisableVertexAttribArray(rect_shader_vpos_loc);
    glDisableVertexAttribArray(rect_shader_tpos_loc);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void DGraphics::text(const std::wstring& txt, const Vector2& p)
{
    text(txt,p.x,p.y);
}

Vector2 bezier_bezierCubic(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float t)
{
    float f1 = 1.0f-t;
    return f1*f1*f1*a + 
    3.0f*f1*f1*t*b + 
    3.0f*f1*t*t*c + 
    t*t*t*d;
}

Vector2 bezier_bezierQuadratic(Vector2 p0, Vector2 p1,Vector2 p2, float t)
{
    float t1 = 1.0f-t;
    return  t1*(t1*p0+t*p1)+t*(t1*p1+t*p2);
}

//stride = bytes between elements in array
//for example, if you cast a Vector2 array to Vector2 array here, you want stride of 4 (sizeof(Vector2)-sizeof(Vector2))
void DGraphics::generate_cubic_bezier_path(const struct Vector2* points, size_t count, float xoff, float yoff, float xscale, float yscale, unsigned int stride)
{
    bezier_buffer.clear();

    float s = 1.0f/properties.bezier_detail;
    float t = 1.0f;

    Vector2 a;
    Vector2 d;
    Vector2 b;
    Vector2 c;

    size_t offset = stride+sizeof(Vector2);
    const uint8_t* dataptr = reinterpret_cast<const uint8_t*>(points);

    for(size_t i = 0; i < count-1; i += 3)
    {
        a = *reinterpret_cast<const Vector2*>(dataptr);
        b = *reinterpret_cast<const Vector2*>(dataptr+=offset);
        c = *reinterpret_cast<const Vector2*>(dataptr+=offset);
        d = *reinterpret_cast<const Vector2*>(dataptr+=offset);

        a.y = -a.y * yscale + yoff;
        b.y = -b.y * yscale + yoff;
        c.y = -c.y * yscale + yoff;
        d.y = -d.y * yscale + yoff;

        a.x = a.x * xscale + xoff;
        b.x = b.x * xscale + xoff;
        c.x = c.x * xscale + xoff;
        d.x = d.x * xscale + xoff;

        t -= 1.0f;

        while(t < 1.0f)
        {
            bezier_buffer.push_back(bezier_bezierCubic(a,b,c,d,t));
            t += s;
        }
    }
    bezier_buffer.push_back(bezier_bezierCubic(a,b,c,d,1.0f));
}

void DGraphics::generate_quadratic_bezier_path(const struct Vector2* points, size_t count, float xoff, float yoff, float xscale, float yscale, unsigned int stride)
{
    bezier_buffer.clear();

    float s = 1.0f/properties.bezier_detail;
    float t = 1.0f;

    Vector2 p0;
    Vector2 p1;
    Vector2 p2;

    size_t offset = stride+sizeof(Vector2);
    const uint8_t* dataptr = reinterpret_cast<const uint8_t*>(points);

    for(size_t i = 0; i < count-1; i += 2)
    {
        p0 = *reinterpret_cast<const Vector2*>(dataptr);
        p1 = *reinterpret_cast<const Vector2*>(dataptr+=offset);
        p2 = *reinterpret_cast<const Vector2*>(dataptr+=offset);

        p0.y = -p0.y * yscale + yoff;
        p1.y = -p1.y * yscale + yoff;
        p2.y = -p2.y * yscale + yoff;

        p0.x = p0.x * xscale + xoff;
        p1.x = p1.x * xscale + xoff;
        p2.x = p2.x * xscale + xoff;

        t -= 1.0f;
        while(t < 1.0f)
        {
            bezier_buffer.push_back(bezier_bezierQuadratic(p0,p1,p2,t));
            t += s;
        }
    }
    bezier_buffer.push_back(bezier_bezierQuadratic(p0,p1,p2,1.0f));
}

void DGraphics::render_bezier_buffer()
{
    static std::vector<Vector2> mesh;

    mesh.clear();

    float stroke2 = (properties.stroke_weight/2);

    Vector2 dir = (bezier_buffer[1] - bezier_buffer[0]);
    dir = dir / dir.mag();
    Vector2 normal = {-dir.y,dir.x};
    Vector2 s_dist = (normal * stroke2);

    mesh.push_back(bezier_buffer[0] + s_dist);
    mesh.push_back(bezier_buffer[0] - s_dist);

    Vector2 last_dir = dir;

    for(size_t i = 1; i < bezier_buffer.size()-1; ++i)
    {
        dir = (bezier_buffer[i+1] - bezier_buffer[i]);
        dir = dir / dir.mag();
        Vector2 ddir = lerp(dir, last_dir,0.5);
        normal = {-ddir.y,ddir.x};
        s_dist = (normal * stroke2);

        mesh.push_back(bezier_buffer[i] + s_dist);
        mesh.push_back(bezier_buffer[i] - s_dist);

        last_dir = dir;
    }

    dir = (bezier_buffer[bezier_buffer.size()-1] - bezier_buffer[bezier_buffer.size()-2]);
    dir = dir / dir.mag();
    normal = {-dir.y,dir.x};
    s_dist = (normal * stroke2);

    mesh.push_back(bezier_buffer[bezier_buffer.size()-1] + s_dist);
    mesh.push_back(bezier_buffer[bezier_buffer.size()-1] - s_dist);

    glUseProgram(generic_colored_shader->getId());

    glUniformMatrix4fv(generic_colored_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniformMatrix4fv(generic_colored_shader_transform_loc,1,GL_FALSE,transform_mat.values);
    glUniform4f(generic_colored_shader_color_loc,properties.stroke_color.red/255.0f,
                                                properties.stroke_color.green/255.0f,
                                                properties.stroke_color.blue/255.0f,
                                                properties.stroke_color.alpha/255.0f);


    glEnableVertexAttribArray(generic_colored_shader_vpos_loc);
    glVertexAttribPointer(generic_colored_shader_vpos_loc,2,GL_FLOAT,false,0, mesh.data());

    glDrawArrays(GL_TRIANGLE_STRIP,0, static_cast<int>(mesh.size()));

    glDisableVertexAttribArray(generic_colored_shader_vpos_loc);

    if(properties.strokecap == CapStyle::ROUND)
    {
        point(bezier_buffer[0].x,-bezier_buffer[0].y);
        point(bezier_buffer[bezier_buffer.size()-1].x,-bezier_buffer[bezier_buffer.size()-1].y);
    }
}

void DGraphics::bezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2)
{
    static Vector2 pp[4];

    pp[0].x = x1;
    pp[0].y = y1;
    pp[3].x = x2;
    pp[3].y = y2;
    pp[1].x = cx1;
    pp[1].y = cy1;
    pp[2].x = cx2;
    pp[2].y = cy2;

    generate_cubic_bezier_path(pp,4);
    render_bezier_buffer();
}

void DGraphics::bezier(const Vector2& p1, const Vector2& p2, const Vector2& cp1, const Vector2& cp2)
{
    bezier(p1.x,p1.y,p2.x,p2.y,cp1.x,cp1.y,cp2.x,cp2.y);
}

void DGraphics::bezier(float x1, float y1, float x2, float y2, float cx, float cy)
{
    static Vector2 pp[3];

    pp[0].x = x1;
    pp[0].y = y1;
    pp[1].x = cx;
    pp[1].y = cy;
    pp[2].x = x2;
    pp[2].y = y2;

    generate_quadratic_bezier_path(pp,3);
    render_bezier_buffer();
}

void DGraphics::bezier(const Vector2& p1, const Vector2& p2, const Vector2& cp)
{
    bezier(p1.x,p1.y,p2.x,p2.y,cp.x,cp.y);
}

GraphicsProperties DGraphics::getStyle()
{
    return properties;
}

DImage DGraphics::toImage() const
{
    size_t w4 = buffer_width*4;
    Color* data = static_cast<Color*>(malloc(w4*buffer_height));

    glBindTexture(GL_TEXTURE_2D,texture_id);
    glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

    Color* tmp = static_cast<Color*>(malloc(w4));
    Color* end = data + (buffer_height-1)*w4;

    for(unsigned i = 0; i < buffer_height/2; ++i)
    {
        Color* first = data+(w4*i);
        Color* last = end-(w4*i);
        std::memcpy(tmp,first,w4);
        std::memcpy(first,last,w4);
        std::memcpy(last,tmp,w4);
    }
    free(tmp);

    unsigned int texid = DImage::generateTexture(buffer_width,buffer_height,data);

    return DImage(data,texid,buffer_width,buffer_height);
}

void DGraphics::filter(const DFilter& f)
{
    if(!f.impl)
    {
        return;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER,filter_buffer_id);

    glUseProgram(f.getProgram());

    glUniform2f(f.impl->source_size_location,static_cast<float>(buffer_width),static_cast<float>(buffer_height));

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(f.impl->source_location,0);

    f.impl->upload_all_uniforms();

    glEnableVertexAttribArray(f.impl->vertex_pos_location);

    glVertexAttribPointer(f.impl->vertex_pos_location,2,GL_FLOAT,false,0, view_vertex);
    
    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(f.impl->vertex_pos_location);

    glBindFramebuffer(GL_FRAMEBUFFER,buffer_id);


    clear();

    glUseProgram(Application::GetInstance()->application_shader->getId());
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,filter_texture_id);
    glUniform1i(Application::GetInstance()->application_shader_tex_uniform,0);

    glEnableVertexAttribArray(Application::GetInstance()->application_shader_vertpos_attrib);
    glEnableVertexAttribArray(Application::GetInstance()->application_shader_texc_attrib);

    glVertexAttribPointer(Application::GetInstance()->application_shader_texc_attrib,2,GL_FLOAT,false,0, coords_view);
    glVertexAttribPointer(Application::GetInstance()->application_shader_vertpos_attrib,2,GL_FLOAT,false,0, view_vertex);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(Application::GetInstance()->application_shader_vertpos_attrib);
    glDisableVertexAttribArray(Application::GetInstance()->application_shader_texc_attrib);
    
    glBindTexture(GL_TEXTURE_2D,0);
}

void DGraphics::filter(filters f, float param)
{
    switch (f)
    {
        case filters::PIXELATE:
        {
            DFilter& ft = Application::GetInstance()->stock_filters[f];
            ft.setUniform("scale",param);
            filter(ft);
            break;
        }

        case filters::THRESHOLD:
        {
            DFilter& ft = Application::GetInstance()->stock_filters[f];
            ft.setUniform("threshold",param);
            filter(ft);
            break;
        }

        case filters::INVERT:
        case filters::GREY:
        {
            filter(Application::GetInstance()->stock_filters[f]);
            break;
        }
    }
}

void DGraphics::clip(int x1, int y1, int x2, int y2)
{
    properties.use_clip = true;
    properties.clip_x1 = x1;
    properties.clip_x2 = x2;
    properties.clip_y1 = y1;
    properties.clip_y2 = y2;

    glEnable(GL_SCISSOR_TEST);
    glScissor(x1,buffer_height-y1-y2,x2,y2);
}

void DGraphics::noClip()
{
    properties.use_clip = false;
    glDisable(GL_SCISSOR_TEST);
}

DGraphics& DGraphics::operator=(DGraphics&& other)
{
    if(buffer_id != static_cast<unsigned int>(-1))
    {
        glDeleteFramebuffers(1,&buffer_id);
    }

    if(texture_id != 0)
    {
        glDeleteTextures(1,&texture_id);
    }

    buffer_id = other.buffer_id;
    texture_id = other.texture_id;
    buffer_width = other.buffer_width;
    buffer_height = other.buffer_height;

    other.buffer_id = static_cast<unsigned int>(-1);
    other.texture_id = 0;

    properties = std::move(other.properties);
    transform_mat = other.transform_mat;
    view_mat = other.view_mat;
    matrix_stack = std::move(other.matrix_stack);
    property_stack = std::move(other.property_stack);

    ellipse_shader = std::move(other.ellipse_shader);
    rect_shader = std::move(other.rect_shader);
    triangle_shader = std::move(other.triangle_shader);
    line_shader = std::move(other.line_shader);
    image_shader = std::move(other.image_shader);
    quad_shader = std::move(other.quad_shader);
    text_shader = std::move(other.text_shader);
    generic_colored_shader = std::move(other.generic_colored_shader);
    
    ellipse_shader_offset_loc = other.ellipse_shader_offset_loc;
    ellipse_shader_strokeWeight_loc = other.ellipse_shader_strokeWeight_loc;
    ellipse_shader_strokeColor_loc = other.ellipse_shader_strokeColor_loc;
    ellipse_shader_fillColor_loc = other.ellipse_shader_fillColor_loc;
    ellipse_shader_transform_loc = other.ellipse_shader_transform_loc;
    ellipse_shader_view_loc = other.ellipse_shader_view_loc;
    ellipse_shader_posmode_loc = other.ellipse_shader_posmode_loc;
    ellipse_shader_vpos_loc = other.ellipse_shader_vpos_loc;
    ellipse_shader_tpos_loc = other.ellipse_shader_tpos_loc;
    rect_shader_offset_loc = other.rect_shader_offset_loc;
    rect_shader_strokeWeight_loc = other.rect_shader_strokeWeight_loc;
    rect_shader_strokeColor_loc = other.rect_shader_strokeColor_loc;
    rect_shader_fillColor_loc = other.rect_shader_fillColor_loc;
    rect_shader_transform_loc = other.rect_shader_transform_loc;
    rect_shader_view_loc = other.rect_shader_view_loc;
    rect_shader_posmode_loc = other.rect_shader_posmode_loc;
    rect_shader_radii_loc = other.rect_shader_radii_loc;
    rect_shader_vpos_loc = other.rect_shader_vpos_loc;
    rect_shader_tpos_loc = other.rect_shader_tpos_loc;
    triangle_shader_strokeWeight_loc = other.triangle_shader_strokeWeight_loc;
    triangle_shader_strokeColor_loc = other.triangle_shader_strokeColor_loc;
    triangle_shader_fillColor_loc = other.triangle_shader_fillColor_loc;
    triangle_shader_bpos_loc = other.triangle_shader_bpos_loc;
    triangle_shader_transform_loc = other.triangle_shader_transform_loc;
    triangle_shader_view_loc = other.triangle_shader_view_loc;
    triangle_shader_vpos_loc = other.triangle_shader_vpos_loc;
    line_shader_points_loc = other.line_shader_points_loc;
    line_shader_strokeWeight_loc = other.line_shader_strokeWeight_loc;
    line_shader_strokeColor_loc = other.line_shader_strokeColor_loc;
    line_shader_transform_loc = other.line_shader_transform_loc;
    line_shader_view_loc = other.line_shader_view_loc;
    line_shader_vpos_loc = other.line_shader_vpos_loc;
    line_shader_tpos_loc = other.line_shader_tpos_loc;
    image_shader_offset_loc = other.image_shader_offset_loc;
    image_shader_tint_loc = other.image_shader_tint_loc;
    image_shader_use_tint_loc = other.image_shader_use_tint_loc;
    image_shader_posmode_loc = other.image_shader_posmode_loc;
    image_shader_tex_loc = other.image_shader_tex_loc;
    image_shader_transform_loc = other.image_shader_transform_loc;
    image_shader_view_loc = other.image_shader_view_loc;
    image_shader_vpos_loc = other.image_shader_vpos_loc;
    image_shader_tpos_loc = other.image_shader_tpos_loc;
    quad_shader_strokeWeight_loc = other.quad_shader_strokeWeight_loc;
    quad_shader_strokeColor_loc = other.quad_shader_strokeColor_loc;
    quad_shader_fillColor_loc = other.quad_shader_fillColor_loc;
    quad_shader_bpos_loc = other.quad_shader_bpos_loc;
    quad_shader_transform_loc = other.quad_shader_transform_loc;
    quad_shader_view_loc = other.quad_shader_view_loc;
    quad_shader_vpos_loc = other.quad_shader_vpos_loc;
    text_shader_texture_loc = other.text_shader_texture_loc;
    text_shader_posmode_loc = other.text_shader_posmode_loc;
    text_shader_fillColor_loc = other.text_shader_fillColor_loc;
    text_shader_transform_loc = other.text_shader_transform_loc;
    text_shader_view_loc = other.text_shader_view_loc;
    text_shader_vpos_loc = other.text_shader_vpos_loc;
    text_shader_tpos_loc = other.text_shader_tpos_loc;
    generic_colored_shader_color_loc = other.generic_colored_shader_color_loc;
    generic_colored_shader_transform_loc = other.generic_colored_shader_transform_loc;
    generic_colored_shader_view_loc = other.generic_colored_shader_view_loc;
    generic_colored_shader_vpos_loc = other.generic_colored_shader_vpos_loc;

    return *this;
}

float to_0range(float v, float max)
{
    while ((v += max) < 0);
    while ((v -= max) > max);
    return v;
}

Color DGraphics::get_rgba(float r, float g, float b, float a)
{
    r = to_0range(r,properties.color_max1);
    g = to_0range(g,properties.color_max2);
    b = to_0range(b,properties.color_max3);
    a = to_0range(a,properties.color_maxa);
    
    uint8_t rv = static_cast<uint8_t>((r / properties.color_max1)*255.0f);
    uint8_t gv = static_cast<uint8_t>((g / properties.color_max2)*255.0f);
    uint8_t bv = static_cast<uint8_t>((b / properties.color_max3)*255.0f);
    uint8_t av = static_cast<uint8_t>((a / properties.color_maxa)*255.0f);

    return Color(rv,gv,bv,av);
}

Color DGraphics::get_hsba(float h, float s, float b, float a)
{
    h = to_0range(h,properties.color_max1);
    s = to_0range(s,properties.color_max2);
    b = to_0range(b,properties.color_max3);
    a = to_0range(a,properties.color_maxa);
    
    float hv = (h / properties.color_max1) * 360.0f;
    float sv = (s / properties.color_max2) * 100.0f;
    float bv = (b / properties.color_max3) * 100.0f;
    float av = (a / properties.color_maxa) * 100.0f;

    return HSBColor(hv,sv,bv,av).rgb();
}

Color DGraphics::get_color(float v1, float v2, float v3, float a)
{
    if(properties.colormode == ColorMode::RGB)
    {
        return get_rgba(v1,v2,v3,a);
    }
    else
    {
        return get_hsba(v1,v2,v3,a);
    }
}

unsigned int DGraphics::get_texture_id()
{
    return texture_id;
}