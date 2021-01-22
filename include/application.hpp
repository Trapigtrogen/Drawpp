#ifndef DPP_APPLICATION_H
#define DPP_APPLICATION_H

#include <cstdint>
#include <functional>

class Window;

class Application
{
public:
    Application(int width = 200, int height = 200, const char* title = "Title");

    int run(std::function<void(float)> draw, std::function<void()> setup = [](){}, std::function<void()> cleanup = [](){});

    void setKeyPressed(std::function<void()>);
    void setKeyReleased(std::function<void()>);

    //virtual void keyPressed();
    void size(int width, int height);
    void setResizable(bool);
    void setTitle(const char* title);

    static Application* GetInstance()
    {
        return instance;
    }

private:
    bool init_application();
    void cleanup_application();
    
    Window* window;
    bool quit_flag = false;

    std::function<void(float)> draw_func;
    std::function<void()> setup_func;
    std::function<void()> cleanup_func;

    static Application* instance;
};

#endif