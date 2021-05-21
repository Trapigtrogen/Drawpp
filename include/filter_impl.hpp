#ifndef DPP_FILTER_IMPL_H
#define DPP_FILTER_IMPL_H

#include <string>
#include <shader.hpp>
#include <unordered_map>
#include <filter_uniform_data.hpp>
#include <glad.h>

struct Vector2;
struct Vector3;
struct Vector4;
struct Matrix2;
struct Matrix3;
struct Matrix4;

///\private
struct DFilter_impl
{
    ~DFilter_impl();

    bool init(const std::string& filterSource);

    template<class T> T* getUniformDataPtr(const std::string& name)
    {
        auto f = uniforms.find(name);
        T* ptr = nullptr;

        if(f == uniforms.end())
        {
            ptr = new T;
            ptr->location = glGetUniformLocation(shader.getId(),name.c_str());
            uniforms[name] = ptr;
        }
        else
        {
            ptr = static_cast<T*>(f->second);
        }

        return ptr;
    }

    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, float value1, float value2);
    void setUniform(const std::string& name, float value1, float value2, float value3);
    void setUniform(const std::string& name, float value1, float value2, float value3, float value4);
    void setUniform(const std::string& name, const Vector2& value);
    void setUniform(const std::string& name, const Vector3& value);
    void setUniform(const std::string& name, const Vector4& value);

    void setUniform(const std::string& name, int count, float* value);
    void setUniform(const std::string& name, int count, Vector2* value);
    void setUniform(const std::string& name, int count, Vector3* value);
    void setUniform(const std::string& name, int count, Vector4* value);

    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, int value1, int value2);
    void setUniform(const std::string& name, int value1, int value2, int value3);
    void setUniform(const std::string& name, int value1, int value2, int value3, int value4);
    
    void setUniform(const std::string& name, int count, int* value);

    void setUniform(const std::string& name, const Matrix2& value);
    void setUniform(const std::string& name, const Matrix3& value);
    void setUniform(const std::string& name, const Matrix4& value);

    void setUniform(const std::string& name, int count, Matrix2* value);
    void setUniform(const std::string& name, int count, Matrix3* value);
    void setUniform(const std::string& name, int count, Matrix4* value);

    void upload_all_uniforms();

    Shader shader;

    int source_location;
    int source_size_location;
    int vertex_pos_location;
    std::unordered_map<std::string,UniformDataBase*> uniforms;

    static const std::string fragment_stub;
    static const char* vertex_source;
};

#endif