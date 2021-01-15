#include <iostream>
#include <glad/glad.h>
#include <KHR/khrplatform.h>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello World!";
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    return 0;
}