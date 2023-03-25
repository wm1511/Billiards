#pragma once

class Shader
{
public:
	Shader(const std::string& vertex_path, const std::string& fragment_path, const std::string& geometry_path = {});

	void Bind() const;

	void SetVec3(const glm::vec3& v, const std::string& name) const;
	void SetMat4(const glm::mat4& m, const std::string& name) const;
	void SetFloat(float s, const std::string& name) const;
	void SetInt(int n, const std::string& name) const;
	void SetBool(bool c, const std::string& name) const;

private:
	[[nodiscard]] std::string LoadShaderSource(const std::string& path) const;
	[[nodiscard]] unsigned LoadShader(unsigned type, const std::string& path) const;
	void LinkProgram(unsigned vertex, unsigned fragment, unsigned geometry = 0);

	unsigned id_;
};