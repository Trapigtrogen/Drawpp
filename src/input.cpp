#include <input.hpp>
#include <GLFW/glfw3.h>
#include <debug.hpp>
#include <keys.hpp>

char key = '\0';
int keyCode;

void Input::keyboard_callback(GLFWwindow* window, int keyc, int scancode, int action, int mods)
{
    if((unsigned)keyc > 0x80)
    {
        switch (keyc)
        {
            case GLFW_KEY_BACKSPACE: keyCode = 0x8, key = keyCode; break;
            case GLFW_KEY_TAB:       keyCode = 0x9, key = keyCode; break;
            case GLFW_KEY_ENTER:     keyCode = 0xA, key = keyCode; break;
            case GLFW_KEY_ESCAPE:    keyCode = 0x1B, key = keyCode; break;
            case GLFW_KEY_DELETE:    keyCode = 0x7F, key = keyCode; break;
            default:                 keyCode = keyc, key = -1; break;
        }
    }
    else if(keyc > 0x40 && keyc < 0x5B)
    {
        keyCode = keyc+32;
        key = keyCode;
    }
    else
    {
        keyCode = keyc;
        key = keyCode;
    }

    //if(action == GLFW_PRESS)  printf("%d - %d: %c\n",scancode,keyc,keyc);

    switch (action)
    {
        case GLFW_REPEAT:
        case GLFW_PRESS:   if(keyPressed_func)keyPressed_func(); break;
        case GLFW_RELEASE: if(keyReleased_func)keyReleased_func(); break;
    }
}

std::function<void()> Input::keyPressed_func = nullptr;
std::function<void()> Input::keyReleased_func = nullptr;