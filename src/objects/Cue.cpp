#include "stdafx.h"
#include "Cue.hpp"

Cue::Cue() : Object(Config::cue_path)
{
}

void Cue::HandleShot(const std::shared_ptr<Ball>& white_ball, const float dt)
{
	const auto window = glfwGetCurrentContext();
	const auto cue_direction = glm::vec3(sin(angle_), 0.0f, cos(angle_));
	const auto cue_rotation_axis = CalculateRotationAxis();
	const auto cue_displacement = glm::cross(cue_direction, cue_rotation_axis);

	constexpr auto up = glm::vec3(0.0f, 1.0f, 0.0f);
	const auto power_vector = glm::cross(cue_direction, up);
	auto power = glm::distance(translation_, white_ball->translation_);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (!power_changed_)
		{
			Rotate(cue_rotation_axis, dt);
			Translate(dt * Ball::radius_ * cue_direction);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (!power_changed_)
		{
			Rotate(cue_rotation_axis, -dt);
			Translate(-dt * Ball::radius_ * cue_direction);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (power > Ball::radius_ + Config::min_change)
		{
			Translate(-cue_displacement * dt);
			power_changed_ = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (power <= 0.5f)
		{
			Translate(cue_displacement * dt);
			power_changed_ = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		power *= Config::power_coeff;
		white_ball->Shot(-power_vector * power);
		power_changed_ = false;
	}
}

void Cue::PlaceAtBall(const std::shared_ptr<Ball>& ball)
{
	translation_.y = Ball::radius_;
	translation_.z = ball->translation_.z;

	if (ball->translation_.x > 0.0f)
	{
		translation_.x = ball->translation_.x + Ball::radius_ + Config::min_change;
		angle_ = glm::pi<float>();
	}
	else
	{
		translation_.x = ball->translation_.x - Ball::radius_ - Config::min_change;
		angle_ = 0.0f;
	}
}

glm::vec3 Cue::CalculateRotationAxis() const
{
	if (angle_ < glm::half_pi<float>())
		return glm::vec3(-0.1f, 1.0f, -0.1f);

	if (angle_ < glm::pi<float>())
		return glm::vec3(-0.1f, 1.0f, -0.1f);

	if (angle_ < glm::three_over_two_pi<float>())
		return glm::vec3(-0.1f, 1.0f, 0.1f);

	if (angle_ < glm::two_pi<float>())
		return glm::vec3(-0.1f, 1.0f, 0.1f);

	return rotation_axis_;

	// Interpolacja ale nie działa dobrze

	/*if (angle_ < glm::half_pi<float>())
	{
		const float x = glm::mix(0.1f, 0.0f, angle_ / glm::half_pi<float>());
		const float z = glm::mix(0.0f, -0.1f, angle_ / glm::half_pi<float>());
		return glm::vec3(x, 1.0f, z);
	}
	if (angle_ < glm::pi<float>())
	{
		const float x = glm::mix(0.0f, -0.1f, angle_ / glm::pi<float>());
		const float z = glm::mix(-0.1f, 0.0f, angle_ / glm::pi<float>());
		return glm::vec3(x, 1.0f, z);
	}
	if (angle_ < glm::three_over_two_pi<float>())
	{
		const float x = glm::mix(-0.1f, 0.0f, angle_ / glm::three_over_two_pi<float>());
		const float z = glm::mix(0.0f, 0.1f, angle_ / glm::three_over_two_pi<float>());
		return glm::vec3(x, 1.0f, z);
	}
	if (angle_ < glm::two_pi<float>())
	{
		const float x = glm::mix(0.0f, 0.1f, angle_ / glm::two_pi<float>());
		const float z = glm::mix(0.1f, 0.0f, angle_ / glm::two_pi<float>());
		return glm::vec3(x, 1.0f, z);
	}*/
}
