#ifndef DPP_WINDOW_H
#define DPP_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window
{
public:

    struct WindowProperties
    {
        const char* title = "Drawpp Application";
        int width_hint = 200;
        int height_hint = 200;
        int width = 200;
        int height = 200;
        bool resizable = false;
    };

    GLFWwindow* GetHandle();
    bool Init();
    void Cleanup();

    WindowProperties properties;

private:
    GLFWwindow* handle = nullptr;
};

#endif