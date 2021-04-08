#include <input.hpp>
#include <GLFW/glfw3.h>
#include <debug.hpp>
#include <keys.hpp>

char key = '\0';
int keyCode;

int mouseButton = 0;
bool mousePressed = false;

int mouseX = 0;
int mouseY = 0;
int pmouseX = 0;
int pmouseY = 0;
int pfmouseX = 0;
int pfmouseY = 0;

void Input::keyboard_callback(GLFWwindow*, int keyc, int, int action, int)
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

void Input::mousebtn_callback(GLFWwindow*,int button, int action, int)
{
    mouseButton = button + KeyID::MOUSE_LEFT;

    if(action == GLFW_PRESS)
    {
        mouseBtnStates[button] = true;

        if(mousePressed_func)
        {
            mousePressed_func();
        }

        mouseBtnCount += 1;
    }
    else if(action == GLFW_RELEASE)
    {
        bool prev = mouseBtnStates[button];
        mouseBtnStates[button] = false;

        if(prev && mouseClicked_func)
        {
            mouseClicked_func();
        }
        
        if(mouseReleased_func)
        {
            mouseReleased_func();
        }

        mouseBtnCount -= 1;
        mousePressed = mouseBtnCount > 0;
    }
}

void Input::mousewhl_callback(GLFWwindow*,double, double yoffset)
{
    if(mouseWheel_func)
    {
        mouseWheel_func(yoffset);
    }
}

void Input::mousemov_callback(GLFWwindow*,double xpos,double ypos)
{
    pmouseX = mouseX;
    pmouseY = mouseY;

    mouseX = (int)xpos;
    mouseY = (int)ypos;

    if(mouseBtnCount > 0 && mouseDragged_func)
    {
        mouseDragged_func();
    }
    else if(mouseBtnCount == 0 && mouseMoved_func)
    {
        mouseMoved_func();
    }
}

void Input::setPrevMouse()
{
    pfmouseX = mouseX;
    pfmouseY = mouseY;
}

std::function<void()> Input::keyPressed_func = nullptr;
std::function<void()> Input::keyReleased_func = nullptr;

std::function<void()> Input::mouseClicked_func = nullptr;
std::function<void()> Input::mousePressed_func = nullptr;
std::function<void()> Input::mouseReleased_func = nullptr;
std::function<void(float)> Input::mouseWheel_func = nullptr;
std::function<void()> Input::mouseMoved_func = nullptr;
std::function<void()> Input::mouseDragged_func = nullptr;

bool Input::mouseBtnStates[8] = {false};
int Input::mouseBtnCount = 0;