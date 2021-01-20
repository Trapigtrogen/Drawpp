#ifndef DPP_APPLICATION_H
#define DPP_APPLICATION_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cstdint>
#include <string>

struct WindowProperties
{
    const char* title = "Drawpp Application";
    int width = 200;
    int height = 200;
    bool resizable = false;
};

class Application
{
public:
    void start_application();

    virtual void setup();
    virtual void draw();
    //virtual void keyPressed();
    void size(int width, int height);
    void setResizable(bool);
    void setTitle(const char* title);

    static Application* GetInstance()
    {
        return instance;
    }

    static void InitInstance()
    {
        if(instance == nullptr)
        {
            instance = new Application();
        }
    }

private:
    bool init_application();
    void cleanup_application();
    
    GLFWwindow* window = nullptr;
    WindowProperties window_properties;
    bool quit_flag = false; 

    static Application* instance;
};

#endif