#include <graphics.hpp>
#include <glad/glad.h>
#include <debug.hpp>

const float primitive_square[] = 
{
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
};

float coords_quad[] = 
{
    -1.0f, -1.0f,
     1.0f, -1.0f, 
     1.0f,  1.0f, 
    -1.0f, -1.0f, 
     1.0f,  1.0f, 
    -1.0f,  1.0f, 
};


DGraphics::DGraphics(int width, int height)
{
    buffer_width = static_cast<unsigned int>(width);
    buffer_height = static_cast<unsigned int>(height);
    glGenFramebuffers(1,&buffer_id);

    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,buffer_width,buffer_height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture_id,0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        dbg::error("Failed to create framebuffer");
    }
}

void DGraphics::beginDraw()
{
    properties = GraphicsProperties();
    glBindFramebuffer(GL_FRAMEBUFFER,buffer_id);
    glViewport(0,0,buffer_width,buffer_height);
}

void DGraphics::endDraw()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
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
    transform_mat.translate(t);
}

void DGraphics::rotate(float angle)
{
    rotateZ(angle);
}

void DGraphics::rotateX(float angle)
{
    transform_mat.rotate<Axis::X>(angle);
}

void DGraphics::rotateY(float angle)
{
    transform_mat.rotate<Axis::Y>(angle);
}

void DGraphics::rotateZ(float angle)
{
    transform_mat.rotate<Axis::Z>(angle);
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
    transform_mat.scale(s);
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
    matrix_stack.push(transform_mat);
}

void DGraphics::popMatrix()
{
    transform_mat = matrix_stack.top();
    matrix_stack.pop();
}

void DGraphics::pushStyle()
{
    property_stack.push(properties);
}

void DGraphics::popStyle()
{
    properties = property_stack.top();
    property_stack.pop();
}



unsigned int DGraphics::get_texture_id()
{
    return texture_id;
}

//unsigned int DGraphics::current_bound_buffer = 0;
//unsigned int DGraphics::previous_bound_buffer = 0;