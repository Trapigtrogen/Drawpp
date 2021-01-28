#include <random.hpp>

Random::Random() : generator(std::random_device()()), gaussian(0.0f,1.0f) {}

Random::Random(int seed) : generator(seed) {}

void Random::randomSeed(int seed)
{
    generator.seed(seed);
}

int Random::random(int high)
{
    if(max != high || min != 0)
    {
        max = high;
        min = 0;
        uniform.param(std::uniform_int_distribution<int>::param_type(0,high));
    }

    return uniform(generator);
}

int Random::random(int low, int high)
{
    if(max != high || min != low)
    {
        max = high;
        min = low;
        uniform.param(std::uniform_int_distribution<int>::param_type(low,high));
    }

    return uniform(generator);
}

float Random::random()
{
    if(std::abs(fmax-1.0f) > std::numeric_limits<float>::epsilon() || 
        std::abs(fmin) > std::numeric_limits<float>::epsilon())
    {
        max = 1.0f;
        min = 0.0f;
        funiform.param(std::uniform_real_distribution<float>::param_type(0.0f,1.0f));
    }

    return funiform(generator);
}

float Random::randomf(float low, float high)
{
    if(std::abs(fmax-high) > std::numeric_limits<float>::epsilon() || 
        std::abs(fmin-low) > std::numeric_limits<float>::epsilon())
    {
        max = high;
        min = low;
        funiform.param(std::uniform_real_distribution<float>::param_type(low,high));
    }

    return funiform(generator);
}

float Random::randomGaussian()
{
    return gaussian(generator);
}