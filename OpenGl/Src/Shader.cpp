#include "Shader.h"
#include<string>
#include<sstream>
#include<fstream>
#include "Renderer.h"
#include<GL/glew.h>
#include<iostream>

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_ShaderID(0)
{
    ShaderProgramSource source = ShaderParser(filepath);
    m_ShaderID = CreateShader(source.vertexShader, source.fragmentShader);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_ShaderID));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_ShaderID));
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}
 
ShaderProgramSource Shader::ShaderParser(const std::string& filepath) {

    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];

    enum class shaderType
    {
        None = -1,
        vertex = 0,
        fragment = 1
    };

    shaderType type = shaderType::None;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = shaderType::vertex;
            else if (line.find("fragment") != std::string::npos)
                type = shaderType::fragment;
        }
        else {
            ss[(int)type] << line << std::endl;
        }
    }

    return { ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    //creating shader
    GLCall(unsigned int id = glCreateShader(type));
    //converting to character array pointer
    const char* src = source.c_str();
    //connected array souce code to shader source code
    GLCall(glShaderSource(id, 1, &src, nullptr));
    //compile shader
    GLCall(glCompileShader(id));

    //check status
    int shaderStatus;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &shaderStatus));

    if (shaderStatus == GL_FALSE) {
        int size;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size));
        char* message = (char*)alloca(size * sizeof(char));
        GLCall(glGetShaderInfoLog(id, size, &size, message));
        std::cout << "Failed to Compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader!\n";
        std::cout << message << std::endl;
        return 0;
    };

    return id;
}

unsigned int Shader::CreateShader(std::string& vertexShader, std::string& fragmentShader) {
    //create program container
    GLCall(unsigned int program = glCreateProgram());
    //compile vertex shader
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    //compile fragment shader
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //attach shaders to program and delete the shader
    GLCall(glAttachShader(program, vs));
    GLCall(glDeleteShader(vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glDeleteShader(fs));

    //links the program obj
    GLCall(glLinkProgram(program));

    //check whether the program can execute in current opengl state
    GLCall(glValidateProgram(program));

    return program;
}

int Shader::GetUniformLocation(const std::string& name) {

    if (m_UnifromLocationCache.find(name) != m_UnifromLocationCache.end())
    {
        return m_UnifromLocationCache[name];
    }
    GLCall(int location = glGetUniformLocation(m_ShaderID, name.c_str()));

    if (location == -1) {
        std::cout << "Uniform : " << name << " doesn't exist" << std::endl;
    }
    m_UnifromLocationCache[name] = location;

    return location;
}

void Shader::SetUniform1f(const std::string& name, float v) {
    GLCall(glUniform1f(GetUniformLocation(name), v));
}

void Shader::SetUniform1i(const std::string& name, int v) {
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE ,&matrix[0][0]));
}

void Shader::SetUniform1iv(const std::string& name, int count, int position[]) {
    GLCall(glUniform1iv(GetUniformLocation(name), count, position));
}
void Shader::SetUniform1fv(const std::string& name, int count, float position[]) {
    GLCall(glUniform1fv(GetUniformLocation(name), count, position));
}