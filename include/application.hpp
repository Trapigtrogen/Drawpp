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

    ///\brief Run the application
    ///
    ///If you don't need the draw function, you can pass a nullptr as the draw function.
    int run(std::function<void(float)> draw, std::function<void()> setup = [](){}, std::function<void()> cleanup = [](){});
    

    ///\brief Set the KeyPressed callback
    void setKeyPressed(std::function<void()>);


    ///\brief Set the KeyReleased callback
    void setKeyReleased(std::function<void()>);


    ///\brief Set the MouseClicked callback
    void setMouseClicked(std::function<void()>);
    

    ///\brief Set the MousePressed callback
    void setMousePressed(std::function<void()>);
    

    ///\brief Set the MouseReleased callback
    void setMouseReleased(std::function<void()>);
    

    ///\brief Set the MouseWheel callback
    void setMouseWheel(std::function<void(float)>);
    

    ///\brief Set the MouseMoved callback
    void setMouseMoved(std::function<void()>);
    

    ///\brief Set the MouseDragged callback
    void setMouseDragged(std::function<void()>);


    ///\brief Change the application window size
    void size(int width, int height);


    ///\brief Set the allowance of resizing
    ///
    ///Only effective in setup.
    void setResizable(bool);


    ///\brief Set the application window title
    void setTitle(const char* title);


    ///\brief Exit the application
    ///
    ///Calling exit() will not immideately quit, instead the application will quit after the current cycle is finished.
    void exit();


    ///\brief Get the current window width
    int getWidth();


    ///\brief Get the current window height
    int getHeight();

    ///\private
    DGraphics& graphics_object();


    ///\private
    bool graphicsExists();


    ///\private
    static Application* GetInstance();


    ///\brief Default random instance
    Random random;


    ///\brief Default noise instance
    Noise noise;

private:
    bool init_application();
    void cleanup_application();

    void draw_buffer();
    
    std::unique_ptr<Window> window;
    std::unique_ptr<DGraphics> graphics = nullptr;
    bool quit_flag = false;
    bool started = false;

    std::function<void(float)> draw_func = nullptr;
    std::function<void()> setup_func = nullptr;
    std::function<void()> cleanup_func = nullptr;

    static Application* instance;
};

#endif