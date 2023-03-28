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

	virtual void Draw(const std::shared_ptr<Shader>& shader);
	void Translate(const glm::vec3& translation);
	void Scale(const glm::vec3& scale);
	void Rotate(const glm::vec3& rotation, float angle);

	glm::vec3 translation_{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale_{ 1.0f, 1.0f, 1.0f };
	glm::vec3 rotation_axis_{ 0.0f, 0.0f, 0.0f };
	float angle_{ 0.0f };

	[[nodiscard]] glm::mat4 GetModelMatrix();
protected:

	std::vector<std::shared_ptr<Material>> materials_{};
	std::vector<std::shared_ptr<Mesh>> meshes_{}; //:)
};
