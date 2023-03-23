#pragma once
#include "../core/Material.hpp"
#include "../core/Mesh.hpp"
#include "../core/Shader.hpp"

class Object
{
public:
	virtual ~Object() = default;
	Object() = default;
	explicit Object(const std::string& path);

	virtual void Draw(const std::shared_ptr<Shader>& shader, unsigned type = GL_TEXTURE_2D) const;
	void Translate(const glm::vec3& translation);
	void Scale(const glm::vec3& scale);
	void Rotate(const glm::vec3& rotation);

	glm::vec3 translation_{0.0f, 0.0f, 0.0f};
	glm::vec3 scale_{1.0f, 1.0f, 1.0f};
	glm::vec3 rotation_{0.0f, 0.0f, 0.0f};

protected:
	[[nodiscard]] glm::mat4 GetModelMatrix() const;

	std::vector<std::shared_ptr<Material>> materials_{};
	std::vector<std::shared_ptr<Mesh>> meshes_{}; //:)
};
