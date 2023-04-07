#pragma once
#include "../core/Shader.hpp"

class Camera
{
public:
	Camera() = default;

	void Init();
	void UpdateViewMatrix(float frame_time);
	void UpdateProjectionMatrix(int width, int height);
	void UpdateMain(const std::shared_ptr<Shader>& main_shader) const;
	void UpdateBackground(const std::shared_ptr<Shader>& background_shader) const;

private:
	void Move(GLFWwindow* window, const glm::vec3& direction, float factor);
	void Rotate(GLFWwindow* window, float factor);

	glm::mat4 projection_matrix_{};
	glm::mat4 view_matrix_{};

	glm::vec2 prior_cursor_{0.0f};
	glm::vec3 position_{0.0f, 1.5f, 0.0f};
	float pitch_{-glm::half_pi<float>()};
	float yaw_{0.0f};
};
