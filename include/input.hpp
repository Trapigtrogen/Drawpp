#ifndef DPP_INPUT_H
#define DPP_INPUT_H

#include <vector>
#include <functional>

struct GLFWwindow;

//Add option for no repeat

class Input
{
public:
    static void keyboard_callback(GLFWwindow*,int,int,int,int);

    static std::function<void()> keyPressed_func;
    static std::function<void()> keyReleased_func;
};

#endif