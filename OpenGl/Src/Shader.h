#pragma once

#include<string>
#include<unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource {

	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_ShaderID;
	//catching for uniforms
	std::unordered_map<std::string, int> m_UnifromLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//set uniforms
	void SetUniform4f(const std::string& name,float v0, float v1, float v2, float v3);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform1i(const std::string& name, int v);
	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);
	void SetUniform1iv(const std::string& name, int count, int position[]);
	void SetUniform1fv(const std::string& name, int count, float position[]);
	unsigned int GetID() const { return m_ShaderID; }

private:
	int GetUniformLocation(const std::string& name);

	ShaderProgramSource ShaderParser(const std::string& filepath);

	unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int CreateShader(std::string& vertexShader, std::string& fragmentShader);
};

