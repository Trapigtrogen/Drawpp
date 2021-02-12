#ifndef DPP_SHADER_H
#define DPP_SHADER_H

#include <string>
#include <debug.hpp>
#include <glad/glad.h>

#include <iostream> 
#include <fstream> 

/// Shader class loads the OpenGL shaders
class Shader
{
public:
    // Use default
	Shader();
	~Shader();

    Shader(const Shader& other);
    Shader(Shader&& other);

    Shader& operator=(Shader&& other);

	int getId() { return id; }

    static Shader loadShadersFromFile(const char* vsFile, const char* fsFile);
    static Shader loadShadersFromString(const char* vsStr, const char* fsStr);
    static Shader loadShadersDefault();

    GLuint vertexShader;
    GLuint fragmentShader;

    std::string shaderVSrc;
    std::string shaderFSrc;

private:
    std::string readShaderFile(const char* filename);
    GLuint compileShader(unsigned int shader_type, const char* shader_source);
    void createShaderProgram();

    GLuint id;

    const char* defaultVertexSource = "#version 330 core\n"
        "layout (location = 0) in vec4 vert;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "uniform mat4 model;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vert;\n"
        "}\0";

    const char* defaultFragmentSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
};

#endif