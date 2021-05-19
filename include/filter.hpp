#ifndef DPP_FILTER_H
#define DPP_FILTER_H

#include <memory>
#include <string>

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


    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, float value1, float value2);
    void setUniform(const std::string& name, float value1, float value2, float value3);
    void setUniform(const std::string& name, float value1, float value2, float value3, float value4);

    void setUniform(const std::string& name, int count, float* value);

    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, int value1, int value2);
    void setUniform(const std::string& name, int value1, int value2, int value3);
    void setUniform(const std::string& name, int value1, int value2, int value3, int value4);
    
    void setUniform(const std::string& name, int count, int* value);

private:
    std::shared_ptr<DFilter_impl> impl;
};

#endif