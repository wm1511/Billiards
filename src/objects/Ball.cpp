#include "stdafx.h"
#include "Ball.hpp"

#include "../core/Loader.hpp"

Ball::Ball() : Object(Config::ball_path) { }

Ball::Ball(const int number) : Object(Config::ball_path)
{
	const auto path = std::filesystem::current_path() / ("assets/textures/ball" + std::to_string(number) + ".jpg");
	materials_[0]->diffuse_texture = Loader::LoadTexture(path.string());
}

void Ball::Shot(const glm::vec3 power)
{
	if (!is_in_motion_)
	{
		velocity_ = power;
		is_in_motion_ = true;
	}
}

void Ball::Roll(const float dt)
{
	Translate(velocity_ * dt);

	const glm::vec3 up(0, 1, 0);
	const auto rotation_axis = glm::cross(up, glm::normalize(velocity_));
	const float rotation_angle = glm::length(velocity_) * dt / radius_;
	Rotate(rotation_axis, rotation_angle);

	velocity_ *= 0.985f;

	if (glm::length(velocity_) <= std::numeric_limits<float>::epsilon())
		velocity_ *= 0;
}


