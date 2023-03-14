#pragma once
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
	Shader(const std::string& vertex_filename, const std::string& fragment_filename);
	void Bind() const;
	void Unbind() const;

	void SetVec3(const glm::vec3& v, const std::string& name) const;
	void SetMat4(const glm::mat4& m, const std::string& name) const;
	void SetFloat(float s, const std::string& name) const;

private:
	[[nodiscard]] std::string LoadShaderSource(const std::string& path) const;
	[[nodiscard]] unsigned LoadShader(unsigned type, const std::string& path) const;
	void LinkProgram(unsigned vertex, unsigned fragment);

	unsigned id_;
};