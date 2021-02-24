#include <algorithm>
#include <graphics.hpp>
#include <shader.hpp>
#include <glad/glad.h>
#include <debug.hpp>
#include <vector3.hpp>

const float primitive_square[] = 
{
    0.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  0.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    1.0f,  0.0f, 0.0f,
    0.0f,  0.0f, 0.0f,
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

const char* ellipse_shader_v = R"(#version 100
precision mediump float;
//uniform mat4 transform;
uniform mat4 view;
uniform vec4 offset;
attribute vec3 pos;
attribute vec2 texpos;
varying vec2 texc;
void main()
{
    texc = texpos;

    mat4 transf = mat4(1.0);
    transf[0][3] = transf[0][3] + offset.x;
    transf[1][3] = transf[1][3] - offset.y;
    transf[0][0] = transf[0][0] + offset.z;
    transf[1][1] = transf[1][1] + offset.w;
    mat4 mv = transf * view;

    gl_Position = vec4(pos,1.0) * mv;
}
)";

const char* ellipse_shader_f = R"(#version 100
precision mediump float;
uniform float strokeWeight;
uniform vec4 strokeColor;
uniform vec4 fillColor;
uniform vec4 offset;
varying vec2 texc;

float atan2(in float y, in float x)
{
    bool s = (abs(x) > abs(y));
    return mix(radians(180.0)/2.0 - atan(x,y), atan(y,x), float(s));
}

void main()
{
    vec2 tc = abs(texc*2.0 - 1.0);
    float l = length(tc);

    float ang = atan2(tc.x,tc.y);
    vec2 dir = vec2(cos(ang),sin(ang));

    //something wrong here, stroke len too large. mult by 0.66 to make better, but 
    //it's not accurate still. also skews if width != height, so maybe this is shit overall
    //float d2 = 1.0 - length(vec2(strokeWeight * 0.666) / (offset.wz / 2.0));

    //this one makes a correct stroke width, if width == height.
    //weird artefact will happen if width != height.
    //using this for now because it's the best we got
    vec2 p2 = (vec2(1.0) / (offset.wz / 2.0)) * vec2(strokeWeight);
    p2.x = p2.x * abs(cos(ang));
    p2.y = p2.y * abs(sin(ang));
    float d2 = length(dir-p2);

    if(l < 1.0 && l > d2)
    {
        gl_FragColor = strokeColor;
    }
    else if(l <= d2)
    {
        gl_FragColor = fillColor;
    }
    else
    {
        discard;
    }
}
)";

const char* rect_shader_f = R"(#version 100
precision mediump float;
uniform float strokeWeight;
uniform vec4 strokeColor;
uniform vec4 fillColor;
uniform vec4 offset;
uniform vec4 radii;
varying vec2 texc;

float atan2(in float y, in float x)
{
    bool s = (abs(x) > abs(y));
    return mix(radians(180.0)/2.0 - atan(x,y), atan(y,x), float(s));
}

void main()
{
    vec2 off1 = vec2(1.0) / offset.zw;
    vec2 stroke = off1 * strokeWeight;
    
    vec4 radii2 = clamp(radii, vec4(0.0),vec4(min(offset.z,offset.w)/2.0));
    vec2 rad;
    vec2 tpos;
    bool corner = false;
    bool ystroke = false;
    bool xstroke = false;
    

    //topleft
    if(texc.x < 0.5 && texc.y > 0.5)
    {
        if(radii2.x != 0.0)
        {
            rad = vec2(radii2.x) * off1;
        }

        if(texc.x < rad.x && texc.y > 1.0-rad.y)
        {
            tpos = (texc - vec2(0.0,1.0-rad.y)) / rad;
            tpos = vec2(1.0-tpos.x,tpos.y);
            corner = true;
        }
        else
        {
            ystroke = (texc.y < 1.0 && texc.y > 1.0-stroke.y);
            xstroke = (texc.x > 0.0 && texc.x < stroke.x);  
        }
    }
    //topright
    else if(texc.x > 0.5 && texc.y > 0.5)
    {
        if(radii2.y != 0.0)
        {
            rad = vec2(radii2.y) * off1;
        }

        if(texc.x > 1.0-rad.x && texc.y > 1.0-rad.y)
        {
            tpos = (texc - vec2(1.0-rad.x,1.0-rad.y)) / rad;
            corner = true;
        }
        else
        {
            ystroke = (texc.y < 1.0 && texc.y > 1.0-stroke.y);
            xstroke = (texc.x < 1.0 && texc.x > 1.0-stroke.x);
        }
    }
    //bottomright
    else if(texc.x > 0.5 && texc.y < 0.5)
    {
        if(radii2.z != 0.0)
        {
            rad = vec2(radii2.z) * off1;
        }
        
        if(texc.x > 1.0-rad.x && texc.y < rad.y)
        {
            tpos = (texc - vec2(1.0-rad.x,0.0)) / rad;
            tpos = vec2(tpos.x,1.0-tpos.y);
            corner = true;
        }
        else
        {
            ystroke = (texc.y > 0.0 && texc.y < stroke.y);
            xstroke = (texc.x < 1.0 && texc.x > 1.0-stroke.x);
        }
    }
    //bottomleft
    else if(texc.x < 0.5 && texc.y < 0.5)
    {
        if(radii2.w != 0.0)
        {
            rad = vec2(radii2.w) * off1;
        }
        
        if(texc.x < rad.x && texc.y < rad.y)
        {
            tpos = vec2(1.0) - (texc / rad);
            corner = true;
        }
        else
        {
            ystroke = (texc.y > 0.0 && texc.y < stroke.y);
            xstroke = (texc.x > 0.0 && texc.x < stroke.x);
        }
    }

    if(corner)
    {
        vec2 str = stroke * (vec2(1.0) / rad);

        float l = length(tpos);

        float ang = atan2(tpos.x, tpos.y);
        vec2 dir = vec2(cos(ang),sin(ang));

        vec2 p2 = stroke / rad;
        p2.x = p2.x * abs(cos(ang));
        p2.y = p2.y * abs(sin(ang));
        float sl = length(p2);

        if(l <= 1.0 && l >= 1.0-sl)
        {
            gl_FragColor = strokeColor;
        }
        else if(l < 1.0-sl)
        {
            gl_FragColor = fillColor;
        }
        else
        {
            discard;
        }
    }
    else
    {
        if(ystroke || xstroke)
        {
            gl_FragColor = strokeColor;
        }
        else
        {
            gl_FragColor = fillColor;
        }
    }

    //simple rect, no rounded corners
    //bool ystroke = (texc.y > 0.0 && texc.y < stroke.y) || (texc.y < 1.0 && texc.y > 1.0-stroke.y);
    //bool xstroke = (texc.x > 0.0 && texc.x < stroke.x) || (texc.x < 1.0 && texc.x > 1.0-stroke.x);
    //
    //if(ystroke || xstroke)
    //{
    //    gl_FragColor = strokeColor;
    //}
    //else
    //{
    //    gl_FragColor = fillColor;
    //}
}
)";

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

