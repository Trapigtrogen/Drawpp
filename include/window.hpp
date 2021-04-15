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
        int width_hint = 300;
        int height_hint = 300;
        int width = 300;
        int height = 300;
        bool resizable = false;
        bool fullscreen = false;
        void* fullscreen_monitor = nullptr;
    };

    GLFWwindow* GetHandle();
    bool Init();
    void Cleanup();

    WindowProperties properties;

private:
    GLFWwindow* handle = nullptr;
};

#endif