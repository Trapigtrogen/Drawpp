#include <application.hpp>
#include <debug.hpp>
#include <drawpp.hpp>

void Application::start_application()
{
    if(!init_application())
    {
        return;
    }

    while(!quit_flag)
    {
        glfwPollEvents();

        draw();
    }

    cleanup_application();
}

void Application::setup()
{
    ::setup();
}

void Application::draw()
{
    ::draw();
}

void Application::size(int width, int height)
{
    window_properties.width = width;
    window_properties.height = height;
    if(window && window_properties.resizable)
    {
        glfwSetWindowSize(window,width,height);
    }
}

void Application::setResizable(bool state)
{
    window_properties.resizable = state;
}

void Application::setTitle(const char* title)
{
    window_properties.title = title;
    if(window)
    {
        glfwSetWindowTitle(window,title);
    }
}

bool Application::init_application()
{
    setup();

    if(glfwInit() == GLFW_FALSE)
    {
        dbg::error("glfwInit failed");
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(window_properties.width, 
                              window_properties.height, 
                              window_properties.title, 
                              NULL, NULL);

    if(!window)
    {
        dbg::error("Window creation failed");
        return false;
    }

    glfwMakeContextCurrent(window);
    
    if(!gladLoadGL())
    {
        dbg::error("gladLoadGL failed");
        return false;
    }

    return true;
}

void Application::cleanup_application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

Application* Application::instance = nullptr;