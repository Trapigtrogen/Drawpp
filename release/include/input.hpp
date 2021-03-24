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
    static void mousebtn_callback(GLFWwindow*,int,int,int);
    static void mousewhl_callback(GLFWwindow*,double,double);
    static void mousemov_callback(GLFWwindow*,double,double);

    static std::function<void()> keyPressed_func;
    static std::function<void()> keyReleased_func;

    static std::function<void()> mouseClicked_func;
    static std::function<void()> mousePressed_func;
    static std::function<void()> mouseReleased_func;
    static std::function<void(float)> mouseWheel_func;
    static std::function<void()> mouseMoved_func;
    static std::function<void()> mouseDragged_func;

    static void setPrevMouse();


    static bool mouseBtnStates[8];
    static int mouseBtnCount;
};

#endif