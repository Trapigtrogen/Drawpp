#include <application.hpp>
#include <drawpp.hpp>

void runApp()
{
    Application::InitInstance();

    Application::GetInstance()->start_application();
}

void size(int width, int height)
{
    Application::GetInstance()->size(width,height);
}

void setTitle(const char* title)
{
    Application::GetInstance()->setTitle(title);
}

void setResizable(bool state)
{
    Application::GetInstance()->setResizable(state);
}