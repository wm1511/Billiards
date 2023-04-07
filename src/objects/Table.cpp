#include "stdafx.h"
#include "Table.hpp"

Table::Table() : Object(Config::table_path)
{
	holes_.resize(6);
	holes_[0] = glm::vec3(1.35f - Ball::radius_, 0.0f, 0.7f - Ball::radius_);
	holes_[1] = glm::vec3(1.35f - Ball::radius_, 0.0f, -0.7f + Ball::radius_);
	holes_[2] = glm::vec3(0.0f, 0.0f, -0.7f - Ball::radius_);
	holes_[3] = glm::vec3(-1.35f + Ball::radius_, 0.0f, -0.7f + Ball::radius_);
	holes_[4] = glm::vec3(-1.35f + Ball::radius_, 0.0f, 0.7f - Ball::radius_);
	holes_[5] = glm::vec3(0.0f, 0.0f, 0.7f + Ball::radius_);
}
