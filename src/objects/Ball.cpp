#include "stdafx.h"
#include "Ball.hpp"

#include "../core/Loader.hpp"

Ball::Ball() : Object(Config::ball_path) { }

Ball::Ball(const int number) : Object(Config::ball_path)
{
	const auto path = std::filesystem::current_path() / ("assets/textures/ball" + std::to_string(number) + ".jpg");
	materials_[0]->diffuse_texture = Loader::LoadTexture(path.string());
}

void Ball::Shot(glm::vec3 power)
{
	velocity = power;
}

void Ball::Roll(const float dt)
{
	Translate(velocity * dt);

	glm::vec3 up(0, 1, 0);
	auto rotation_axis = glm::cross(up, glm::normalize(velocity));
	float rotation_angle = glm::length(velocity) * dt / radius_;
	Rotate(rotation_axis, rotation_angle);

	velocity *= 0.985f;

	if (glm::length(velocity) <= std::numeric_limits<float>::epsilon())
		velocity *= 0;
}


