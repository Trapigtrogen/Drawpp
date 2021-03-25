#include <algorithm>
#include <graphics.hpp>
#include <shader.hpp>
#include <glad/glad.h>
#include <debug.hpp>
#include <image.hpp>
#include <vector3.hpp>
#include <cstring>

#include "stb_image_write.h"

#pragma warning(push,1)
#include "nanosvg.h"
#include "nanosvgrast.h"
#pragma warning(pop)

const float primitive_square[] = 
{
    0.0f, -1.0f,
    1.0f, -1.0f,
    1.0f,  0.0f,
    0.0f, -1.0f,
    1.0f,  0.0f,
    0.0f,  0.0f,
};

const float primitive_square_line[] = 
{
    -0.5f,-0.5f,
    0.5f, -0.5f,
    0.5f,  0.5f,
    -0.5f,-0.5f,
    0.5f,  0.5f,
    -0.5f, 0.5f,
};

float coords_quad[] = 
{
    0.0f, 0.0f,
    1.0f, 0.0f, 
    1.0f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 1.0f, 
    0.0f, 1.0f, 
};

float triangle_verts[] = 
{
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
};

float quad_verts[] = 
{
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
};


#include <shaders/generic_vert.ipp>
#include <shaders/ellipse_frag.ipp>
#include <shaders/rect_frag.ipp>
#include <shaders/triangle_vert.ipp>
#include <shaders/triangle_frag.ipp>
#include <shaders/line_vert.ipp>
#include <shaders/line_frag.ipp>
#include <shaders/image_frag.ipp>
#include <shaders/quad_frag.ipp>


DGraphics::DGraphics(int width, int height)
{
    buffer_width = static_cast<unsigned int>(width);
    buffer_height = static_cast<unsigned int>(height);

    GLint prev_buffer = (GLint)-1;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_buffer);

    glGenFramebuffers(1,&buffer_id);

    glBindFramebuffer(GL_FRAMEBUFFER, buffer_id);

    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,buffer_width,buffer_height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture_id,0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        dbg::error("Failed to create framebuffer");
    }

    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &format);
    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &type);

    glBindFramebuffer(GL_FRAMEBUFFER, prev_buffer);

    init_shaders();
}

DGraphics::~DGraphics()
{
    if(buffer_id != -1)
    {
        glDeleteFramebuffers(1,&buffer_id);
    }

    if(texture_id != 0)
    {
        glDeleteTextures(1,&texture_id);
    }
}

