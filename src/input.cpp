#include <input.hpp>
#include <GLFW/glfw3.h>
#include <debug.hpp>

char key = '\0';

void Input::keyboard_callback(GLFWwindow* window, int keyc, int scancode, int action, int mods)
{
    key = keyc+32;
    //call application keyPresssed
}