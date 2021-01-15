#include <tmp_main_header.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

unsigned long create_window()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    return reinterpret_cast<unsigned long>(window);
}

int destroy_window(unsigned long window)
{
    glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(window));
    glfwTerminate();

    return 0;
}