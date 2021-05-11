#include <application.hpp>
#include <debug.hpp>
#include <drawpp.hpp>
#include <window.hpp>
#include <input.hpp>
#include <shader.hpp>
#include <graphics.hpp>
#include <image.hpp>
#include <time.hpp>
#include <font.hpp>
#include <chrono>
#include <thread>
#include <cstring>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>
#include <filter.h>

static float quad_coords[] = 
{
    -1.0f, -1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f,  1.0f,
    -1.0f,  1.0f,
};

static float quadtex_coords[] = 
{
    0.0f, 0.0f,
    1.0f, 0.0f, 
    1.0f, 1.0f, 
    0.0f, 0.0f, 
    1.0f, 1.0f, 
    0.0f, 1.0f, 
};

static const char* quad_shader_v = R"(#version 100
precision mediump float;
attribute vec2 pos;
attribute vec2 texpos;
varying vec2 texc;
void main()
{
    texc = texpos;
    gl_Position = vec4(pos,0.0,1.0);
}
)";

static const char* quad_shader_f = R"(#version 100
precision mediump float;
uniform sampler2D texture;
varying vec2 texc;
void main()
{
    //gl_FragColor = vec4(1.0,0,0,1.0);
    gl_FragColor = texture2D(texture,texc);
}
)";

bool focused;
unsigned long long frameCount;

void windowclose_cb(GLFWwindow*)
{
    Application::GetInstance()->exit();
}

void window_focus_callback(GLFWwindow*,int f)
{
    focused = f;
}

Application::Application(int width, int height, const char* title)
{
    if(instance == nullptr)
    {
        instance = this;
    }
    else
    {
        dbg::error("Only one Application instance is allowed");
        ::exit(1);
    }
    window = std::unique_ptr<Window>(new Window);

    window->properties.width_hint = width>-1?width:window->properties.width_hint;
    window->properties.height_hint = height>-1?height:window->properties.height_hint;
    window->properties.title = title;
}

Application::~Application()
{
    instance = nullptr;
}

int Application::run(std::function<void(float)> draw,
                      std::function<void()> setup,
                      std::function<void()> cleanup)
{
    if(!draw)
    {
        draw_func = [](float f){};
    }
    else
    {
        draw_func = draw;
    }
    setup_func = setup;
    cleanup_func = cleanup;

    if(!init_application())
    {
        return 1;
    }

    started = true;

    std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();

    float delta = 0;

    while(!quit_flag)
    {
        Input::setPrevMouse();
        glfwPollEvents();

        delta = std::chrono::duration<float>(std::chrono::steady_clock::now()-st).count();

        if(min_delta < 0 || min_delta < delta)
        {
            draw_func(delta);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::duration<float>(min_delta-delta));
            draw_func(min_delta);
        }

        st = std::chrono::steady_clock::now();

        draw_buffer();

        glfwSwapBuffers(window->GetHandle());

        ++frameCount;
    }

    cleanup_application();

    delete[] stock_filters;
    delete application_shader;

    glfwDestroyCursor(custom_cursor);
    custom_cursor = nullptr;

    return 0;
}

void Application::setKeyPressed(std::function<void()> fun)
{
    Input::keyPressed_func = fun;
}

void Application::setKeyReleased(std::function<void()> fun)
{
    Input::keyReleased_func = fun;
}

void Application::setMouseClicked(std::function<void()> fun)
{
    Input::mouseClicked_func = fun;
}

void Application::setMousePressed(std::function<void()> fun)
{
    Input::mousePressed_func = fun;
}

void Application::setMouseReleased(std::function<void()> fun)
{
    Input::mouseReleased_func = fun;
}

void Application::setMouseWheel(std::function<void(float)> fun)
{
    Input::mouseWheel_func = fun;
}

void Application::setMouseMoved(std::function<void()> fun)
{
    Input::mouseMoved_func = fun;
}

void Application::setMouseDragged(std::function<void()> fun)
{
    Input::mouseDragged_func = fun;
}


void Application::size(int width, int height)
{
    window->properties.width_hint = width>-1?width:window->properties.width_hint;
    window->properties.height_hint = height>-1?height:window->properties.height_hint;

    resize_window(window->properties.width_hint,window->properties.height_hint,nullptr);
    window->properties.fullscreen = false;
}

