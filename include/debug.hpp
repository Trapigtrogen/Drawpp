#ifndef DPP_DEBUG_H
#define DPP_DEBUG_H
#include <iostream>

namespace dbg
{
    static void error(const char* msg){
        std::cerr << "[ERROR]: " << msg << '\n';
    }
}

#endif