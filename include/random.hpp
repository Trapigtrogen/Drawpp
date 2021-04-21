#ifndef DPP_RANDOM_H
#define DPP_RANDOM_H

#include <random>

///\brief Random number generator
class Random
{
public:

    ///\brief Initialize with random seed
    Random();


    ///\brief Initialize with \p seed
    Random(int seed);


    ~Random() = default;


    ///\brief Set generator seed to \p seed
    void randomSeed(int seed);


    ///\brief Generate an int in range [0, \p high ]
    int randomInt(int high);


    ///\brief Generate an int in range [ \p low, \p high ]
    int randomInt(int low, int high);


    ///\brief Generate a float in range [ 0.0, 1.0 )
    float randomFloat01();


    ///\brief Generate a float in range [ \p low, \p high )
    float randomFloat(float low, float high);


    ///\brief Generate a float in a gaussian distribution
    ///
    ///Distribution mean is 0.0, and standard deviation is 1.0
    float randomGaussian();

private:

    std::mt19937 generator;

    std::normal_distribution<float> gaussian;
    std::uniform_int_distribution<int> uniform;
    std::uniform_real_distribution<float> funiform;

    //keep track of distribution parameters, so when random is called
    //again with same parameters, no need to re-set them
    int min = 0;
    int max = 1;
};

#endif