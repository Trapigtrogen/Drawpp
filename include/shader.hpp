#ifndef DPP_SHADER_H
#define DPP_SHADER_H

#include <string>

///\private
class Shader
{
    friend class DFilter;
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
    static std::string readShaderFile(const char* filename);
    unsigned int compileShader(unsigned int shader_type, const char* shader_source);
    void createShaderProgram();

    unsigned int id;

    const char* defaultVertexSource = R"(
        #version 100
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
        #version 100
        void main()
        {
           gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
        )";
};

#endif