void DGraphics::init_shaders()
{
    ellipse_shader = std::make_unique<Shader>(Shader::loadShadersFromString(generic_shader_v,ellipse_shader_f));
    
    ellipse_shader_offset_loc = glGetUniformLocation(ellipse_shader->getId(),"offset");
    ellipse_shader_strokeWeight_loc = glGetUniformLocation(ellipse_shader->getId(),"strokeWeight");
    ellipse_shader_strokeColor_loc = glGetUniformLocation(ellipse_shader->getId(),"strokeColor");                                             
    ellipse_shader_fillColor_loc = glGetUniformLocation(ellipse_shader->getId(),"fillColor");
    //ellipse_shader_transform_loc = glGetUniformLocation(ellipse_shader->getId(),"transform");
    ellipse_shader_view_loc = glGetUniformLocation(ellipse_shader->getId(),"view");
    ellipse_shader_posmode_loc = glGetUniformLocation(ellipse_shader->getId(),"posmode");
    ellipse_shader_vpos_loc = glGetAttribLocation(ellipse_shader->getId(),"pos");
    ellipse_shader_tpos_loc = glGetAttribLocation(ellipse_shader->getId(),"texpos");


    rect_shader = std::make_unique<Shader>(Shader::loadShadersFromString(generic_shader_v,rect_shader_f));
    
    rect_shader_offset_loc = glGetUniformLocation(rect_shader->getId(),"offset");
    rect_shader_strokeWeight_loc = glGetUniformLocation(rect_shader->getId(),"strokeWeight");
    rect_shader_strokeColor_loc = glGetUniformLocation(rect_shader->getId(),"strokeColor");                                             
    rect_shader_fillColor_loc = glGetUniformLocation(rect_shader->getId(),"fillColor");                                           
    rect_shader_radii_loc = glGetUniformLocation(rect_shader->getId(),"radii");
    rect_shader_view_loc = glGetUniformLocation(rect_shader->getId(),"view");
    rect_shader_posmode_loc = glGetUniformLocation(rect_shader->getId(),"posmode");
    rect_shader_vpos_loc = glGetAttribLocation(rect_shader->getId(),"pos");
    rect_shader_tpos_loc = glGetAttribLocation(rect_shader->getId(),"texpos");

    triangle_shader = std::make_unique<Shader>(Shader::loadShadersFromString(triangle_shader_v,triangle_shader_f));

    triangle_shader_strokeWeight_loc = glGetUniformLocation(triangle_shader->getId(),"strokeWeight");
    triangle_shader_strokeColor_loc = glGetUniformLocation(triangle_shader->getId(),"strokeColor");                                             
    triangle_shader_fillColor_loc = glGetUniformLocation(triangle_shader->getId(),"fillColor");
    triangle_shader_view_loc = glGetUniformLocation(triangle_shader->getId(),"view");
    triangle_shader_bpos_loc = glGetUniformLocation(triangle_shader->getId(),"bpos");
    triangle_shader_vpos_loc = glGetAttribLocation(triangle_shader->getId(),"pos");

    line_shader = std::make_unique<Shader>(Shader::loadShadersFromString(line_shader_v,line_shader_f));

    line_shader_points_loc = glGetUniformLocation(line_shader->getId(),"points");
    line_shader_strokeWeight_loc = glGetUniformLocation(line_shader->getId(),"strokeWeight");
    line_shader_strokeColor_loc = glGetUniformLocation(line_shader->getId(),"strokeColor");   
    line_shader_view_loc = glGetUniformLocation(line_shader->getId(),"view");
    line_shader_cap_loc = glGetUniformLocation(line_shader->getId(),"captype");
    line_shader_tpos_loc = glGetAttribLocation(line_shader->getId(),"texpos");
    line_shader_vpos_loc = glGetAttribLocation(line_shader->getId(),"pos");

    image_shader = std::make_unique<Shader>(Shader::loadShadersFromString(generic_shader_v,image_shader_f));
 
    image_shader_offset_loc = glGetUniformLocation(image_shader->getId(),"offset");
    image_shader_posmode_loc = glGetUniformLocation(image_shader->getId(),"posmode");
    image_shader_view_loc = glGetUniformLocation(image_shader->getId(),"view");
    image_shader_tex_loc = glGetUniformLocation(image_shader->getId(),"tex");
    image_shader_tpos_loc = glGetAttribLocation(image_shader->getId(),"texpos");
    image_shader_vpos_loc = glGetAttribLocation(image_shader->getId(),"pos");

    quad_shader = std::make_unique<Shader>(Shader::loadShadersFromString(triangle_shader_v,quad_shader_f));

    quad_shader_strokeWeight_loc = glGetUniformLocation(quad_shader->getId(),"strokeWeight");
    quad_shader_strokeColor_loc = glGetUniformLocation(quad_shader->getId(),"strokeColor");                                             
    quad_shader_fillColor_loc = glGetUniformLocation(quad_shader->getId(),"fillColor");
    quad_shader_view_loc = glGetUniformLocation(quad_shader->getId(),"view");
    quad_shader_bpos_loc = glGetUniformLocation(quad_shader->getId(),"bpos");
    quad_shader_vpos_loc = glGetAttribLocation(quad_shader->getId(),"pos");
}

void DGraphics::beginDraw()
{
    view_mat = DMatrix4::identity().translate(DVector(-1.0,1.0)).scale(DVector(2.0/buffer_width,2.0/buffer_height));
    //transform_mat = DMatrix4::identity();
    glBindFramebuffer(GL_FRAMEBUFFER,buffer_id);
    glViewport(0,0,buffer_width,buffer_height);
}

