#ifndef DPP_FILTER_UNIFORM_DATA_H
#define DPP_FILTER_UNIFORM_DATA_H

struct UniformDataBase
{
    unsigned int location;

    virtual void set() = 0;
};

struct UniformData1f : public UniformDataBase
{
    float value;

    void set();
};

struct UniformData2f : public UniformDataBase
{
    float value[2];

    void set();
};

struct UniformData3f : public UniformDataBase
{
    float value[3];

    void set();
};

struct UniformData4f : public UniformDataBase
{
    float value[4];

    void set();
};


struct UniformDatafv : public UniformDataBase
{
    float* value = nullptr;
    int count = 0;
};

struct UniformData1fv : public UniformDatafv
{
    void set();
};

/*struct UniformData2fv : public UniformDatafv
{
    void set();
};

struct UniformData3fv : public UniformDatafv
{
    void set();
};

struct UniformData4fv : public UniformDatafv
{
    void set();
};*/


struct UniformData1i : public UniformDataBase
{
    int value;

    void set();
};

struct UniformData2i : public UniformDataBase
{
    int value[2];

    void set();
};

struct UniformData3i : public UniformDataBase
{
    int value[3];

    void set();
};

struct UniformData4i : public UniformDataBase
{
    int value[4];

    void set();
};


struct UniformDataiv : public UniformDataBase
{
    int* value = nullptr;
    int count = 0;
};

struct UniformData1iv : public UniformDataiv
{
    void set();
};


#endif