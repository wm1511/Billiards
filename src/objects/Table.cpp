#include "stdafx.h"
#include "Table.hpp"

Table::Table() : Object(Config::table_path)
{

}

void Table::HandleCollision(const std::shared_ptr<Ball>& ball)
{
	if (ball->translation_.x >= bound_x_)
	{
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(-1.0f, 0.0f, 0.0f));
		ball->translation_.x = bound_x_;
	}
	else if (ball->translation_.x <= -bound_x_)
	{
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(1.0f, 0.0f, 0.0f));
		ball->translation_.x = -bound_x_;
	}
	else if (ball->translation_.z >= bound_z_)
	{
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(0.0f, 0.0f, -1.0f));
		ball->translation_.z = bound_z_;
	}
	else if (ball->translation_.z <= -bound_z_)
	{
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(0.0f, 0.0f, 1.0f));
		ball->translation_.z = -bound_z_;
	}
}
