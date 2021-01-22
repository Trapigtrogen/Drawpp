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
            //these keys should be within ascii range
            case GLFW_KEY_BACKSPACE: keyCode = VK_BACKSPACE, key = keyCode; break;
            case GLFW_KEY_TAB:       keyCode = VK_TAB, key = keyCode; break;
            case GLFW_KEY_ENTER:     keyCode = VK_ENTER, key = keyCode; break;
            case GLFW_KEY_ESCAPE:    keyCode = VK_ESC, key = keyCode; break;
            case GLFW_KEY_DELETE:    keyCode = VK_DELETE, key = keyCode; break;

            //rest of keys -> coded
            default:                 keyCode = keyc, key = CODED; break;
        }
    }
    //convert alphabeticals to lower case
    else if(keyc > 0x40 && keyc < 0x5B)
    {
        keyCode = keyc+32;
        key = keyCode;
    }
    //rest are ascii
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