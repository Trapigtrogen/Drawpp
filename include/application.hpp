#ifndef DPP_APPLICATION_H
#define DPP_APPLICATION_H

#include <cstdint>
#include <functional>
#include <vector>
#include <memory>
#include <random.hpp>
#include <noise.hpp>

class Window;
class DGraphics;
struct GLFWcursor;
class DImage;
class DFilter;

enum CursorStyle
{
    ARROW,
    HAND,
    CROSS,
    TEXT,
};

///Application class is the core of the program
class Application
{
    friend class DGraphics;
public:

    ///\addtogroup drawpp_application_api
    ///@{

    ///\brief Construct an application
    ///
    ///Only once instance of Application is allowed to exist while the program is running.
    ///Attempting to instantiate multiple Applications will crash the program.
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

    ///@}


    ///\brief Change the application window size
    void size(int width, int height);


    ///\brief Set the application to fullscreen mode
    ///
    ///\p monitor is the zero-based index of the display to use.
    void setFullscreen(int monitor);


    ///\brief Set the application window title
    void setTitle(const char* title);


    ///\brief Set the maximum framerate
    ///
    ///Anything below 1, will set the fps to unlimited. \n
    ///If VSync is enabled, fps is limited by monitor refresh rate, 
    ///and setting the maximum framerate above that will have no effect. \n
    void setFrameRate(int fps);


    ///\brief Enable or disable VSync
    void setVSync(bool vsync);


    ///\brief Exit application after current cycle
    void exit();


    ///\brief Set the cursor style
    void setCursor(CursorStyle c);


    ///\brief Set the cursor to an image
    void setCursor(const DImage& c, int xorigin = 0, int yorigin = 0);


    ///\brief Hide the cursor
    void hideCursor();


    ///\brief Set the window location
    ///
    ///(0,0) is at the top-left corner of the primary monitor
    void setLocation(int x, int y);


    ///\brief Get the pixel width of a monitor
    int getMonitorWidth(int monitor);


    ///\brief Get the pixel height of a monitor
    int getMonitorHeight(int monitor);


    ///\brief Get a reference to the default draw target
    DGraphics& graphics_object();


    ///\brief Get the current window width
    int getWidth() const;


    ///\brief Get the current window height
    int getHeight() const;


    ///\brief Get a pointer to the application singleton
    static Application* GetInstance();


    ///\brief Default random instance
    Random random;


    ///\brief Default noise instance
    Noise noise;

private:
    bool init_application();
    void init_filters();
    void cleanup_application();
    void resize_window(int width, int height, void* monitor);

    float min_delta = -1;

    void draw_buffer();

    std::unique_ptr<Window> window;
    std::unique_ptr<DGraphics> graphics;
    bool quit_flag = false;
    bool started = false;

    std::function<void(float)> draw_func = nullptr;
    std::function<void()> setup_func = nullptr;
    std::function<void()> cleanup_func = nullptr;

    std::vector<GLFWcursor*> std_cursors;
    GLFWcursor* custom_cursor = nullptr;

    class Shader* application_shader;
    int application_shader_vertpos_attrib = 0;
    int application_shader_texc_attrib = 0;
    int application_shader_tex_uniform = 0;

    DFilter* stock_filters = nullptr;

    static Application* instance;
};

#endif