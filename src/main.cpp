#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    char c = getchar();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}