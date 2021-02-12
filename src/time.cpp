#include <time.hpp>

long long Time::millis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-st).count();
}

int Time::second()
{
    return getlocal().tm_sec;
}

int Time::minute()
{
    return getlocal().tm_min;
}

int Time::hour()
{
    return getlocal().tm_hour;
}

int Time::day()
{
    return getlocal().tm_mday;
}

int Time::month()
{
    return getlocal().tm_mon+1;
}

int Time::year()
{
    return getlocal().tm_year + 1900;
}

void Time::Reset()
{
    st = std::chrono::system_clock::now();
}

tm Time::getlocal()
{
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return *std::localtime(&now);
}

std::chrono::system_clock::time_point Time::st;