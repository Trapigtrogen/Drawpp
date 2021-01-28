#include <application.hpp>
#include <drawpp.hpp>

void size(int width, int height)
{
    Application::GetInstance()->size(width,height);
}

void setTitle(const char* title)
{
    Application::GetInstance()->setTitle(title);
}

void setResizable(bool state)
{
    Application::GetInstance()->setResizable(state);
}

void exit()
{
    Application::GetInstance()->exit();
}

void randomSeed(int seed)
{
    Application::GetInstance()->random.randomSeed(seed);
}

int random(int high)
{
    return Application::GetInstance()->random.random(high);
}

int random(int low, int high)
{
    return Application::GetInstance()->random.random(low,high);
}

float random()
{
    return Application::GetInstance()->random.random();
}

float randomf(float low, float high)
{
    return Application::GetInstance()->random.randomf(low,high);
}

float randomGaussian()
{
    return Application::GetInstance()->random.randomGaussian();
}
