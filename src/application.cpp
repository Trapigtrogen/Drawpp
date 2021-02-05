#include <application.hpp>
#include <debug.hpp>
#include <drawpp.hpp>
#include <window.hpp>
#include <input.hpp>
#include <primitives.hpp>
#include <shader.hpp>
#include <graphics.hpp>
#include <chrono>

float quad_coords[] = 
{
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
};

float quadtex_coords[] = 
{
    -1.0f, -1.0f,
     1.0f, -1.0f, 
     1.0f,  1.0f, 
    -1.0f, -1.0f, 
     1.0f,  1.0f, 
    -1.0f,  1.0f, 
};

const char* quad_shader_v = R"(#version 100
precision mediump float;
attribute vec3 pos;
attribute vec2 texpos;
varying vec2 texc;
void main()
{
    texc = texpos;
    gl_Position = vec4(pos,1.0);
}
)";

const char* quad_shader_f = R"(#version 100
precision mediump float;
uniform sampler2D texture;
varying vec2 texc;
void main()
{
    //gl_FragColor = vec4(1.0,0,0,1.0);
    gl_FragColor = texture2D(texture,texc);
}
)";

Shader* shader = nullptr;
int vertpos_attrib = 0;
int texc_attrib = 0;
int tex_uniform = 0;

void windowclose_cb(GLFWwindow* window)
{
    Application::GetInstance()->exit();
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
    window = new Window();

    window->properties.width_hint = width>-1?width:window->properties.width_hint;
    window->properties.height_hint = height>-1?height:window->properties.height_hint;
    window->properties.title = title;
}

int Application::run(std::function<void(float)> draw,
                      std::function<void()> setup,
                      std::function<void()> cleanup)
{
    draw_func = draw;
    setup_func = setup;
    cleanup_func = cleanup;

    if(!init_application())
    {
        return 1;
    }

    std::chrono::system_clock::time_point st = std::chrono::system_clock::now();

    while(!quit_flag)
    {
        glfwPollEvents();

        draw_func(std::chrono::duration<float>(std::chrono::system_clock::now()-st).count());
        st = std::chrono::system_clock::now();

        draw_buffer();

        glfwSwapBuffers(window->GetHandle());
    }

    cleanup_application();

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
    
    if(window && window->properties.resizable)
    {
        window->properties.width    = window->properties.width_hint;
        window->properties.height   = window->properties.height_hint;
        glfwSetWindowSize(window->GetHandle(),width,height);
    }
}

void Application::setResizable(bool state)
{
    if(!window)
    {
        window->properties.resizable = state;
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

void Application::exit()
{
    quit_flag = true;
}

bool Application::init_application()
{
    if(!window->Init())
    {
        return false;
    }

    glfwSetKeyCallback(         window->GetHandle(),&Input::keyboard_callback);
    glfwSetMouseButtonCallback( window->GetHandle(),&Input::mousebtn_callback);
    glfwSetScrollCallback(      window->GetHandle(),&Input::mousewhl_callback);
    glfwSetCursorPosCallback(   window->GetHandle(),&Input::mousemov_callback);
    glfwSetWindowCloseCallback( window->GetHandle(),&windowclose_cb);

    graphics = new DGraphics(window->properties.width,window->properties.height);
    shader = new Shader(Shader::loadShadersFromString(quad_shader_v,quad_shader_f));
    vertpos_attrib = glGetAttribLocation(shader->getId(),"pos");
    texc_attrib = glGetAttribLocation(shader->getId(),"texpos");
    tex_uniform = glGetUniformLocation(shader->getId(),"texture");

    graphics->beginDraw();
    
    if(setup_func)
    {
        setup_func();
    }

    return true;
}

void Application::cleanup_application()
{
    if(cleanup_func)
    {
        cleanup_func();
    }

    window->Cleanup();
    
    delete window;
    delete graphics;
}

Application* Application::GetInstance()
{
    return instance;
}

void Application::draw_buffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0,window->properties.width,window->properties.height);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //bind shader, texture, and draw quad with the texture
    glUseProgram(shader->getId());
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,graphics->get_texture_id());
    glUniform1i(tex_uniform,0);

    glEnableVertexAttribArray(vertpos_attrib);
    glEnableVertexAttribArray(texc_attrib);

    glVertexAttribPointer(texc_attrib,2,GL_FLOAT,false,0, quadtex_coords);
    glVertexAttribPointer(vertpos_attrib,3,GL_FLOAT,false,0, quad_coords);

    glDrawArrays(GL_TRIANGLES,0,6);

    glDisableVertexAttribArray(vertpos_attrib);
    glDisableVertexAttribArray(texc_attrib);
    
    glBindTexture(GL_TEXTURE_2D,0);

    graphics->beginDraw();
}

Application* Application::instance = nullptr;