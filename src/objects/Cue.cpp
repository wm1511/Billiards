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

	//float rotationAngleX = (angle_ ) ? : ;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (!power_changed_)
		{
			//TODO

			
			if (angle_ > 0 && angle_ < 1.57f)
			{
				//
				Rotate(glm::vec3(-0.0f, 1.0f, -0.25f), dt);
			}
			else if (angle_ > 1.57f && angle_ < 3.14f)
			{
				Rotate(glm::vec3(-0.0f, 1.0f, -0.05f), dt);
			}
			else if (angle_ > 3.14 && angle_ < 4.71f)
			{
				Rotate(glm::vec3(-0.1f, 1.0f, 0.0f), dt);
			}
			else if (angle_ > 4.71 && angle_ < 6.3f)
			{
				//
				Rotate(glm::vec3(-0.1f, 1.0f, 0.1f), dt);
			}
			else
			{
				Rotate(glm::vec3(-0.1f, 1.0f, 0.1f), dt);
			}

			Translate(dt * Ball::radius_ * cue_direction);

		}
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (!power_changed_)
		{
			//TODO
			Translate(-dt * Ball::radius_ * cue_direction);
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
