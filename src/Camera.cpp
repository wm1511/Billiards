#include "stdafx.h"
#include "Camera.hpp"

Camera::Camera(const float fov, const float near_clip, const float far_clip, const float movement_speed, const float rotation_speed)
	: fov_(fov), near_clip_(near_clip), far_clip_(far_clip), movement_speed_(movement_speed), rotation_speed_(rotation_speed)
{
	projection_ = glm::perspective(glm::radians(fov_), 1.7916667f, near_clip_, far_clip_);
	view_ = glm::mat4(1.0f);
}

void Camera::UpdateView(const float frame_time)
{
	GLFWwindow* window = glfwGetCurrentContext();

	constexpr glm::vec3 up = {0.0f, 1.0f, 0.0f};
	const glm::vec3 direction = glm::normalize(glm::vec3(
        cos(yaw_) * cos(pitch_),
        sin(pitch_),
		sin(yaw_) * cos(pitch_)));
	
	MoveCamera(window, direction, movement_speed_ /** frame_time*/);

	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		RotateCamera(window, rotation_speed_ /** frame_time*/);

	view_ = glm::lookAt(position_, position_ + direction, up);
}

void Camera::UpdateProjection(const int width, const int height)
{
	projection_ = glm::perspective(glm::radians(fov_), (float)width / (float)height, near_clip_, far_clip_);
}

void Camera::MoveCamera(GLFWwindow* window, const glm::vec3& direction, const float factor)
{
	constexpr glm::vec3 up = {0.0f, 1.0f, 0.0f};
	const glm::vec3 right = glm::cross(direction, up);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position_ += direction * factor;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position_ -= direction * factor;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position_ -= right * factor;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position_ += right * factor;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		position_ += up * factor;
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		position_ -= up * factor;
	}
}

void Camera::RotateCamera(GLFWwindow* window, const float factor)
{
	double current_cursor_x, current_cursor_y;
	glfwGetCursorPos(window, &current_cursor_x, &current_cursor_y);

	const glm::vec2 delta = {static_cast<float>(current_cursor_x) - prior_cursor_.x, static_cast<float>(current_cursor_y) - prior_cursor_.y};
	prior_cursor_ = {current_cursor_x, current_cursor_y};

	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		pitch_ -= delta.y * factor;
		yaw_ += delta.x * factor;

		pitch_ = glm::clamp(pitch_, -1.5f, 1.5f);
		yaw_ = glm::mod(yaw_, glm::two_pi<float>());
	}
}
