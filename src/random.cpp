#include <random.hpp>

Random::Random() : generator(std::random_device()()), gaussian(0.0f,1.0f) {}

Random::Random(int seed) : generator(seed) {}

void Random::randomSeed(int seed)
{
    generator.seed(seed);
}

int Random::randomInt(int high)
{
    return randomInt(0,high);
}

int Random::randomInt(int low, int high)
{
    if(max != high || min != low)
    {
        max = high;
        min = low;
        uniform.param(std::uniform_int_distribution<int>::param_type(low,high));
    }

    return uniform(generator);
}

float Random::randomFloat01()
{
    return randomFloat(0.0f,1.0f);
}

float Random::randomFloat(float low, float high)
{
    funiform.param(std::uniform_real_distribution<float>::param_type(low,high));
    return funiform(generator);
}

float Random::randomGaussian()
{
    return gaussian(generator);
}