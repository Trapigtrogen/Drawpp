#include <filter.hpp>
#include <filter_impl.hpp>
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

DFilter_impl::~DFilter_impl()
{
    for(auto& u : uniforms)
    {
        delete u.second;
    }
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

void DFilter_impl::upload_all_uniforms()
{
    for(auto& u : uniforms)
    {
        u.second->set();
    }
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


void DFilter_impl::setUniform(const std::string& name, float value)
{
    getUniformDataPtr<UniformData1f>(name)->value = value;
}

void DFilter_impl::setUniform(const std::string& name, float value1, float value2)
{
    UniformData2f* ptr = getUniformDataPtr<UniformData2f>(name);
    ptr->value[0] = value1;
    ptr->value[1] = value2;
}

void DFilter_impl::setUniform(const std::string& name, float value1, float value2, float value3)
{
    UniformData3f* ptr = getUniformDataPtr<UniformData3f>(name);
    ptr->value[0] = value1;
    ptr->value[1] = value2;
    ptr->value[2] = value3;
}

void DFilter_impl::setUniform(const std::string& name, float value1, float value2, float value3, float value4)
{
    UniformData4f* ptr = getUniformDataPtr<UniformData4f>(name);
    ptr->value[0] = value1;
    ptr->value[1] = value2;
    ptr->value[2] = value3;
    ptr->value[3] = value4;
}

void DFilter_impl::setUniform(const std::string& name, int count, float* value)
{
    UniformData1fv* ptr = getUniformDataPtr<UniformData1fv>(name);
    ptr->count = count;
    ptr->value = value;
}


void DFilter_impl::setUniform(const std::string& name, int value)
{
    getUniformDataPtr<UniformData1i>(name)->value = value;
}

void DFilter_impl::setUniform(const std::string& name, int value1, int value2)
{
    UniformData2i* ptr = getUniformDataPtr<UniformData2i>(name);
    ptr->value[0] = value1;
    ptr->value[1] = value2;
}

void DFilter_impl::setUniform(const std::string& name, int value1, int value2, int value3)
{
    UniformData3i* ptr = getUniformDataPtr<UniformData3i>(name);
    ptr->value[0] = value1;
    ptr->value[1] = value2;
    ptr->value[2] = value3;
}

void DFilter_impl::setUniform(const std::string& name, int value1, int value2, int value3, int value4)
{
    UniformData4i* ptr = getUniformDataPtr<UniformData4i>(name);
    ptr->value[0] = value1;
    ptr->value[1] = value2;
    ptr->value[2] = value3;
    ptr->value[3] = value4;
}

void DFilter_impl::setUniform(const std::string& name, int count, int* value)
{
    UniformData1iv* ptr = getUniformDataPtr<UniformData1iv>(name);
    ptr->count = count;
    ptr->value = value;
}



void DFilter::setUniform(const std::string& name, float value)
{
    impl->setUniform(name,value);
}

void DFilter::setUniform(const std::string& name, float value1, float value2)
{
    impl->setUniform(name,value1,value2);
}

void DFilter::setUniform(const std::string& name, float value1, float value2, float value3)
{
    impl->setUniform(name,value1,value2,value3);
}

void DFilter::setUniform(const std::string& name, float value1, float value2, float value3, float value4)
{
    impl->setUniform(name,value1,value2,value3,value4);
}

void DFilter::setUniform(const std::string& name, int count, float* value)
{
    impl->setUniform(name,count,value);
}


void DFilter::setUniform(const std::string& name, int value)
{
    impl->setUniform(name,value);
}

void DFilter::setUniform(const std::string& name, int value1, int value2)
{
    impl->setUniform(name,value1,value2);
}

void DFilter::setUniform(const std::string& name, int value1, int value2, int value3)
{
    impl->setUniform(name,value1,value2,value3);
}

void DFilter::setUniform(const std::string& name, int value1, int value2, int value3, int value4)
{
    impl->setUniform(name,value1,value2,value3,value4);
}

void DFilter::setUniform(const std::string& name, int count, int* value)
{
    impl->setUniform(name,count,value);
}


void UniformData1f::set()
{
    glUniform1f(location,value);
}

void UniformData2f::set()
{
    glUniform2f(location,value[0],value[1]);
}

void UniformData3f::set()
{
    glUniform3f(location,value[0],value[1],value[2]);
}

void UniformData4f::set()
{
    glUniform4f(location,value[0],value[1],value[2],value[3]);
}

void  UniformData1fv::set()
{
    glUniform1fv(location,count,value);
};


void UniformData1i::set()
{
    glUniform1i(location,value);
}

void UniformData2i::set()
{
    glUniform2i(location,value[0],value[1]);
}

void UniformData3i::set()
{
    glUniform3i(location,value[0],value[1],value[2]);
}

void UniformData4i::set()
{
    glUniform4i(location,value[0],value[1],value[2],value[3]);
}

void UniformData1iv::set()
{
    glUniform1iv(location,count,value);
}