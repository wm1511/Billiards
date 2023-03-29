#include "stdafx.h"
#include "World.hpp"

World::World() :
	table_(std::make_shared<Table>()),
	cue_(std::make_shared<Cue>())
{
	//cue_->Rotate(glm::vec3(0,1,0), glm::half_pi<float>());
	for (int n = 0; n < 16; n++)
	{
		balls_.push_back(std::make_shared<Ball>(n));
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

void World::Update(const float dt) const
{
	KeyListener(dt);
	balls_[0]->Roll(dt);
	table_->HandleCollision(balls_[0]);
}

void World::KeyListener(const float dt) const
{
	auto ctx = glfwGetCurrentContext();
	auto cue_direction = glm::vec3(sin(cue_->angle_), 0, cos(cue_->angle_));

	auto up = glm::vec3(0, 1, 0);
	auto power_vector = glm::cross(cue_direction, up);
	auto power = glm::distance(cue_->translation_, balls_[0]->translation_);

	auto white_ball_dir = balls_[0]->translation_;

	if (glfwGetKey(ctx, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		cue_->Translate(0.01f * Ball::radius_ * cue_direction);
		cue_->angle_ += 0.01f;
	}

	if (glfwGetKey(ctx, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		cue_->Translate(-0.01f * Ball::radius_ * cue_direction);
		cue_->angle_ -= 0.01f;
	}

	if (glfwGetKey(ctx, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (power > Ball::radius_)
			cue_->Translate(-power_vector * 0.01f);
	}

	if (glfwGetKey(ctx, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (power <= 0.5f)
			cue_->Translate(power_vector * 0.01f);
	}

	//STRIKE
	if (glfwGetKey(ctx, GLFW_KEY_F) == GLFW_PRESS)
	{
		power *= 100;
		cue_->Strike(balls_[0], -power_vector * power);
	}
}

void World::Init() const
{
	balls_[0]->Translate(glm::vec3(0.8f, 0.0f, 0.0f));

	cue_->Translate(glm::vec3(0.8f + Ball::radius_ + 0.001f, Ball::radius_, 0.0f));

	cue_->Rotate(glm::vec3(0, 1, 0), glm::pi<float>());


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


