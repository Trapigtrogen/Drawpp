#ifndef DPP_DEBUG_H
#define DPP_DEBUG_H
#include <iostream>

namespace dbg
{
    template<class T>
    static void print(T arg)
    {
        std::cerr << arg << '\n';
    }

    template<class U, class... T>
    static void print(U arg, T... args)
    {
        std::cerr << arg;
        print(args...);
    }

    template<class... T>
    static void error(T... args){
        print("[ERROR]: ",args...);
    }

    template<class... T>
    static void message(T... args){
        print("[DEBUG]: ",args...);
    }
}

#endif