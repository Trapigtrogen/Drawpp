#ifndef DPP_FILTER_UNIFORM_DATA_H
#define DPP_FILTER_UNIFORM_DATA_H

#include <vector>

///\private
struct UniformDataBase
{
    unsigned int location;

    virtual void set() = 0;
};

///\private
struct UniformData1f : public UniformDataBase
{
    float value;

    void set();
};

///\private
struct UniformData2f : public UniformDataBase
{
    float value[2];

    void set();
};

///\private
struct UniformData3f : public UniformDataBase
{
    float value[3];

    void set();
};

///\private
struct UniformData4f : public UniformDataBase
{
    float value[4];

    void set();
};


///\private
struct UniformDatafv : public UniformDataBase
{
    std::vector<float> value;
    int count = 0;
};

///\private
struct UniformData1fv : public UniformDatafv
{
    void set();
};

///\private
struct UniformData2fv : public UniformDatafv
{
    void set();
};

///\private
struct UniformData3fv : public UniformDatafv
{
    void set();
};

///\private
struct UniformData4fv : public UniformDatafv
{
    void set();
};


///\private
struct UniformData1i : public UniformDataBase
{
    int value;

    void set();
};

///\private
struct UniformData2i : public UniformDataBase
{
    int value[2];

    void set();
};

///\private
struct UniformData3i : public UniformDataBase
{
    int value[3];

    void set();
};

///\private
struct UniformData4i : public UniformDataBase
{
    int value[4];

    void set();
};

///\private
struct UniformData1iv : public UniformDataBase
{
    std::vector<int> value;

    void set();
};

///\private
struct UniformDataMatrix2f : public UniformDataBase
{
    float value[4];

    void set();
};

///\private
struct UniformDataMatrix3f : public UniformDataBase
{
    float value[9];

    void set();
};

///\private
struct UniformDataMatrix4f : public UniformDataBase
{
    float value[16];

    void set();
};

///\private
struct UniformDataMatrixfv : public UniformDataBase
{
    std::vector<float> value;
    int count = 0;
};

///\private
struct UniformDataMatrix2fv : public UniformDataMatrixfv
{
    void set();
};

///\private
struct UniformDataMatrix3fv : public UniformDataMatrixfv
{
    void set();
};

///\private
struct UniformDataMatrix4fv : public UniformDataMatrixfv
{
    void set();
};


#endif