void DGraphics::init_shaders()
{
    ellipse_shader = new Shader(Shader::loadShadersFromString(ellipse_shader_v,ellipse_shader_f));
    
    ellipse_shader_offset_loc = glGetUniformLocation(ellipse_shader->getId(),"offset");
    ellipse_shader_strokeWeight_loc = glGetUniformLocation(ellipse_shader->getId(),"strokeWeight");
    ellipse_shader_strokeColor_loc = glGetUniformLocation(ellipse_shader->getId(),"strokeColor");                                             
    ellipse_shader_fillColor_loc = glGetUniformLocation(ellipse_shader->getId(),"fillColor");
    //ellipse_shader_transform_loc = glGetUniformLocation(ellipse_shader->getId(),"transform");
    ellipse_shader_view_loc = glGetUniformLocation(ellipse_shader->getId(),"view");
    ellipse_shader_vpos_loc = glGetAttribLocation(ellipse_shader->getId(),"pos");
    ellipse_shader_tpos_loc = glGetAttribLocation(ellipse_shader->getId(),"texpos");


    rect_shader = new Shader(Shader::loadShadersFromString(ellipse_shader_v,rect_shader_f));
    
    rect_shader_offset_loc = glGetUniformLocation(rect_shader->getId(),"offset");
    rect_shader_strokeWeight_loc = glGetUniformLocation(rect_shader->getId(),"strokeWeight");
    rect_shader_strokeColor_loc = glGetUniformLocation(rect_shader->getId(),"strokeColor");                                             
    rect_shader_fillColor_loc = glGetUniformLocation(rect_shader->getId(),"fillColor");                                           
    rect_shader_radii_loc = glGetUniformLocation(rect_shader->getId(),"radii");
    rect_shader_view_loc = glGetUniformLocation(rect_shader->getId(),"view");
    rect_shader_vpos_loc = glGetAttribLocation(rect_shader->getId(),"pos");
    rect_shader_tpos_loc = glGetAttribLocation(rect_shader->getId(),"texpos");
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

void DGraphics::strokeWeight(float w)
{
    properties.stroke_weight = std::abs(w);
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

    return Color(v,v,v,a);
}

Color DGraphics::color(float v1, float v2, float v3)
{
    return get_color(v1,v3,v3,properties.color_maxa);
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

    glEnableVertexAttribArray(ellipse_shader_vpos_loc);
    glEnableVertexAttribArray(ellipse_shader_tpos_loc);

    glVertexAttribPointer(ellipse_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(ellipse_shader_vpos_loc,3,GL_FLOAT,false,0, primitive_square);

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

    glEnableVertexAttribArray(rect_shader_vpos_loc);
    glEnableVertexAttribArray(rect_shader_tpos_loc);

    glVertexAttribPointer(rect_shader_tpos_loc,2,GL_FLOAT,false,0, coords_quad);
    glVertexAttribPointer(rect_shader_vpos_loc,3,GL_FLOAT,false,0, primitive_square);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(rect_shader_vpos_loc);
    glDisableVertexAttribArray(rect_shader_tpos_loc);
}

void DGraphics::square(float x, float y, float size)
{
    rect(x,y,size,size);
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

    return Color(rv,gv,bv,av);
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

    return Color(r,g,bb,aa);
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

//unsigned int DGraphics::current_bound_buffer = 0;
//unsigned int DGraphics::previous_bound_buffer = 0;