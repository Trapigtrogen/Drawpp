#ifndef DPP_APPLICATION_H
#define DPP_APPLICATION_H

#include <cstdint>
#include <functional>
#include <memory>
#include <random.hpp>
#include <noise.hpp>

class Window;
class DGraphics;

///Application class is the core of the program
class Application
{
public:
    Application(int width = 200, int height = 200, const char* title = "Title");

    ~Application();

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


    ///\brief Set the maximum framerate
    ///
    ///Anything below 1, will set the fps to unlimited. \n
    ///If VSync is enabled, fps is limited by monitor refresh rate, 
    ///and setting the maximum framerate above that will have no effect. \n
    void setFrameRate(int fps);


    ///\brief Enable or disable VSync
    void setVSync(bool vsync);
    void exit();

    DGraphics& graphics_object();
    int getWidth() const;
    int getHeight() const;
    bool graphicsExists() const;

    static Application* GetInstance();

    Random random;
    Noise noise;

private:
    bool init_application();
    void cleanup_application();

    float min_delta = -1;

    void draw_buffer();
    
    std::unique_ptr<Window> window;
    std::unique_ptr<DGraphics> graphics;
    bool quit_flag = false;
    bool started = false;

    std::function<void(float)> draw_func = nullptr;
    std::function<void()> setup_func = nullptr;
    std::function<void()> cleanup_func = nullptr;

    static Application* instance;
};

#endif