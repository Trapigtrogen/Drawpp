#include <random.hpp>

Random::Random() : generator(std::random_device()()), gaussian(0.0f,1.0f) {}

Random::Random(int seed) : generator(seed) {}

void Random::randomSeed(int seed)
{
    generator.seed(seed);
}

int Random::random(int high)
{
    return random(0,high);
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
    return randomf(0.0f,1.0f);
}

float Random::randomf(float low, float high)
{
    funiform.param(std::uniform_real_distribution<float>::param_type(low,high));
    return funiform(generator);
}

float Random::randomGaussian()
{
    return gaussian(generator);
}