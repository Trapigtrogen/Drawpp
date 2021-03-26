#ifndef DPP_WINDOW_H
#define DPP_WINDOW_H

struct GLFWwindow;

///\private
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