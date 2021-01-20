#include <application.hpp>
#include <drawpp.hpp>

void runApp()
{
    Application::InitInstance();

    Application::GetInstance()->start_application();
}