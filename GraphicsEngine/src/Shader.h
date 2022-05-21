#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
	//caching for Uniforms
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// set Uniforms
	void SetUnifrom3f(const std::string& name, float v0, float v1, float v2);
	void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUnifrom1f(const std::string& name, float v);
	void SetUnifrom1i(const std::string& name, int v);
	void SetUnifromMat4f(const std::string& name, const glm::mat4& matrix);
private:
	unsigned int GetUniformLocations(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);
};