void DGraphics::endDraw()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void DGraphics::fill(Color rgba)
{
    properties.fill_color = rgba;
    properties.use_fill = true;
}

void DGraphics::fill(Color rgb, float alpha)
{
    properties.fill_color = Color(rgb.red(),rgb.green(),rgb.blue(),alpha);
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
    properties.stroke_color = Color(rgb.red(),rgb.green(),rgb.blue(),alpha);
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
    glClearColor(0.0,0.0,0.0,0.0);
    int f1,f2;
    glGetIntegerv(GL_BLEND_SRC_ALPHA,&f1);
    glGetIntegerv(GL_BLEND_DST_ALPHA,&f2);

    glBlendFunc(GL_ZERO,GL_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);

    glBlendFunc(f1,f2);
}

void DGraphics::background(Color rgba)
{
    glClearColor(rgba.red()/properties.color_max1,
                rgba.green()/properties.color_max2,
                rgba.blue()/properties.color_max3,
                rgba.alpha()/properties.color_maxa);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DGraphics::background(Color rgb, float alpha)
{
    background(Color(rgb.red(),rgb.green(),rgb.blue(),alpha));
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
    image(img,0,0,buffer_width,buffer_height);
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


Color DGraphics::color(float grey)
{
    return color(grey,properties.color_maxa);
}

Color DGraphics::color(float grey, float alpha)
{
    uint8_t v = (grey / properties.color_max1) * 255;
    uint8_t a = (alpha / properties.color_maxa) * 255;

    // Color uses main target colormode
    // Gotta do this to use local colormode
    Color r;
    std::memset(&r+1,v,3);
    reinterpret_cast<uint8_t*>(&r)[0] = a;
    r.RGB2HSB(v,v,v);

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
    return (c.red() / 255.0f) * properties.color_max1;
}

float DGraphics::green(Color c)
{
    return (c.green() / 255.0f) * properties.color_max2;
}

float DGraphics::blue(Color c)
{
    return (c.blue() / 255.0f) * properties.color_max3;
}

float DGraphics::alpha(Color c)
{
    return (c.alpha() / 255.0f) * properties.color_maxa;
}

float DGraphics::hue(Color c)
{
    return (c.hue() / 255.0f) * properties.color_max1;
}

float DGraphics::saturation(Color c)
{
    return (c.saturation() / 255.0f) * properties.color_max2;
}

float DGraphics::brightness(Color c)
{
    return (c.brightness() / 255.0f) * properties.color_max3;
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
    translate(x,y,0);
}

void DGraphics::translate(float x, float y, float z)
{
    translate({x,y,z});
}

void DGraphics::translate(const DVector& t)
{
    //transform_mat = transform_mat.translate(DVector(t.x/buffer_width,-t.y/buffer_height));
    view_mat = view_mat.translate(DVector(t.x,-t.y));
}

void DGraphics::rotate(float angle)
{
    rotateZ(angle);
}

void DGraphics::rotateX(float angle)
{
    view_mat = view_mat.rotate<Axis::X>(-angle);
}

void DGraphics::rotateY(float angle)
{
    view_mat = view_mat.rotate<Axis::Y>(-angle);
}

void DGraphics::rotateZ(float angle)
{
    //transform_mat = transform_mat.rotate<Axis::Z>(angle);
    view_mat = view_mat.rotate<Axis::Z>(-angle);
}

void DGraphics::scale(float s)
{
    scale({s,s,s});
}

void DGraphics::scale(float x, float y)
{
    scale({x,y,1});
}

void DGraphics::scale(float x, float y, float z)
{
    scale({x,y,z});
}

void DGraphics::scale(const DVector& s)
{
    //transform_mat = transform_mat.scale(s);
    view_mat = view_mat.scale(s);
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

void DGraphics::pushMatrix()
{
    matrix_stack.push(view_mat);
}

void DGraphics::popMatrix()
{
    if(matrix_stack.empty())
    {
        return;
    }

    view_mat = matrix_stack.top();
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
    glUniform4f(ellipse_shader_strokeColor_loc,properties.stroke_color.red()/255.0f,
                                                                    properties.stroke_color.green()/255.0f,
                                                                    properties.stroke_color.blue()/255.0f,
                                                                    properties.stroke_color.alpha()/255.0f);
    glUniform4f(ellipse_shader_fillColor_loc,properties.fill_color.red()/255.0f,
                                                                    properties.fill_color.green()/255.0f,
                                                                    properties.fill_color.blue()/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha()/255.0f:0.0f);
    //glUniformMatrix4fv(ellipse_shader_transform_loc,1,GL_FALSE,transform_mat.values);
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

void DGraphics::circle(float x, float y, float size)
{
    ellipse(x,y,size*2,size*2);
}

void DGraphics::rect(float x, float y, float sizex, float sizey)
{
    rect(x,y,sizex,sizey,0,0,0,0);
}

void DGraphics::rect(float x, float y, float sizex, float sizey, float radii)
{
    rect(x,y,sizex,sizey,radii,radii,radii,radii);
}

void DGraphics::rect(float x, float y, float sizex, float sizey, float tl, float tr, float br, float bl)
{
    glUseProgram(rect_shader->getId());
    glUniform4f(rect_shader_offset_loc,x,y,sizex,sizey);
    glUniform4f(rect_shader_radii_loc,tl,tr,br,bl);
    glUniform1f(rect_shader_strokeWeight_loc,properties.use_stroke?properties.stroke_weight:0.0f);
    glUniform4f(rect_shader_strokeColor_loc,properties.stroke_color.red()/255.0f,
                                                                    properties.stroke_color.green()/255.0f,
                                                                    properties.stroke_color.blue()/255.0f,
                                                                    properties.stroke_color.alpha()/255.0f);
    glUniform4f(rect_shader_fillColor_loc,properties.fill_color.red()/255.0f,
                                                                    properties.fill_color.green()/255.0f,
                                                                    properties.fill_color.blue()/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha()/255.0f:0.0f);
    glUniformMatrix4fv(rect_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniform1i(rect_shader_posmode_loc,properties.rectmode);

    glEnableVertexAttribArray(rect_shader_vpos_loc);
    glEnableVertexAttribArray(rect_shader_tpos_loc);

    glVertexAttribPointer(rect_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(rect_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(rect_shader_vpos_loc);
    glDisableVertexAttribArray(rect_shader_tpos_loc);
}

void DGraphics::square(float x, float y, float size)
{
    rect(x,y,size,size);
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
    glUniform4f(triangle_shader_strokeColor_loc,properties.stroke_color.red()/255.0f,
                                                                    properties.stroke_color.green()/255.0f,
                                                                    properties.stroke_color.blue()/255.0f,
                                                                    properties.stroke_color.alpha()/255.0f);
    glUniform4f(triangle_shader_fillColor_loc,properties.fill_color.red()/255.0f,
                                                                    properties.fill_color.green()/255.0f,
                                                                    properties.fill_color.blue()/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha()/255.0f:0.0f);
    glUniformMatrix4fv(triangle_shader_view_loc,1,GL_FALSE,view_mat.values);

    glEnableVertexAttribArray(triangle_shader_vpos_loc);


    glVertexAttribPointer(triangle_shader_vpos_loc,2,GL_FLOAT,false,0, triangle_verts);

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableVertexAttribArray(triangle_shader_vpos_loc);
}

void DGraphics::triangle(const DVector& p1,const DVector& p2,const DVector& p3)
{
    triangle(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y);
}

void DGraphics::line(float x1, float y1, float x2, float y2)
{
    glUseProgram(line_shader->getId());
    glUniform1f(line_shader_strokeWeight_loc,properties.use_stroke?properties.stroke_weight:0.0f);
    glUniform4f(line_shader_points_loc,x1,y1,x2,y2);
    glUniform4f(line_shader_strokeColor_loc,properties.stroke_color.red()/255.0f,
                                                                    properties.stroke_color.green()/255.0f,
                                                                    properties.stroke_color.blue()/255.0f,
                                                                    properties.stroke_color.alpha()/255.0f);
    glUniformMatrix4fv(line_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniform1i(line_shader_cap_loc,properties.strokecap);

    glEnableVertexAttribArray(line_shader_vpos_loc);
    glEnableVertexAttribArray(line_shader_tpos_loc);


    glVertexAttribPointer(line_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(line_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square_line);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(line_shader_tpos_loc);
    glDisableVertexAttribArray(line_shader_vpos_loc);
}

void DGraphics::line(const DVector& p1,const DVector& p2)
{
    line(p1.x,p1.y,p2.x,p2.y);
}

void DGraphics::point(float x, float y)
{
    line(x,y,x,y);
}

void DGraphics::point(const DVector& p)
{
    line(p,p);
}

void DGraphics::image(const DImage& img, float x, float y)
{
    image(img,x,y,img.width,img.height);
}

void DGraphics::image(const DImage& img, float x, float y, float w, float h)
{
    glUseProgram(image_shader->getId());
    glUniform4f(image_shader_offset_loc,x,y,w,h);
   
    glUniformMatrix4fv(image_shader_view_loc,1,GL_FALSE,view_mat.values);
    glUniform1i(image_shader_posmode_loc,properties.imagemode);

    img.bind(0);
    glUniform1i(image_shader_tex_loc,0);

    glEnableVertexAttribArray(image_shader_vpos_loc);
    glEnableVertexAttribArray(image_shader_tpos_loc);

    glVertexAttribPointer(image_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(image_shader_vpos_loc,2,GL_FLOAT,false,0, primitive_square);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(image_shader_vpos_loc);
    glDisableVertexAttribArray(image_shader_tpos_loc);
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
    glUniform4f(quad_shader_strokeColor_loc,properties.stroke_color.red()/255.0f,
                                                                    properties.stroke_color.green()/255.0f,
                                                                    properties.stroke_color.blue()/255.0f,
                                                                    properties.stroke_color.alpha()/255.0f);
    glUniform4f(quad_shader_fillColor_loc,properties.fill_color.red()/255.0f,
                                                                    properties.fill_color.green()/255.0f,
                                                                    properties.fill_color.blue()/255.0f,
                                                                    properties.use_fill?properties.fill_color.alpha()/255.0f:0.0f);
    glUniformMatrix4fv(quad_shader_view_loc,1,GL_FALSE,view_mat.values);

    glEnableVertexAttribArray(quad_shader_vpos_loc);

    glVertexAttribPointer(quad_shader_vpos_loc,2,GL_FLOAT,false,0, quad_verts);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(quad_shader_vpos_loc);
}

void DGraphics::quad(const DVector& p1, const DVector& p2, const DVector& p3, const DVector& p4)
{
    quad(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y);
}

void DGraphics::shape(DShape* s, float x, float y, float w, float h)
{
    // DEBUG TEMP: Draw bounds
    glColor4ub(0, 0, 0, 255);
    glBegin(GL_LINE_LOOP);
    glVertex2f(w, h);
    glVertex2f(x, h);
    glVertex2f(x, y);
    glVertex2f(w, y);
    glEnd();

    // If SVG was loaded into this shape its objects has been split to new child shapes
    // The NULL image indicates that when drawing this shape, only its children should be drawn instead
    if (s->image != NULL)
    {
        // If child of SVG shape was copied this is where it's drawn
        for (NSVGpath* path = s->image->shapes->paths; path != NULL; path = path->next)
        {
            shapeDrawPath(path->pts, path->npts, path->closed, 1.0f);
            shapeDrawControlPts(path->pts, path->npts);
        }
    }

    // Draw childrens
    for (int i = 0; i < s->getChildCount(); i++)
    {
        DShape* child = s->getChild(i);
        if (child->image == NULL) { continue; }

        for (NSVGpath* path = child->image->shapes->paths; path != NULL; path = path->next)
        {
            shapeDrawPath(path->pts, path->npts, path->closed, 1.0f);
            shapeDrawControlPts(path->pts, path->npts);
        }
    }
}

void DGraphics::shapeDrawPath(float* pts, int npts, char closed, float tol)
{
    int i;
    static unsigned char lineColor[4] = { 0,160,192,255 };

    glBegin(GL_LINE_STRIP);
    glColor4ubv(lineColor);
    glVertex2f(pts[0], pts[1]);
    for (i = 0; i < npts - 1; i += 3)
    {
        float* p = &pts[i * 2];
        shapeCubicBez(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], tol, 0);
    }

    if (closed) 
    {
        glVertex2f(pts[0], pts[1]);
    }
    glEnd();

    glDrawArrays(GL_TRIANGLES, 0, npts);
}

float DGraphics::shapeDistPtSeg(float x, float y, float px, float py, float qx, float qy)
{
    float pqx, pqy, dx, dy, d, t;
    pqx = qx - px;
    pqy = qy - py;
    dx = x - px;
    dy = y - py;
    d = pqx * pqx + pqy * pqy;
    t = pqx * dx + pqy * dy;
    if (d > 0) t /= d;
    if (t < 0) t = 0;
    else if (t > 1) t = 1;
    dx = px + t * pqx - x;
    dy = py + t * pqy - y;
    return dx * dx + dy * dy;
}

void DGraphics::shapeDrawControlPts(float* pts, int npts)
{
    int i;
    static unsigned char lineColor[4] = { 0,160,192,255 };
    static unsigned char bgColor[4] = { 205,202,200,255 };


    // Control lines
    glColor4ubv(lineColor);
    glBegin(GL_LINES);
    for (i = 0; i < npts - 1; i += 3) {
        float* p = &pts[i * 2];
        glVertex2f(p[0], p[1]);
        glVertex2f(p[2], p[3]);
        glVertex2f(p[4], p[5]);
        glVertex2f(p[6], p[7]);
    }
    glEnd();

    // Points
    glPointSize(6.0f);
    glColor4ubv(lineColor);

    glBegin(GL_POINTS);
    glVertex2f(pts[0], pts[1]);
    for (i = 0; i < npts - 1; i += 3) {
        float* p = &pts[i * 2];
        glVertex2f(p[6], p[7]);
    }
    glEnd();

    // Points
    glPointSize(3.0f);

    glBegin(GL_POINTS);
    glColor4ubv(bgColor);
    glVertex2f(pts[0], pts[1]);
    for (i = 0; i < npts - 1; i += 3) {
        float* p = &pts[i * 2];
        glColor4ubv(lineColor);
        glVertex2f(p[2], p[3]);
        glVertex2f(p[4], p[5]);
        glColor4ubv(bgColor);
        glVertex2f(p[6], p[7]);
    }
    glEnd();
}

void DGraphics::shapeCubicBez(float x1, float y1, float x2, float y2,
    float x3, float y3, float x4, float y4,
    float tol, int level)
{
    float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
    float d;

    if (level > 12) return;

    x12 = (x1 + x2) * 0.5f;
    y12 = (y1 + y2) * 0.5f;
    x23 = (x2 + x3) * 0.5f;
    y23 = (y2 + y3) * 0.5f;
    x34 = (x3 + x4) * 0.5f;
    y34 = (y3 + y4) * 0.5f;
    x123 = (x12 + x23) * 0.5f;
    y123 = (y12 + y23) * 0.5f;
    x234 = (x23 + x34) * 0.5f;
    y234 = (y23 + y34) * 0.5f;
    x1234 = (x123 + x234) * 0.5f;
    y1234 = (y123 + y234) * 0.5f;

    d = shapeDistPtSeg(x1234, y1234, x1, y1, x4, y4);
    if (d > tol * tol) {
        shapeCubicBez(x1, y1, x12, y12, x123, y123, x1234, y1234, tol, level + 1);
        shapeCubicBez(x1234, y1234, x234, y234, x34, y34, x4, y4, tol, level + 1);
    }
    else {
        glVertex2f(x4, y4);
    }
}

bool DGraphics::save(const std::string& filename, ImageFormat format) const
{
    if(buffer_id == -1 || buffer_height == 0 || buffer_width == 0) return false;

    unsigned char* data = new unsigned char[buffer_width*buffer_height*3];
    glBindTexture(GL_TEXTURE_2D,texture_id);

    glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_UNSIGNED_BYTE,data);

    int result = 0;

    stbi_flip_vertically_on_write(1);

    switch (format)
    {
        case ImageFormat::PNG:
        {
            std::string name = filename + ".png";
            result = stbi_write_png(name.data(),buffer_width,buffer_height,3,data,buffer_width*3);
            break;
        }
        case ImageFormat::JPG:
        {
            std::string name = filename + ".jpg";
            result = stbi_write_jpg(name.data(),buffer_width,buffer_height,3,data,100);
            break;
        }
        case ImageFormat::TGA:
        {
            std::string name = filename + ".tga";
            result = stbi_write_tga(name.data(),buffer_width,buffer_height,3,data);
            break;
        }
        case ImageFormat::BMP:
        {
            std::string name = filename + ".bmp";
            result = stbi_write_bmp(name.data(),buffer_width,buffer_height,3,data);
            break;
        }
    }

    delete[] data;

    return result == 1;
}


GraphicsProperties DGraphics::getStyle()
{
    return properties;
}

Color DGraphics::get_rgba(float r, float g, float b, float a)
{
    r = std::max(0.0f,std::min(properties.color_max1,r));
    g = std::max(0.0f,std::min(properties.color_max1,g));
    b = std::max(0.0f,std::min(properties.color_max1,b));
    a = std::max(0.0f,std::min(properties.color_max1,a));
    
    uint8_t rv = (r / properties.color_max1)*255;
    uint8_t gv = (g / properties.color_max2)*255;
    uint8_t bv = (b / properties.color_max3)*255;
    uint8_t av = (a / properties.color_maxa)*255;

    Color rc;
    reinterpret_cast<uint8_t*>(&rc)[0] = av;
    reinterpret_cast<uint8_t*>(&rc)[1] = rv;
    reinterpret_cast<uint8_t*>(&rc)[2] = gv;
    reinterpret_cast<uint8_t*>(&rc)[3] = bv;
    rc.RGB2HSB(rv,gv,bv);

    return rc;

    //return Color(rv,gv,bv,av);
}

Color DGraphics::get_hsba(float h, float s, float b, float a)
{
    h = std::max(0.0f,std::min(properties.color_max1,h));
    s = std::max(0.0f,std::min(properties.color_max1,s));
    b = std::max(0.0f,std::min(properties.color_max1,b));
    a = std::max(0.0f,std::min(properties.color_max1,a));
    
    float hv = h / properties.color_max1;
    float sv = s / properties.color_max2;
    float bv = b / properties.color_max3;
    float av = a / properties.color_maxa;

    float tr=0, tg=0, tb=0;

    if(hv < 0.33333f)
    {
        tr = (0.33333f - hv) / 0.16666f;
        tg = hv / 0.16666f;
        tb = 0;
    }
    else if(hv < 0.66666f)
    {
        tr = 0;
        tg = (0.66666f - hv) / 0.16666f;
        tb = (hv - 0.33333f) / 0.16666f;
    } 
    else
    {
        tr = (hv - 0.66666f) / 0.16666f;
        tg = 0;
        tb = (1.0f - hv) / 0.16666f;
    }

    tr = std::min(tr,1.0f);
    tg = std::min(tg,1.0f);
    tb = std::min(tb,1.0f);

    uint8_t r =  (1 - sv + sv * tr) * bv * 255;
    uint8_t g =  (1 - sv + sv * tg) * bv * 255;
    uint8_t bb = (1 - sv + sv * tb) * bv * 255;
    uint8_t aa = av * 255;

    Color rc;
    reinterpret_cast<uint8_t*>(&rc)[0] = aa;
    reinterpret_cast<uint8_t*>(&rc)[1] = r;
    reinterpret_cast<uint8_t*>(&rc)[2] = g;
    reinterpret_cast<uint8_t*>(&rc)[3] = bb;

    //rc.RGB2HSB(r,g,bb);
    float* hsb = reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(&rc)+4);
    hsb[0] = hv * 360;
    hsb[1] = sv * 100;
    hsb[2] = bv * 100;

    return rc;

    //return Color(r,g,bb,aa);
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