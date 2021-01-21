#include <application.hpp>
#include <debug.hpp>
#include <drawpp.hpp>
#include <window.hpp>
#include <input.hpp>

Application::Application(int width, int height, const char* title)
{
    if(instance == nullptr)
    {
        instance = this;
    }
    else
    {
        dbg::error("Only one Application instance is allowed");
        exit(1);
    }
    window = new Window();

    window->properties.width = width>-1?width:window->properties.width;
    window->properties.height = height>-1?height:window->properties.height;
    window->properties.title = title;

}

int Application::run(std::function<void(float)> draw,
                      std::function<void()> setup,
                      std::function<void()> cleanup)
{
    draw_func = draw;
    setup_func = setup;
    cleanup_func = cleanup;

    if(!init_application())
    {
        return 1;
    }

    while(!quit_flag)
    {
        glfwPollEvents();

        draw_func(1);
    }

    cleanup_application();

    return 0;
}


void Application::size(int width, int height)
{
    window->properties.width = width>-1?width:window->properties.width;
    window->properties.height = height>-1?height:window->properties.height;
    if(window && window->properties.resizable)
    {
        glfwSetWindowSize(window->GetHandle(),width,height);
    }
}

void Application::setResizable(bool state)
{
    if(!window)
    {
        window->properties.resizable = state;
    }
}

void Application::setTitle(const char* title)
{
    window->properties.title = title;
    if(window)
    {
        glfwSetWindowTitle(window->GetHandle(),title);
    }
}

bool Application::init_application()
{
    if(!window->Init())
    {
        return false;
    }

    glfwSetKeyCallback(window->GetHandle(),&Input::keyboard_callback);
    setup_func();

    return true;
}

void Application::cleanup_application()
{
    cleanup_func();
    window->Cleanup();
    delete window;
}

Application* Application::instance = nullptr;