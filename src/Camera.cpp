#include "stdafx.h"
#include "Camera.hpp"
#include "Input.hpp"

Camera::Camera(const float fov, const float near_clip, const float far_clip, const float movement_speed, const float rotation_speed)
	: fov_(fov), near_clip_(near_clip), far_clip_(far_clip), movement_speed_(movement_speed), rotation_speed_(rotation_speed)
{
	projection_ = glm::perspective(glm::radians(fov_), 1.7916667f, near_clip_, far_clip_);
	view_ = glm::mat4(1.0f);
}

void Camera::UpdateView(const float frame_time)
{
	const float movement_factor = movement_speed_ * frame_time;
	const float rotation_factor = rotation_speed_ * frame_time;
	const glm::vec2 delta = Input::GetCursorDelta();

	const glm::vec3 direction = glm::normalize(glm::vec3(
        cos(yaw_) * cos(pitch_),
        sin(pitch_),
		sin(yaw_) * cos(pitch_)));

	const glm::vec3 right = glm::cross(direction, {0.0f, 1.0f, 0.0f});
	const glm::vec3 up = glm::cross(right, direction);

	if (Input::GetPressedKey() == GLFW_KEY_W)
	{
		position_ += direction * movement_factor;
	}
	else if (Input::GetPressedKey() == GLFW_KEY_S)
	{
		position_ -= direction * movement_factor;
	}
	if (Input::GetPressedKey() == GLFW_KEY_A)
	{
		position_ -= right * movement_factor;
	}
	else if (Input::GetPressedKey() == GLFW_KEY_D)
	{
		position_ += right * movement_factor;
	}
	if (Input::GetPressedKey() == GLFW_KEY_E)
	{
		position_ += up * movement_factor;
	}
	else if (Input::GetPressedKey() == GLFW_KEY_Q)
	{
		position_ -= up * movement_factor;
	}

	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		pitch_ += delta.y * rotation_factor;
		yaw_ -= delta.x * rotation_factor;

		pitch_ = glm::clamp(pitch_, -1.5f, 1.5f);
		yaw_ = glm::mod(yaw_, glm::two_pi<float>());
	}

	view_ = glm::lookAt(position_, position_ + direction, up);
}

void Camera::UpdateProjection(const int width, const int height)
{
	projection_ = glm::perspective(glm::radians(fov_), (float)width / (float)height, near_clip_, far_clip_);
}