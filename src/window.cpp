#include <window.hpp>
#include <debug.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>

bool Window::Init()
{
    if(glfwInit() == GLFW_FALSE)
    {
        dbg::error("glfwInit failed");
        return false;
    }

    properties.width    = properties.width_hint;
    properties.height   = properties.height_hint;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    handle = glfwCreateWindow(properties.width, 
                              properties.height, 
                              properties.title, 
                              NULL, NULL);

    if(!handle)
    {
        dbg::error("Window creation failed");
        return false;
    }

    glfwMakeContextCurrent(handle);
    
    if(!gladLoadGL())
    {
        dbg::error("gladLoadGL failed");
        return false;
    }

    return true;
}

void Window::Cleanup()
{
    glfwDestroyWindow(handle);
    glfwTerminate();
}

GLFWwindow* Window::GetHandle()
{
    return handle;
}