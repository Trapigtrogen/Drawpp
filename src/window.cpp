#include <window.hpp>
#include <debug.hpp>

bool Window::Init()
{
    if(glfwInit() == GLFW_FALSE)
    {
        dbg::error("glfwInit failed");
        return false;
    }

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