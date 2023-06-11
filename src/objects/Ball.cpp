#include "stdafx.h"
#include "Ball.hpp"

#include "../core/Loader.hpp"

Ball::Ball(const int number) : Object(Config::ball_path)
{
	const auto path = std::filesystem::current_path() / ("assets/textures/ball" + std::to_string(number) + ".jpg");
	materials_[0]->diffuse_texture = Loader::LoadTexture(path.string());
}

void Ball::Shot(const glm::vec3 power)
{
	if (!IsInMotion())
		velocity_ = power;
}

void Ball::Roll(const float dt)
{
	Translate(velocity_ * dt);

	constexpr glm::vec3 up(0.0f, 1.0f, 0.0f);

	const auto rotation_axis = glm::length(velocity_) > Config::min_change
		                           ? glm::cross(up, glm::normalize(velocity_))
		                           : glm::vec3(0.0f, 0.0f, 0.0f);
	const float rotation_angle = glm::length(velocity_) * dt / radius_;

	Rotate(rotation_axis, rotation_angle);
	velocity_ *= Config::velocity_multiplier;

	if (!IsInMotion())
		velocity_ *= 0.0f;
}

void Ball::CollideWith(const std::shared_ptr<Ball>& ball)
{
	auto n = glm::vec3(translation_ - ball->translation_);

	auto n_length = glm::length(n);
	auto un = glm::normalize(n);

	if (n_length > radius_ * 2.0f) return;

	//ustawianie bili do pozycji styku, żeby sie nie wchodziły w siebie no
	auto min_trans_dist = un * (radius_ * 2 - n_length);
	translation_ += min_trans_dist * 0.5f;
	ball->translation_ -= min_trans_dist * 0.5f;

	//jednostkowy styczny do bili (zarazem prostopadły do n_norm)
	auto ut = glm::vec3(-un.z, 0.0f, un.x);

	//jakieś prędkości
	auto v1_n = glm::dot(un, velocity_);
	auto v1_t = glm::dot(ut, velocity_);
	auto v2_n = glm::dot(un, ball->velocity_);
	auto v2_t = glm::dot(ut, ball->velocity_);

	//normal velocities
	auto v1_n_tag = v2_n;
	auto v2_n_tag = v1_n;

	auto v1_n_vec = glm::vec3(un * v1_n_tag);
	auto v1_t_vec = glm::vec3(ut * v1_t);
	auto v2_n_vec = glm::vec3(un * v2_n_tag);
	auto v2_t_vec = glm::vec3(ut * v2_t);

	velocity_ = v1_n_vec + v1_t_vec;
	ball->velocity_ = v2_n_vec + v2_t_vec;
}

void Ball::BounceOffBound(const glm::vec3 surface_normal, const float bound_x, const float bound_z)
{
	velocity_ = glm::reflect(velocity_, surface_normal);

	if (surface_normal.x > Config::min_change || surface_normal.x < -Config::min_change)
		translation_.x = -surface_normal.x * bound_x;
	else if (surface_normal.z > Config::min_change || surface_normal.z < -Config::min_change)
		translation_.z = -surface_normal.z * bound_z;
}

void Ball::BounceOffHole(const glm::vec2 surface_normal, const float hole_radius)
{
	const float temp = translation_.y;
	const auto horizontal_velocity = glm::vec2(velocity_.x, velocity_.z);
	const auto reflected_velocity = glm::reflect(horizontal_velocity, surface_normal);
	const auto horizontal_direction = -glm::vec3(surface_normal.x, 0.0f, surface_normal.y);

	velocity_ = glm::vec3(reflected_velocity.x, velocity_.y, reflected_velocity.y);
	translation_ = hole_ + horizontal_direction * (hole_radius - radius_);
	translation_.y = temp;
}

void Ball::TakeFromHole()
{
	is_in_hole_ = false;
	velocity_ = glm::vec3(0.0f);
	translation_ = glm::vec3(0.0f, radius_, 0.0f);
}

void Ball::SetDrawn(const bool drawn)
{
	is_drawn_ = drawn;
}

bool Ball::IsInHole(const std::vector<glm::vec3>& holes, const float hole_radius)
{
	for (const auto& hole : holes)
	{
		if (glm::distance(translation_, hole) < hole_radius)
		{
			hole_ = hole;
			is_in_hole_ = true;
		}
	}

	return is_in_hole_;
}
