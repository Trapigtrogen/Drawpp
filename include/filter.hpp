#ifndef DPP_FILTER_H
#define DPP_FILTER_H

#include <memory>
#include <string>

struct Vector2;
struct Vector3;
struct Vector4;
struct Matrix2;
struct Matrix3;
struct Matrix4;

struct DFilter_impl;

///\brief Class for post-processing filters
class DFilter
{
    friend class DGraphics;
public:


    ///\brief Load a filter from a string
    static DFilter loadFilter(const std::string& filterSource);


    ///\brief Load a filter from a file
    static DFilter loadFile(const std::string& filename);


    ///\brief Get the shader program id
    unsigned int getProgram() const;


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, float value);


    ///\brief Assign values to uniform called \p name
    void setUniform(const std::string& name, float value1, float value2);


    ///\brief Assign values to uniform called \p name
    void setUniform(const std::string& name, float value1, float value2, float value3);


    ///\brief Assign values to uniform called \p name
    void setUniform(const std::string& name, float value1, float value2, float value3, float value4);


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, const Vector2& value);


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, const Vector3& value);


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, const Vector4& value);


    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, float* value);


    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, Vector2* value);


    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, Vector3* value);


    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, Vector4* value);


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, int value);


    ///\brief Assign values to uniform called \p name
    void setUniform(const std::string& name, int value1, int value2);


    ///\brief Assign values to uniform called \p name
    void setUniform(const std::string& name, int value1, int value2, int value3);


    ///\brief Assign values to uniform called \p name
    void setUniform(const std::string& name, int value1, int value2, int value3, int value4);
    

    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, int* value);


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, const Matrix2& value);


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, const Matrix3& value);


    ///\brief Assign \p value to uniform called \p name
    void setUniform(const std::string& name, const Matrix4& value);


    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, Matrix2* value);


    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, Matrix3* value);


    ///\brief Assign array values to uniform called \p name
    ///
    ///If count is less than zero, this function does nothing. 
    void setUniform(const std::string& name, int count, Matrix4* value);

private:
    std::shared_ptr<DFilter_impl> impl;
};

#endif