#include <application.hpp>
#include <drawpp.hpp>
#include <time.hpp>

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

long long millis()
{
    return Time::millis();
}

int second()
{
    return Time::second();
}

int minute()
{
    return Time::minute();
}

int hour()
{
    return Time::hour();
}

int day()
{
    return Time::day();
}

int month()
{
    return Time::month();
}

int year()
{
    return Time::year();
}

void Reset()
{
    return Time::Reset();
}