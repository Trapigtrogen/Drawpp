#include <filter.hpp>
#include <filter_impl.hpp>
#include <debug.hpp>
#include <vector2.hpp>
#include <vector3.hpp>
#include <vector4.hpp>
#include <matrix2.hpp>
#include <matrix3.hpp>
#include <matrix4.hpp>


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

void DFilter_impl::setUniform(const std::string& name, const Vector2& value)
{
    setUniform(name,value.x,value.y);
}

void DFilter_impl::setUniform(const std::string& name, const Vector3& value)
{
    setUniform(name,value.x,value.y,value.z);
}

void DFilter_impl::setUniform(const std::string& name, const Vector4& value)
{
    setUniform(name,value.x,value.y,value.z,value.w);
}


void DFilter_impl::setUniform(const std::string& name, int count, float* value)
{
    UniformData1fv* ptr = getUniformDataPtr<UniformData1fv>(name);
    ptr->count = count;
    ptr->value.clear();
    ptr->value.reserve(count);

    for(unsigned int i = 0; i < count; ++i)
    {
        ptr->value.push_back(value[i]);
    }
}

void DFilter_impl::setUniform(const std::string& name, int count, Vector2* value)
{
    UniformData2fv* ptr = getUniformDataPtr<UniformData2fv>(name);
    ptr->count = count;
    ptr->value.clear();
    ptr->value.reserve(count*2);

    for(unsigned int i = 0; i < count; ++i)
    {
        ptr->value.push_back(value[i].x);
        ptr->value.push_back(value[i].y);
    }
}

void DFilter_impl::setUniform(const std::string& name, int count, Vector3* value)
{
    UniformData3fv* ptr = getUniformDataPtr<UniformData3fv>(name);
    ptr->count = count;
    ptr->value.clear();
    ptr->value.reserve(count*3);

    for(unsigned int i = 0; i < count; ++i)
    {
        ptr->value.push_back(value[i].x);
        ptr->value.push_back(value[i].y);
        ptr->value.push_back(value[i].z);
    }
}

void DFilter_impl::setUniform(const std::string& name, int count, Vector4* value)
{
    UniformData4fv* ptr = getUniformDataPtr<UniformData4fv>(name);
    ptr->count = count;
    ptr->value.clear();
    ptr->value.reserve(count*4);

    for(unsigned int i = 0; i < count; ++i)
    {
        ptr->value.push_back(value[i].x);
        ptr->value.push_back(value[i].y);
        ptr->value.push_back(value[i].z);
        ptr->value.push_back(value[i].w);
    }
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
    ptr->value.clear();
    ptr->value.reserve(count);

    for(unsigned int i = 0; i < count; ++i)
    {
        ptr->value.push_back(value[i]);
    }
}

void DFilter_impl::setUniform(const std::string& name, const Matrix2& value)
{
    UniformDataMatrix2f* ptr = getUniformDataPtr<UniformDataMatrix2f>(name);

    ptr->value[0] = value[0];
    ptr->value[1] = value[1];
    ptr->value[2] = value[2];
    ptr->value[3] = value[3];
}

void DFilter_impl::setUniform(const std::string& name, const Matrix3& value)
{
    UniformDataMatrix3f* ptr = getUniformDataPtr<UniformDataMatrix3f>(name);

    for(unsigned int i = 0; i < 9; ++i)
    {
        ptr->value[i] = value[i];
    }
}

void DFilter_impl::setUniform(const std::string& name, const Matrix4& value)
{
    UniformDataMatrix4f* ptr = getUniformDataPtr<UniformDataMatrix4f>(name);

    for(unsigned int i = 0; i < 16; ++i)
    {
        ptr->value[i] = value[i];
    }
}

void DFilter_impl::setUniform(const std::string& name, int count, Matrix2* value)
{
    UniformDataMatrix2fv* ptr = getUniformDataPtr<UniformDataMatrix2fv>(name);
    ptr->count = count;
    ptr->value.clear();
    ptr->value.reserve(count*4);
    
    for(unsigned int i = 0; i < count; ++i)
    {
        ptr->value[i*4+0] = value[i][0];
        ptr->value[i*4+1] = value[i][1];
        ptr->value[i*4+2] = value[i][2];
        ptr->value[i*4+3] = value[i][3];
    }
}

