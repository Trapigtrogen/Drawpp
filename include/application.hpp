#ifndef DPP_APPLICATION_H
#define DPP_APPLICATION_H

#include <cstdint>
#include <functional>
#include <random.hpp>

#include <image.hpp>
#include <shader.hpp>
#include <shape.hpp>
#include <color.hpp>

class Window;

///Application class is the core of the program
class Application
{
public:
    Application(int width = 200, int height = 200, const char* title = "Title");

    int run(std::function<void(float)> draw, std::function<void()> setup = [](){}, std::function<void()> cleanup = [](){});

    void setKeyPressed(std::function<void()>);
    void setKeyReleased(std::function<void()>);

    void setMouseClicked(std::function<void()>);
    void setMousePressed(std::function<void()>);
    void setMouseReleased(std::function<void()>);
    void setMouseWheel(std::function<void(float)>);
    void setMouseMoved(std::function<void()>);
    void setMouseDragged(std::function<void()>);

    //virtual void keyPressed();
    void size(int width, int height);
    void setResizable(bool);
    void setTitle(const char* title);
    void exit();

    static Application* GetInstance();

    Random random;

private:
    bool init_application();
    void cleanup_application();
    
    Window* window;
    bool quit_flag = false;
    bool started = false;

    std::function<void(float)> draw_func;
    std::function<void()> setup_func;
    std::function<void()> cleanup_func;

    static Application* instance;
};

#endif