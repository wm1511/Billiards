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

	// mieszanie bil
	balls_[5].swap(balls_[8]);
	balls_[5].swap(balls_[15]);

	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(balls_.begin() + 1, balls_.end() - 1, rng);

	balls_[5].swap(balls_[15]);
}

void World::Draw(const std::shared_ptr<Shader>& shader) const
{
	table_->Draw(shader);

	if (AreBallsInMotion())
		cue_->PlaceAtBall(balls_[0]);
	else
		cue_->Draw(shader);

	for (const auto& ball : balls_)
		if (ball->IsDrawn())
			ball->Draw(shader);
}

void World::HandleBallsCollision(const int number) const
{
	for (int j = number + 1; j < balls_.size(); j++)
	{
		const auto first_ball = balls_[number];
		auto second_ball = balls_[j];
		first_ball->CollideWith(second_ball);
	}
}

void World::HandleHolesFall(const int number) const
{
	if (!AreBallsInMotion())
	{
		if (number == 0)
		{
			balls_[number]->TakeFromHole();
			balls_[number]->Translate(glm::vec3(0.8f, 0.0f, 0.0f));
			cue_->PlaceAtBall(balls_[0]);
			return;
		}
		
		balls_[number]->SetDrawn(false);
		return;
	}

	if (balls_[number]->translation_.y > Table::hole_bottom_ + Ball::radius_)
		balls_[number]->translation_.y -= 0.005f;

	const auto translation_horizontal = glm::vec2(balls_[number]->translation_.x, balls_[number]->translation_.z);
	const auto hole_horizontal = glm::vec2(balls_[number]->GetHole().x, balls_[number]->GetHole().z);

	const glm::vec2 direction = glm::normalize(translation_horizontal - hole_horizontal);
	const float distance = glm::distance(translation_horizontal, hole_horizontal);

	if (distance > Table::hole_radius_ - Ball::radius_)
		balls_[number]->BounceOffHole(-direction, Table::hole_radius_);
}

void World::HandleBoundsCollision(const int number) const
{
	const auto ball_pos = balls_[number]->translation_;
	constexpr auto hole_edge_z = 0.7f - Table::hole_radius_ - Ball::radius_;
	constexpr auto hole_edge_x = 1.35f - Table::hole_radius_ - Ball::radius_;

	if (ball_pos.x >= Table::bound_x_ && ball_pos.z < hole_edge_z && ball_pos.z > -hole_edge_z)
	{
		balls_[number]->BounceOffBound(glm::vec3(-1.0f, 0.0f, 0.0f), Table::bound_x_, Table::bound_z_);
	}
	else if (ball_pos.x <= -Table::bound_x_ && ball_pos.z < hole_edge_z && ball_pos.z > -hole_edge_z)
	{
		balls_[number]->BounceOffBound(glm::vec3(1.0f, 0.0f, 0.0f), Table::bound_x_, Table::bound_z_);
	}
	else if (ball_pos.z >= Table::bound_z_ &&
		((ball_pos.x < hole_edge_x && ball_pos.x > Table::hole_radius_) ||
		(ball_pos.x > -hole_edge_x && ball_pos.x < -Table::hole_radius_)))
	{
		balls_[number]->BounceOffBound(glm::vec3(0.0f, 0.0f, -1.0f), Table::bound_x_, Table::bound_z_);
	}
	else if (ball_pos.z <= -Table::bound_z_ &&
		((ball_pos.x < hole_edge_x && ball_pos.x > Table::hole_radius_) ||
		(ball_pos.x > -hole_edge_x && ball_pos.x < -Table::hole_radius_)))
	{
		balls_[number]->BounceOffBound(glm::vec3(0.0f, 0.0f, 1.0f), Table::bound_x_, Table::bound_z_);
	}
}

void World::Update(const float dt, const bool in_game) const
{
	if (in_game)
		cue_->HandleShot(balls_[0], dt);

	if (balls_.size() == 1)
		Reset();

	for (int i = 0; i < balls_.size(); i++)
	{
		balls_[i]->Roll(dt);

		if (balls_[i]->IsInHole(table_->GetHoles(), Table::hole_radius_))
			HandleHolesFall(i);
		else
			HandleBoundsCollision(i);

		HandleBallsCollision(i);
	}
}

bool World::AreBallsInMotion() const
{
	for (const auto& ball : balls_)
		if (ball->IsInMotion())
			return true;

	return false;
}

void World::Init() const
{
	// ustawianie białej i kija na pozycji początkowej
	balls_[0]->Translate(glm::vec3(0.8f, 0.0f, 0.0f));
	cue_->translation_ = glm::vec3(0.0f);
	cue_->angle_ = 0.0f;
	cue_->Translate(glm::vec3(0.8f + Ball::radius_ + Config::min_change, Ball::radius_, 0.0f));
	cue_->Rotate(glm::vec3(-0.1f, 1.0f, 0.0f), glm::pi<float>());

	// tworzenie trójkąta
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

void World::Reset() const
{
	for (const auto& ball : balls_)
	{
		ball->TakeFromHole();
		ball->SetDrawn(true);
	}

	Init();
}
