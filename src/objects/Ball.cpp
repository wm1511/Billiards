#include "stdafx.h"
#include "Ball.hpp"

#include "../core/Loader.hpp"
#include "Hole.hpp"

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

	glm::vec3 up(0, 1, 0);
	auto rotation_axis = glm::length(velocity_) != 0 ? glm::cross(up, velocity_) : glm::vec3(0, 0, 0);
	float rotation_angle = glm::length(velocity_) * dt / radius_;

	Rotate(rotation_axis, rotation_angle);
	velocity_ *= 0.985f;

	if (glm::length(velocity_) <= 0.01f)
		velocity_ *= 0;

}

void Ball::CollideWith(const std::shared_ptr<Ball>& ball)
{
	auto n = glm::vec3(translation_ - ball->translation_);

	auto n_length = glm::length(n);
	auto un = glm::normalize(n);

	if (n_length > radius_ * 2) return;

	//ustawianie bili do pozycji styku, ¿eby sie nie wchodzi³y w siebie no
	auto min_trans_dist = un * (radius_ * 2 - n_length);
	translation_ += min_trans_dist * 0.5f;
	ball->translation_ -= min_trans_dist * 0.5f;


	//jednostkowy styczny do bili (zarazem prostopad³y do n_norm)
	auto ut = glm::vec3(-un.z, 0, un.x);

	//jakieœ prêdkoœci
	auto v1n = glm::dot(un, velocity_);
	auto v1t = glm::dot(ut, velocity_);
	auto v2n = glm::dot(un, ball->velocity_);
	auto v2t = glm::dot(ut, ball->velocity_);

	//normal velocities
	auto v1nTag = v2n;
	auto v2nTag = v1n;

	auto v1nVec = glm::vec3(un * v1nTag);
	auto v1tVec = glm::vec3(ut * v1t);
	auto v2nVec = glm::vec3(un * v2nTag);
	auto v2tVec = glm::vec3(ut * v2t);

	velocity_ = v1nVec + v1tVec;
	ball->velocity_ = v2nVec + v2tVec;
}

bool Ball::IsInHole(const std::vector<std::shared_ptr<Hole>>& holes)
{
	bool in_hole = false;

	for (const auto& hole : holes)
		in_hole |= glm::distance(translation_, hole->position) < Hole::radius;

	return in_hole;
}


