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
    // Use custom
	Shader(const char* vsFile, const char* fsFile);
	~Shader();

	int getId() { return id; }

private:
    std::string loadShaderFile(const char* filename);
    GLuint compileShader(unsigned int shader_type, const char* shader_source);
    void createShaderProgram();

    std::streampos getFileLength(std::ifstream& file);

    GLuint id;

    GLuint vertexShader;
    GLuint fragmentShader;

    std::string shaderVSrc;
    std::string shaderFSrc;

    const char* defaultVertexSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* defaultFragmentSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
};

#endif