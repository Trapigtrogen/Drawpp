#include <graphics.hpp>
#include <glad/glad.h>
#include <debug.hpp>

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
    glBindFramebuffer(GL_FRAMEBUFFER,buffer_id);
    glViewport(0,0,buffer_width,buffer_height);
}

void DGraphics::endDraw()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

//unsigned int DGraphics::current_bound_buffer = 0;
//unsigned int DGraphics::previous_bound_buffer = 0;