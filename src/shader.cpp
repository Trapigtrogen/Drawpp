#include <shader.hpp>

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
    int error = loadShaderFile(vsFile, &shaderVSrc, &shaderVLen);
    if(error != 0) dbg::error("Couldn't load vertex shader file");
    error = loadShaderFile(fsFile, &shaderFSrc, &shaderFLen);
    if(error != 0) dbg::error("Couldn't load fragment shader file");

    createShaderProgram();
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

int Shader::loadShaderFile(const char* filename, char** ShaderSource, GLint* len)
{
    std::ifstream file;
    file.open(filename, std::ios::in); // opens as ASCII!
    if(!file) return -1;

   *len = getFileLength(file);

    if(len == 0) return -2;   // Error: Empty File 

    *ShaderSource = new char[*len + 1];
    if(*ShaderSource == 0) return -3;   // can't reserve memory

     // len isn't always strlen cause some characters are stripped in ascii read...
     // it is important to 0-terminate the real length later, len is just max possible value... 
    *ShaderSource[*len] = 0;

    unsigned int i = 0;
    while(file.good()) {
        *ShaderSource[i] = file.get();       // get character from file.
        if(!file.eof())
            i++;
    }

    *ShaderSource[i] = 0;  // 0-terminate it at the correct position

    file.close();

    return 0; // No Error
}

unsigned int Shader::compileShader(unsigned int shader_type, char* shader_source) 
{
    unsigned int shader_id = glCreateShader(shader_type);

    glShaderSource(shader_id, 1, &shader_source, nullptr);
    glCompileShader(shader_id);

    GLint result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) 
    {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

        GLchar* strInfoLog = new GLchar[length + 1];
        glGetShaderInfoLog(shader_id, length, &length, strInfoLog);

        fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    return shader_id;
}

void Shader::createShaderProgram()
{
    id = glCreateProgram();

    // Compile shaders
    vertexShaderObject = compileShader(GL_VERTEX_SHADER, shaderVSrc);
    fragmentShaderObject = compileShader(GL_VERTEX_SHADER, shaderFSrc);

    glAttachShader(id, vertexShaderObject);
    glAttachShader(id, fragmentShaderObject);

    glLinkProgram(id);
    glValidateProgram(id);

    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragmentShaderObject);
}


unsigned long getFileLength(std::ifstream& file) 
{
    if(!file.good()) return 0;

    unsigned long pos = file.tellg();
    file.seekg(0, std::ios::end);
    unsigned long len = file.tellg();
    file.seekg(std::ios::beg);

    return len;
}