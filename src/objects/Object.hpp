#pragma once
#include "../wrapper/Material.hpp"
#include "../wrapper/Mesh.hpp"
#include "../wrapper/Shader.hpp"

class Object
{
public:
	explicit Object(const std::string& path);
	void Draw(const std::shared_ptr<Shader>& shader) const;

	void Translate(const glm::vec3& translation);
	void Scale(const glm::vec3& scale);
	void Rotate(const glm::vec3& rotation);

protected:
	[[nodiscard]] glm::mat4 GetModelMatrix() const;

	std::vector<std::shared_ptr<Material>> materials_{};
	std::vector<std::shared_ptr<Mesh>> meshes_{}; //:)

	glm::vec3 translation_{0.0f, 0.0f, 0.0f};
	glm::vec3 scale_{1.0f, 1.0f, 1.0f};
	glm::vec3 rotation_{0.0f, 0.0f, 0.0f};
};