void Application::setFullscreen(int monitor)
{
    int num_monitors;
    GLFWmonitor** monitors = glfwGetMonitors(&num_monitors);

    if(monitor >= num_monitors || monitor < 0)
    {
        monitor = 0;
    }

    GLFWmonitor* monitor_handle = monitors[monitor];
    const GLFWvidmode* mode = glfwGetVideoMode(monitor_handle);

    window->properties.fullscreen = true;
    window->properties.fullscreen_monitor = monitor_handle;

    resize_window(mode->width,mode->height,monitor_handle);
}

void Application::resize_window(int width, int height, void* monitor)
{
    GLFWmonitor* monitor_handle = static_cast<GLFWmonitor*>(monitor);

    window->properties.width  = width;
    window->properties.height = height;

    std::unique_ptr<DGraphics> ngraphics = 
        std::unique_ptr<DGraphics>(new DGraphics(window->properties.width,window->properties.height));
    
    ngraphics->properties = graphics->properties;
    ngraphics->property_stack = graphics->property_stack;
    ngraphics->transform_mat = graphics->transform_mat;
    ngraphics->matrix_stack = graphics->matrix_stack;

    graphics = std::move(ngraphics);

    if(!monitor_handle && window->properties.fullscreen)
    {
        GLFWmonitor* cur_mon = static_cast<GLFWmonitor*>(window->properties.fullscreen_monitor);
        int mx,my;
        glfwGetMonitorPos(cur_mon,&mx,&my);
        const GLFWvidmode* mode = glfwGetVideoMode(cur_mon);

        window->properties.fullscreen_monitor = nullptr;
        glfwSetWindowMonitor(window->GetHandle(), 
                             monitor_handle,
                             mx + (mode->width-width)/2,
                             my + (mode->height-height)/2,
                             width,height,GLFW_DONT_CARE);
    }
    else if(monitor_handle)
    {
        glfwSetWindowMonitor(window->GetHandle(), monitor_handle, 0,0, width,height,GLFW_DONT_CARE);
    }
    else
    {
        glfwSetWindowSize(window->GetHandle(),width,height);
    }
}

void Application::setTitle(const char* title)
{
    window->properties.title = title;
    if(window)
    {
        glfwSetWindowTitle(window->GetHandle(),title);
    }
}

void Application::setFrameRate(int fps)
{
    if(fps < 1)
    {
        min_delta = -1;
        return;
    }

    min_delta = 1.0/(fps+1);
}

void Application::setVSync(bool vsync)
{
    glfwSwapInterval(vsync);
}

void Application::exit()
{
    quit_flag = true;
}

