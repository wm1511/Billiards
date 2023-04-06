#include "stdafx.h"
#include "World.hpp"
#include "../Config.hpp"

World::World() :
	table_(std::make_shared<Table>()),
	cue_(std::make_shared<Cue>())
{
	for (int n = 0; n < 16; n++)
	{
		balls_.push_back(std::make_shared<Ball>(n));
		balls_[n]->Translate(glm::vec3{ 0.0f, Ball::radius_, 0.0f });
	}
}

void World::Draw(const std::shared_ptr<Shader>& shader) const
{
	table_->Draw(shader);

	if (AreBallsInMotion())
	{
		cue_->translation_.x = balls_[0]->translation_.x + Ball::radius_ + Config::min_change;
		cue_->translation_.z = balls_[0]->translation_.z;
		cue_->angle_ = glm::pi<float>();
	}
	else
	{
		cue_->Draw(shader);
	}

	for (const auto& ball : balls_)
		ball->Draw(shader);
}

void World::HandleBallsCollision() const
{
	for (int i = 0; i < balls_.size(); i++)
	{
		for (int j = i + 1; j < balls_.size(); j++)
		{
			auto first_ball = balls_[i];
			auto second_ball = balls_[j];
			first_ball->CollideWith(second_ball);
		}
	}
}

void World::Update(const float dt)
{
	KeyListener();
	for (int i = 0; i < balls_.size(); i++)
	{
		balls_[i]->Roll(dt);
		table_->HandleCollision(balls_[i]);

		//if (balls_.size() == 1)
			//reset gry;

		if (balls_[i]->IsInHole(table_->holes_))
		{
			if (i != 0)
			{
				balls_.erase(balls_.begin() + i);
			}
			else
			{
				balls_[0]->translation_ = glm::vec3(0.8f, Ball::radius_, 0.0f);
			}
		}
	}

	HandleBallsCollision();
}

void World::KeyListener() const
{
	const auto window = glfwGetCurrentContext();
	const auto cue_direction = glm::vec3(sin(cue_->angle_), 0.0f, cos(cue_->angle_));

	const auto up = glm::vec3(0.0f, 1.0f, 0.0f);
	const auto power_vector = glm::cross(cue_direction, up);
	auto power = glm::distance(cue_->translation_, balls_[0]->translation_);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (!cue_->power_changed_)
		{
			cue_->Translate(0.01f * Ball::radius_ * cue_direction);
			cue_->angle_ += 0.01f;
		}
	}


	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (!cue_->power_changed_)
		{
			cue_->Translate(-0.01f * Ball::radius_ * cue_direction);
			cue_->angle_ -= 0.01f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (power > Ball::radius_ + Config::min_change)
		{
			cue_->Translate(-power_vector * 0.01f);
			cue_->power_changed_ = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (power <= 0.5f)
		{
			cue_->Translate(power_vector * 0.01f);
			cue_->power_changed_ = true;
		}
	}

	//STRIKE
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		power *= Config::power_coeff;
		balls_[0]->Shot(-power_vector * power);
		cue_->power_changed_ = false;
	}
}



bool World::AreBallsInMotion() const
{
	for (const auto& ball : balls_)
	{
		if (length(ball->velocity_) >= Config::min_change)
		{
			ball->is_in_motion_ = true;
			return true;
		}

		ball->is_in_motion_ = false;
	}

	return false;
}

void World::Init() const
{
	balls_[0]->Translate(glm::vec3(0.8f, 0.0f, 0.0f));

	cue_->Translate(glm::vec3(0.8f + Ball::radius_ + Config::min_change, Ball::radius_, 0.0f));

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


