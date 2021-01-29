#include <application.hpp>
#include <debug.hpp>
#include <drawpp.hpp>
#include <window.hpp>
#include <input.hpp>
#include <primitives.hpp>
#include <chrono>

void windowclose_cb(GLFWwindow* window)
{
    Application::GetInstance()->exit();
}

Application::Application(int width, int height, const char* title)
{
    if(instance == nullptr)
    {
        instance = this;
    }
    else
    {
        dbg::error("Only one Application instance is allowed");
        ::exit(1);
    }
    window = new Window();

    window->properties.width_hint = width>-1?width:window->properties.width_hint;
    window->properties.height_hint = height>-1?height:window->properties.height_hint;
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

    std::chrono::system_clock::time_point st = std::chrono::system_clock::now();

    while(!quit_flag)
    {
        glfwSwapBuffers(window->GetHandle());
        glfwPollEvents();

        draw_func(std::chrono::duration<float>(std::chrono::system_clock::now()-st).count());
        st = std::chrono::system_clock::now();

        draw_buffer();
        glfwSwapBuffers(window->GetHandle());
    }

    cleanup_application();

    return 0;
}

void Application::setKeyPressed(std::function<void()> fun)
{
    Input::keyPressed_func = fun;
}

void Application::setKeyReleased(std::function<void()> fun)
{
    Input::keyReleased_func = fun;
}

void Application::setMouseClicked(std::function<void()> fun)
{
    Input::mouseClicked_func = fun;
}

void Application::setMousePressed(std::function<void()> fun)
{
    Input::mousePressed_func = fun;
}

void Application::setMouseReleased(std::function<void()> fun)
{
    Input::mouseReleased_func = fun;
}

void Application::setMouseWheel(std::function<void(float)> fun)
{
    Input::mouseWheel_func = fun;
}

void Application::setMouseMoved(std::function<void()> fun)
{
    Input::mouseMoved_func = fun;
}

void Application::setMouseDragged(std::function<void()> fun)
{
    Input::mouseDragged_func = fun;
}


void Application::size(int width, int height)
{
    window->properties.width_hint = width>-1?width:window->properties.width_hint;
    window->properties.height_hint = height>-1?height:window->properties.height_hint;
    
    if(window && window->properties.resizable)
    {
        window->properties.width    = window->properties.width_hint;
        window->properties.height   = window->properties.height_hint;
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

void Application::exit()
{
    quit_flag = true;
}

bool Application::init_application()
{
    if(!window->Init())
    {
        return false;
    }

    glfwSetKeyCallback(         window->GetHandle(),&Input::keyboard_callback);
    glfwSetMouseButtonCallback( window->GetHandle(),&Input::mousebtn_callback);
    glfwSetScrollCallback(      window->GetHandle(),&Input::mousewhl_callback);
    glfwSetCursorPosCallback(   window->GetHandle(),&Input::mousemov_callback);
    glfwSetWindowCloseCallback( window->GetHandle(),&windowclose_cb);

    if(setup_func)
    {
        setup_func();
    }

    return true;
}

void Application::cleanup_application()
{
    if(cleanup_func)
    {
        cleanup_func();
    }

    window->Cleanup();
    
    delete window;
}

Application* Application::GetInstance()
{
    return instance;
}

void Application::draw_buffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0,window->properties.width,window->properties.height);

    //bind shader, texture, and draw quad with the texture
}

Application* Application::instance = nullptr;