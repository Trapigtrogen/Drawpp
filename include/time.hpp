#ifndef DPP_TIME_H
#define DPP_TIME_H

#include <chrono>
#include <ctime>

///\brief Time class
class Time
{
public:
    
    ///\brief Get count of milliseconds since last reset
    ///
    ///Time is reset right before setup is called.
    static long long millis();


    ///\brief Get the current second
    ///
    ///In range [0,59].
    static int second();


    ///\brief Get the current minute
    ///
    ///In range [0,59].
    static int minute();


    ///\brief Get the current hour
    ///
    ///In range [0,23].
    static int hour();


    ///\brief Get the current day
    ///
    ///In range [1,31].
    static int day();


    ///\brief Get the current month
    ///
    ///In range [1,12].
    static int month();


    ///\brief Get the current year
    static int year();


    ///\brief Reset the point where millis() counts from
    static void Reset();

private:
    static tm getlocal();
    static std::chrono::system_clock::time_point st;
};

#endif