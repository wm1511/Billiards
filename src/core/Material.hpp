#pragma once
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture.hpp"

struct Material
{
	void Bind(const std::shared_ptr<Shader>& shader) const;
	void Unbind(const std::shared_ptr<Shader>& shader) const;

	glm::vec3 diffuse{0.0f};
	glm::vec3 ambient{0.0f};
	float roughness{0.0f};
	float metallic{0.0f};

	std::shared_ptr<Texture> diffuse_texture = nullptr;
	std::shared_ptr<Texture> ao_texture = nullptr;
	std::shared_ptr<Texture> roughness_texture = nullptr;
	std::shared_ptr<Texture> metallic_texture = nullptr;
	std::shared_ptr<Texture> normal_texture = nullptr;
};
