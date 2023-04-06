#pragma once
#include "Object.hpp"

#pragma once
#include "Ball.hpp"
#include "Hole.hpp"

class Table final : public Object
{
public:
	Table();
	void HandleCollision(const std::shared_ptr<Ball>& ball) const;
	std::vector<std::shared_ptr<Hole>> holes_{};

private:
	inline static constexpr float bound_x_ = 1.35f - Ball::radius_ - 0.042f;
	inline static constexpr float bound_z_ = 0.7f - Ball::radius_ - 0.042f;
};
