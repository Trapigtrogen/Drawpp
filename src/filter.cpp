#include <filter.hpp>
#include <filter_impl.hpp>
#include <glad.h>
#include <debug.hpp>


DFilter DFilter::loadFilter(const std::string& filterSource)
{
    DFilter filter;

    DFilter_impl* ptr = new DFilter_impl;

    if(ptr->init(filterSource))
    {
        filter.impl = std::shared_ptr<DFilter_impl>(ptr);
    }
    else
    {
        delete ptr;
    }

    return filter;
}

DFilter DFilter::loadFile(const std::string& filename)
{
    return loadFilter(Shader::readShaderFile(filename.c_str()));
}

bool DFilter_impl::init(const std::string& filterSource)
{
    std::string full_frag_source = fragment_stub + filterSource;

    shader = Shader::loadShadersFromString(vertex_source,full_frag_source.c_str());

    GLint status;
    glValidateProgram(shader.getId());
    glGetProgramiv(shader.getId(),GL_VALIDATE_STATUS,&status);

    if(status == GL_FALSE)
    {
        dbg::error("Failed to compile filter.");
        return false;
    }

    source_location = glGetUniformLocation(shader.getId(),"source");
    source_size_location = glGetUniformLocation(shader.getId(),"source_size");
    vertex_pos_location = glGetAttribLocation(shader.getId(),"pos");

    return true;
}

unsigned int DFilter::getProgram() const
{
    return impl->shader.getId();
}

const std::string DFilter_impl::fragment_stub = R"(
    #version 100
    precision mediump float;
    uniform sampler2D source;
    uniform vec2 source_size;
    //vec2 source_position = gl_FragCoord.xy;
)";

const char* DFilter_impl::vertex_source = R"(
    #version 100
    precision mediump float;
    attribute vec2 pos;
    void main()
    {
        gl_Position = vec4(pos,0.0,1.0);
    }
)";