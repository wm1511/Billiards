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

float power = 70;
float angle = 0.8f;
bool isShot = true;
void World::Update(const float dt) const
{
	isShot = false;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F) == GLFW_PRESS)
		isShot = true;

	KeyListener(dt);

	if (isShot)
		balls_[0]->Shot(power, angle);
	balls_[0]->Roll(dt);
	table_->HandleCollision(balls_[0]);
}

void World::KeyListener(const float dt) const
{
	auto ctx = glfwGetCurrentContext();
	//auto chuj = glm::vec3(balls_[0]->translation_.x, 1, balls_[0]->translation_.z);
	auto up = glm::vec3(0, 1, 0);
	auto dir = glm::vec3(cos(cue_->angle_), 0, sin(cue_->angle_));
	auto temp = glm::vec4(1.0f);
	cue_->power_ = 0.015f;

	if (glfwGetKey(ctx, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		cue_->Translate(0.01f * Ball::radius_ * glm::vec3(sin(cue_->angle_), 0, cos(cue_->angle_)));
		cue_->angle_ += 0.01f;
	}

	if (glfwGetKey(ctx, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		cue_->Translate(-0.01f * Ball::radius_ * glm::vec3(sin(cue_->angle_), 0, cos(cue_->angle_)));
		cue_->angle_ -= 0.01f;
	}

	if (glfwGetKey(ctx, GLFW_KEY_UP) == GLFW_PRESS)
	{
		//cue_->power_ += 0.001f;
		cue_->Translate(0.01f);

	}
	////cue_->Translate(glm::vec3(cos(cue_->angle_), 0, sin(cue_->angle_)) * 0.001f);

	if (glfwGetKey(ctx, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		//cue_->power_ -= 0.001f;
		cue_->Translate(-dir * cue_->power_);
	}
	//cue_->power_ -= 0.001f;
	//cue_->Translate(-glm::vec3(cos(cue_->angle_), 0, sin(cue_->angle_)) * 0.001f);



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


