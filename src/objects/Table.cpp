#include "stdafx.h"
#include "Table.hpp"

Table::Table() : Object(Config::table_path)
{

}

void Table::HandleCollision(const std::shared_ptr<Ball>& ball)
{
	if (ball->translation_.x >= 1.35f - Ball::radius_ - 0.042f)
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(-1, 0, 0));

	else if (ball->translation_.x <= -(1.35f - Ball::radius_ - 0.042f))
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(1, 0, 0));

	else if (ball->translation_.z >= 0.7f - Ball::radius_ - 0.042f)
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(0, 0, -1));

	else if (ball->translation_.z <= -(0.7f - Ball::radius_ - 0.042f))
		ball->velocity = glm::reflect(ball->velocity, glm::vec3(0, 0, 1));
}
