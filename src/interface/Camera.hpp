#pragma once
#include "../core/Shader.hpp"

class Camera
{
public:
	Camera();

	void Init();
	void UpdateViewMatrix(float frame_time);
	void UpdateProjectionMatrix(int width, int height);
	void Update(const std::shared_ptr<Shader>& shader) const;

private:
	void Move(GLFWwindow* window, const glm::vec3& direction, float factor);
	void Rotate(GLFWwindow* window, float factor);

	glm::mat4 projection_matrix_{};
	glm::mat4 view_matrix_{};

	glm::vec2 prior_cursor_{0.0f};
	glm::vec3 position_{0.0f, 2.0f, 0.0f};
	float pitch_{-glm::half_pi<float>()};
	float yaw_{0.0f};

	float fov_{};
	float near_clip_{};
	float far_clip_{};
	float movement_speed_{};
	float rotation_speed_{};
};
