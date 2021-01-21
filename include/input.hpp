#ifndef DPP_INPUT_H
#define DPP_INPUT_H

#include <vector>

struct GLFWwindow;

class Input
{
public:
    static void keyboard_callback(GLFWwindow*,int,int,int,int);
};

#endif