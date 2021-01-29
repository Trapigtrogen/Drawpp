#include <shader.hpp>
#include <vector>

// Use default
Shader::Shader()
{
    shaderVSrc = (char*)defaultVertexSource;
    shaderFSrc = (char*)defaultFragmentSource;

    createShaderProgram();
}

// Use custom
Shader::Shader(const char* vsFile, const char* fsFile)
{
    // Load shader files
    shaderVSrc = loadShaderFile(vsFile);
    shaderFSrc = loadShaderFile(fsFile);

    createShaderProgram();
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

std::string Shader::loadShaderFile(const char* filename)
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
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(shader_id, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    return shader_id;
}

void Shader::createShaderProgram()
{
    id = glCreateProgram();

    // Compile shaders
    vertexShader = compileShader(GL_VERTEX_SHADER, shaderVSrc.c_str());
    fragmentShader = compileShader(GL_VERTEX_SHADER, shaderFSrc.c_str());

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);

    glLinkProgram(id);
    glValidateProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::streampos getFileLength(std::ifstream& file)
{
    std::streampos fsize = 0;

    fsize = file.tellg();
    file.seekg(0, std::ios::end);
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}