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

	int getId() const { return id; }

    static Shader loadShadersFromFile(const char* vsFile, const char* fsFile);
    static Shader loadShadersFromString(const char* vsStr, const char* fsStr);
    static Shader loadShadersDefault();

    std::string shaderVSrc;
    std::string shaderFSrc;

private:
    std::string readShaderFile(const char* filename);
    GLuint compileShader(unsigned int shader_type, const char* shader_source);
    void createShaderProgram();

    GLuint id = 0;

    const char* defaultVertexSource = R"(
        #version 100 core
        attribute vec4 vert;
        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;
        void main()
        {
           gl_Position = projection * view * model * vert;
        }
        )";

    const char* defaultFragmentSource = R"(
        #version 100 core
        void main()
        {
           gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
        )";
};

#endif