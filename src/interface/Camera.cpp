#include "stdafx.h"
#include "Camera.hpp"

void Camera::Init()
{
	UpdateProjectionMatrix(Config::width, Config::height);
	view_matrix_ = glm::mat4(1.0f);
}

void Camera::UpdateViewMatrix(const float frame_time)
{
	GLFWwindow* window = glfwGetCurrentContext();

	constexpr glm::vec3 up = {0.0f, 1.0f, 0.0f};
	const glm::vec3 direction = glm::normalize(glm::vec3(
        cos(yaw_) * cos(pitch_),
        sin(pitch_),
		sin(yaw_) * cos(pitch_)));

	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		Move(window, direction, Config::movement_speed * frame_time);
		Rotate(window, Config::rotation_speed * frame_time);
	}

	view_matrix_ = glm::lookAt(position_, position_ + direction, up);
}

void Camera::UpdateProjectionMatrix(const int width, const int height)
{
	projection_matrix_ = glm::perspective(Config::fov, static_cast<float>(width) / static_cast<float>(height), Config::near_clip, Config::far_clip);
}

void Camera::Update(const std::shared_ptr<Shader>& shader) const
{
	shader->Bind();

	for (int i = 0; i < Config::light_count; i++)
	{
		shader->SetVec3(glm::vec3(20.0f), std::string("lights[") + std::to_string(i) + "].color");
		shader->SetVec3(glm::vec3(-2.0f + 2.0f * i, 2.0f, 0.0f), std::string("lights[") + std::to_string(i) + "].position");
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		shader->SetVec3(glm::vec3(10.0f), std::string("lights[") + std::to_string(Config::light_count) + "].color");
		shader->SetVec3(position_, std::string("lights[") + std::to_string(Config::light_count) + "].position");
		shader->SetInt(Config::light_count + 1, "lightCount");
	}
	else
	{
		shader->SetInt(Config::light_count, "lightCount");
	}

	shader->SetMat4(view_matrix_, "viewMatrix");
    shader->SetMat4(projection_matrix_, "projectionMatrix");
    shader->SetVec3(position_, "cameraPos");
	shader->SetFloat(Config::far_clip, "far_plane");

	shader->Unbind();
}

void Camera::Move(GLFWwindow* window, const glm::vec3& direction, const float factor)
{
	constexpr glm::vec3 up = {0.0f, 1.0f, 0.0f};
	const glm::vec3 right = glm::normalize(glm::cross(direction, up));

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

	position_ = glm::clamp(position_, Config::camera_min_position, Config::camera_max_position);
}

void Camera::Rotate(GLFWwindow* window, const float factor)
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