void DFilter_impl::setUniform(const std::string& name, int count, Matrix3* value)
{
    UniformDataMatrix3fv* ptr = getUniformDataPtr<UniformDataMatrix3fv>(name);
    ptr->count = count;
    ptr->value.clear();
    ptr->value.reserve(count*9);
    
    for(unsigned int i = 0; i < count; ++i)
    {
        for(unsigned int j = 0; j < 9; ++j)
        {
            ptr->value[i*9+j] = value[i][j];
        }
    }
}

void DFilter_impl::setUniform(const std::string& name, int count, Matrix4* value)
{
    UniformDataMatrix4fv* ptr = getUniformDataPtr<UniformDataMatrix4fv>(name);
    ptr->count = count;
    ptr->value.clear();
    ptr->value.reserve(count*16);
    
    for(unsigned int i = 0; i < count; ++i)
    {
        for(unsigned int j = 0; j < 16; ++j)
        {
            ptr->value[i*16+j] = value[i][j];
        }
    }
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


void DFilter::setUniform(const std::string& name, const Vector2& value)
{
    impl->setUniform(name,value);
}

void DFilter::setUniform(const std::string& name, const Vector3& value)
{
    impl->setUniform(name,value);
}

void DFilter::setUniform(const std::string& name, const Vector4& value)
{
    impl->setUniform(name,value);
}


void DFilter::setUniform(const std::string& name, int count, float* value)
{
    if(count < 0)
    {
        return;
    }

    impl->setUniform(name,count,value);
}

void DFilter::setUniform(const std::string& name, int count, Vector2* value)
{
    if(count < 0)
    {
        return;
    }
    
    impl->setUniform(name,count,value);
}

void DFilter::setUniform(const std::string& name, int count, Vector3* value)
{
    if(count < 0)
    {
        return;
    }
    
    impl->setUniform(name,count,value);
}

void DFilter::setUniform(const std::string& name, int count, Vector4* value)
{
    if(count < 0)
    {
        return;
    }
    
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
    if(count < 0)
    {
        return;
    }
    
    impl->setUniform(name,count,value);
}

void DFilter::setUniform(const std::string& name, const Matrix2& value)
{
    impl->setUniform(name,value);
}

void DFilter::setUniform(const std::string& name, const Matrix3& value)
{
    impl->setUniform(name,value);
}

void DFilter::setUniform(const std::string& name, const Matrix4& value)
{
    impl->setUniform(name,value);
}

void DFilter::setUniform(const std::string& name, int count, Matrix2* value)
{
    if(count < 0)
    {
        return;
    }
    
    impl->setUniform(name,count,value);
}

void DFilter::setUniform(const std::string& name, int count, Matrix3* value)
{
    if(count < 0)
    {
        return;
    }
    
    impl->setUniform(name,count,value);
}

void DFilter::setUniform(const std::string& name, int count, Matrix4* value)
{
    if(count < 0)
    {
        return;
    }
    
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
    glUniform1fv(location,count,value.data());
};

void  UniformData2fv::set()
{
    glUniform2fv(location,count,value.data());
};

void  UniformData3fv::set()
{
    glUniform3fv(location,count,value.data());
};

void  UniformData4fv::set()
{
    glUniform4fv(location,count,value.data());
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
    glUniform1iv(location,value.size(),value.data());
}

void UniformDataMatrix2f::set()
{
    glUniformMatrix2fv(location,1,GL_FALSE,value);
}

void UniformDataMatrix3f::set()
{
    glUniformMatrix3fv(location,1,GL_FALSE,value);
}

void UniformDataMatrix4f::set()
{
    glUniformMatrix4fv(location,1,GL_FALSE,value);
}

void UniformDataMatrix2fv::set()
{
    glUniformMatrix2fv(location,count,GL_FALSE,value.data());
}

void UniformDataMatrix3fv::set()
{
    glUniformMatrix3fv(location,count,GL_FALSE,value.data());
}

void UniformDataMatrix4fv::set()
{
    glUniformMatrix4fv(location,count,GL_FALSE,value.data());
}