void Application::setCursor(CursorStyle c)
{
    glfwSetCursor(window->GetHandle(),std_cursors[c]);
    glfwSetInputMode(window->GetHandle(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
}

void Application::setCursor(const DImage& c, int xorigin, int yorigin)
{
    GLFWimage img;
    img.height = c.height();
    img.width = c.width();
    img.pixels = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(c.pixels()));

    GLFWcursor* curs = glfwCreateCursor(&img,xorigin,yorigin);

    if(curs)
    {
        glfwSetCursor(window->GetHandle(),curs);
        glfwDestroyCursor(custom_cursor);
        custom_cursor = curs;
        glfwSetInputMode(window->GetHandle(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    }
}

void Application::hideCursor()
{
    glfwSetInputMode(window->GetHandle(),GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
}

DGraphics& Application::graphics_object()
{
    return *graphics;
}

int Application::getWidth() const
{
    if(window) 
    {
        return window->properties.width;
    }
    return -1;
}

int Application::getHeight() const
{
    if(window)   
    {
        return window->properties.height;
    }
    return -1;
}

bool Application::init_application()
{
    if (!window->Init())
    {
        return false;
    }

    application_shader = new Shader(Shader::loadShadersFromString(quad_shader_v,quad_shader_f));
    application_shader_vertpos_attrib = glGetAttribLocation(application_shader->getId(),"pos");
    application_shader_texc_attrib = glGetAttribLocation(application_shader->getId(),"texpos");
    application_shader_tex_uniform = glGetUniformLocation(application_shader->getId(),"texture");
    
    graphics = std::unique_ptr<DGraphics>(
            new DGraphics(
                window->properties.width,
                window->properties.height
            ));

    init_filters();
            
    glfwSetKeyCallback(         window->GetHandle(),Input::keyboard_callback);
    glfwSetMouseButtonCallback( window->GetHandle(),Input::mousebtn_callback);
    glfwSetScrollCallback(      window->GetHandle(),Input::mousewhl_callback);
    glfwSetCursorPosCallback(   window->GetHandle(),Input::mousemov_callback);
    glfwSetWindowCloseCallback( window->GetHandle(),windowclose_cb);
    glfwSetWindowFocusCallback( window->GetHandle(),window_focus_callback);

    std_cursors.push_back(glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
    std_cursors.push_back(glfwCreateStandardCursor(GLFW_HAND_CURSOR));
    std_cursors.push_back(glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR));
    std_cursors.push_back(glfwCreateStandardCursor(GLFW_IBEAM_CURSOR));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    DFont::init_lib();

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        reinterpret_cast<GLint*>(&DImage::max_texture_units));

    graphics->beginDraw();
    
    Time::Reset();

    if(setup_func)
    {
        setup_func();
    }
    
    return true;
}

void Application::init_filters()
{
    //should be the number of items in filters enum
    constexpr unsigned int num_filters = 4;

    stock_filters = new DFilter[num_filters];

    stock_filters[filters::PIXELATE] = DFilter::loadFilter(R"(
    uniform float scale;
    void main()
    {
        vec2 pos = gl_FragCoord.xy/source_size;
        pos -= mod(pos, vec2(scale) / source_size);
        gl_FragColor = texture2D(source, pos);
    })");

    stock_filters_pixelate_scale_location = 
        glGetUniformLocation(stock_filters[0].getProgram(),"scale");


    stock_filters[filters::INVERT] = DFilter::loadFilter(R"(
    void main()
    {
        gl_FragColor = vec4(vec3(1.0) - texture2D(source, gl_FragCoord.xy/source_size).rgb,1.0);
    })");


    stock_filters[filters::GREY] = DFilter::loadFilter(R"(
    void main()
    {
        vec3 col = texture2D(source, gl_FragCoord.xy/source_size).rgb;
        float val = (col.x + col.y + col.z)/3.0;
        gl_FragColor = vec4(vec3(val),1.0);
    })");


    stock_filters[filters::THRESHOLD] = DFilter::loadFilter(R"(
    uniform float threshold;
    void main()
    {
        vec3 col = texture2D(source, gl_FragCoord.xy/source_size).rgb;
        float val = (col.x + col.y + col.z)/3.0;

        if(val <= threshold)
        {
            gl_FragColor = vec4(vec3(0.0),1.0);
        }
        else
        {
            gl_FragColor = vec4(1.0);
        }
    })");

    stock_filters_treshold_value_location = 
        glGetUniformLocation(stock_filters[filters::THRESHOLD].getProgram(),"threshold");
}

void Application::cleanup_application()
{
    if(cleanup_func)
    {
        cleanup_func();
    }

    for(auto c : std_cursors)
    {
        glfwDestroyCursor(c);
    }
    
    if(custom_cursor)
    {
        glfwDestroyCursor(custom_cursor);
    }

    window->Cleanup();
    
    window.reset();
    graphics.reset();

    DFont::cleanup_lib();
}

Application* Application::GetInstance()
{
    return instance;
}

void Application::draw_buffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0,window->properties.width,window->properties.height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //bind shader, texture, and draw quad with the texture
    glUseProgram(application_shader->getId());
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,graphics->get_texture_id());
    glUniform1i(application_shader_tex_uniform,0);

    glEnableVertexAttribArray(application_shader_vertpos_attrib);
    glEnableVertexAttribArray(application_shader_texc_attrib);

    glVertexAttribPointer(application_shader_texc_attrib,2,GL_FLOAT,false,0, quadtex_coords);
    glVertexAttribPointer(application_shader_vertpos_attrib,2,GL_FLOAT,false,0, quad_coords);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(application_shader_vertpos_attrib);
    glDisableVertexAttribArray(application_shader_texc_attrib);
    
    glBindTexture(GL_TEXTURE_2D,0);

    graphics->beginDraw();
}

Application* Application::instance = nullptr;