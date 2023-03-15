#pragma once

class Camera
{
public:
	Camera(float fov, float near_clip, float far_clip, float movement_speed, float rotation_speed);

	void UpdateView(float frame_time);
	void UpdateProjection(int width, int height);

	[[nodiscard]] const glm::mat4& GetProjection() const
	{
		return projection_;
	}
	[[nodiscard]] const glm::mat4& GetView() const
	{
		return view_;
	}
	[[nodiscard]] const glm::vec3& GetPosition() const
	{
		return position_;
	}

private:
	void MoveCamera(GLFWwindow* window, const glm::vec3& direction, float factor);
	void RotateCamera(GLFWwindow* window, float factor);

	glm::mat4 projection_{};
	glm::mat4 view_{};

	glm::vec2 prior_cursor_{0.0f};
	glm::vec3 position_{0.0f, 1.0f, 0.0f};
	float pitch_{0.0f};
	float yaw_{0.0f};

	float fov_;
	float near_clip_;
	float far_clip_;
	float movement_speed_;
	float rotation_speed_;
};