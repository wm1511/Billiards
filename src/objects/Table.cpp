#include "stdafx.h"
#include "Table.hpp"

Table::Table() : Object(Config::table_path)
{
	holes_.resize(6);
	holes_[0] = std::make_shared<Hole>(glm::vec3(1.35f - 0.1f, 0, 0.7f - 0.1f));
	holes_[1] = std::make_shared<Hole>(glm::vec3(1.35f - 0.1f, 0, -(0.7f - 0.1f)));
	holes_[2] = std::make_shared<Hole>(glm::vec3(0, 0, -(0.7f - 0.02f)));
	holes_[3] = std::make_shared<Hole>(glm::vec3(-(1.35f - 0.1f), 0, -(0.7f - 0.1f)));
	holes_[4] = std::make_shared<Hole>(glm::vec3(-(1.35f - 0.1f), 0, 0.7f - 0.1f));
	holes_[5] = std::make_shared<Hole>(glm::vec3(0, 0, 0.7f - 0.02f));
}

void Table::HandleBoundsCollision(const std::shared_ptr<Ball>& ball) const
{
	if (ball->translation_.x >= bound_x_)
	{
		ball->velocity_ = glm::reflect(ball->velocity_, glm::vec3(-1.0f, 0.0f, 0.0f));
		ball->translation_.x = bound_x_;
	}
	else if (ball->translation_.x <= -bound_x_)
	{
		ball->velocity_ = glm::reflect(ball->velocity_, glm::vec3(1.0f, 0.0f, 0.0f));
		ball->translation_.x = -bound_x_;
	}
	else if (ball->translation_.z >= bound_z_ && (ball->translation_.x < holes_[5]->position.x - Hole::radius || ball->translation_.x > holes_[5]->position.x + Hole::radius))
	{
		ball->velocity_ = glm::reflect(ball->velocity_, glm::vec3(0.0f, 0.0f, -1.0f));
		ball->translation_.z = bound_z_;
	}
	else if (ball->translation_.z <= -bound_z_ && (ball->translation_.x < holes_[2]->position.x - Hole::radius || ball->translation_.x > holes_[2]->position.x + Hole::radius))
	{
		ball->velocity_ = glm::reflect(ball->velocity_, glm::vec3(0.0f, 0.0f, 1.0f));
		ball->translation_.z = -bound_z_;
	}


}
