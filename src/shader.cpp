#include <shader.hpp>
#include <vector>
#include <debug.hpp>

// Use default
Shader::Shader() = default;

Shader::Shader(const Shader& other)
{
    shaderVSrc = other.shaderVSrc;
    shaderFSrc = other.shaderFSrc;
    createShaderProgram();
}

Shader::Shader(Shader&& other) 
{
    if(id > 0) glDeleteProgram(id);
    id = other.id;
    other.id = 0;

    shaderVSrc = other.shaderVSrc;
    shaderFSrc = other.shaderFSrc;
}

Shader& Shader::operator=(Shader&& other)
{
    if(this != &other) {
        if(id > 0) glDeleteProgram(id);
        id = other.id;
        other.id = 0;

        shaderVSrc = other.shaderVSrc;
        shaderFSrc = other.shaderFSrc;
    }

    return *this;
}

Shader Shader::loadShadersFromFile(const char* vsFile, const char* fsFile)
{
    Shader tmpShader;

    // Load shader files
    tmpShader.shaderVSrc = tmpShader.readShaderFile(vsFile);
    tmpShader.shaderFSrc = tmpShader.readShaderFile(fsFile);

    tmpShader.createShaderProgram();

    return tmpShader;
}

Shader Shader::loadShadersFromString(const char* vsStr, const char* fsStr)
{
    Shader tmpShader;

    // Load shader string
    tmpShader.shaderVSrc = vsStr;
    tmpShader.shaderFSrc = fsStr;

    tmpShader.createShaderProgram();

    return tmpShader;
}

Shader Shader::loadShadersDefault() 
{
    Shader tmpShader;

    // Load shader string
    tmpShader.shaderVSrc = tmpShader.defaultVertexSource;
    tmpShader.shaderFSrc = tmpShader.defaultFragmentSource;

    tmpShader.createShaderProgram();

    return tmpShader;
}

Shader::~Shader()
{
    if(id > 0) glDeleteProgram(id);
}

std::string Shader::readShaderFile(const char* filename)
{
    std::string content;
    std::ifstream fileStream(filename, std::ios::in);

    if(!fileStream.is_open()) 
    {
        dbg::error("Shader file not found");
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) 
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    return content;
}

GLuint Shader::compileShader(unsigned int shader_type, const char* shader_source)
{
    GLuint shader_id = glCreateShader(shader_type);


    GLint result = GL_FALSE;
    int logLength;

    // Compile shader
    glShaderSource(shader_id, 1, &shader_source, NULL);
    glCompileShader(shader_id);

    // Check if shader compile was successfull
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> vertShaderError(logLength+1);
        glGetShaderInfoLog(shader_id, logLength, NULL, vertShaderError.data());
        dbg::error(vertShaderError.data());
    }

    return shader_id;
}

void Shader::createShaderProgram()
{
    id = glCreateProgram();

    // Compile shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, shaderVSrc.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderFSrc.c_str());

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);

    glLinkProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}