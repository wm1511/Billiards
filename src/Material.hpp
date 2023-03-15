#pragma once
#include <glm/glm.hpp>

#include "Texture.hpp"

struct Material
{
	glm::vec3 ambient{1.0f};
	glm::vec3 diffuse{1.0f};
	glm::vec3 specular{0.0f};

	std::unique_ptr<Texture> diffuse_texture = nullptr;
	std::unique_ptr<Texture> specular_texture = nullptr;
	std::unique_ptr<Texture> normal_texture = nullptr;
};
