#include "stdafx.h"
#include "Cue.hpp"

Cue::Cue() : Object(Config::cue_path)
{
}

void Cue::HandleShot(const std::shared_ptr<Ball>& white_ball, const float dt)
{
	const auto window = glfwGetCurrentContext();
	const auto cue_direction = glm::vec3(sin(angle_), 0.0f, cos(angle_));

	constexpr auto up = glm::vec3(0.0f, 1.0f, 0.0f);
	const auto power_vector = glm::cross(cue_direction, up);
	auto power = glm::distance(translation_, white_ball->translation_);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (!power_changed_)
		{
			Translate(dt * Ball::radius_ * cue_direction);
			angle_ += dt;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (!power_changed_)
		{
			Translate(-dt * Ball::radius_ * cue_direction);
			angle_ -= dt;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (power > Ball::radius_ + Config::min_change)
		{
			Translate(-power_vector * dt);
			power_changed_ = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (power <= 0.5f)
		{
			Translate(power_vector * dt);
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
	translation_.x = ball->translation_.x + Ball::radius_ + Config::min_change;
	translation_.z = ball->translation_.z;
	angle_ = glm::pi<float>();
}
