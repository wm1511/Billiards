#include "stdafx.h"
#include "World.hpp"

World::World() :
	table_(std::make_shared<Table>()),
	cue_(std::make_shared<Cue>())
{
	table_->Scale(glm::vec3{ 2.0f });
	cue_->Scale(glm::vec3{ 2.0f });

	for (int n = 0; n < 16; n++)
	{
		balls_.push_back(std::make_shared<Ball>(n));
		balls_[n]->Scale(glm::vec3{ 2.0f });
		balls_[n]->Translate(glm::vec3{ 0.0f, Ball::radius_, 0.0f });
	}
}

void World::Draw(const std::shared_ptr<Shader>& shader) const
{
	table_->Draw(shader);
	cue_->Draw(shader);
	for (const auto& ball : balls_)
		ball->Draw(shader);
}

void World::Init() const
{
	cue_->Translate(glm::vec3(-0.4f, Ball::radius_, 0.0f));

	balls_[0]->Translate(glm::vec3(0.8f, 0.0f, 0.0f));

	balls_[1]->Translate(glm::vec3(-0.8f + 2.0f * glm::root_three<float>() * Ball::radius_, 0.0f, 0.0f));

	glm::vec3 temp = balls_[1]->translation_;
	int index = 2;
	for (int i = 0; i < 4; i++)
	{
		temp.x -= glm::root_three<float>() * Ball::radius_;
		temp.z -= Ball::radius_;
		for (int j = 0; j < i + 2; j++)
		{
			balls_[index]->Translate(glm::vec3(temp.x, 0.0f, temp.z + j * (Ball::radius_ * 2.0f)));
			index++;
		}
	}
}
