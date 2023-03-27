#include "stdafx.h"
#include "World.hpp"

World::World() :
	table_(std::make_shared<Table>()),
	cue_(std::make_shared<Cue>())
{

	for (int n = 0; n < 16; n++)
	{
		ball.push_back(std::make_shared<Ball>(n));
		ball[n]->Translate(glm::vec3{ 0.0f, Ball::radius_, 0.0f });
	}
}

void World::Draw(const std::shared_ptr<Shader>& shader) const
{
	table_->Draw(shader);
	cue_->Draw(shader);
	for (const auto& ball : ball)
		ball->Draw(shader);
}

float power = 70 ;
float angle = 0.8f;
bool isShot = true;
void World::Update(const float dt) const
{
	isShot = false;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F) == GLFW_PRESS)
		isShot = true;

	if (isShot)
		ball[0]->Shot(power, angle);
	ball[0]->Roll(dt);

	table_->HandleCollision(ball[0]);

	//balls_[0]->Roll(dt, chuj);
	/*float normalForce = Config::gravity_acc * Ball::mass;
	float frictionForce = Config::friction_coeff * normalForce;
	float acc = (force - frictionForce) / Ball::mass;
	balls_[0]->velocity += acc * dt * 0.00001f;
	balls_[0]->angular_velocity = balls_[0]->velocity / Ball::radius_;

	if (balls_[0]->velocity <= 0)
	{
		balls_[0]->velocity = 0;
	}

	balls_[0]->Translate(glm::vec3(-balls_[0]->velocity, 0, 0));
	balls_[0]->Rotate(glm::vec3(0, 0, balls_[0]->angular_velocity));
	force -= force * dt;*/
}

void World::Init() const
{
	cue_->Translate(glm::vec3(-0.4f, Ball::radius_, 0.0f));

	ball[0]->Translate(glm::vec3(0.8f, 0.0f, 0.0f));

	ball[1]->Translate(glm::vec3(-0.8f + 2.0f * glm::root_three<float>() * Ball::radius_, 0.0f, 0.0f));

	glm::vec3 temp = ball[1]->translation_;
	int index = 2;
	for (int i = 0; i < 4; i++)
	{
		temp.x -= glm::root_three<float>() * Ball::radius_;
		temp.z -= Ball::radius_;
		for (int j = 0; j < i + 2; j++)
		{
			ball[index]->Translate(glm::vec3(temp.x, 0.0f, temp.z + j * (Ball::radius_ * 2.0f)));
			index++;
		}
	}
}
