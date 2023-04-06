#pragma once
#include "Object.hpp"
#include "Hole.hpp"

class Ball final : public Object
{
public:
	Ball();
	explicit Ball(int number);

	void Shot(glm::vec3 power);
	void Roll(float dt);
	void CollideWith(const std::shared_ptr<Ball>& ball);
	bool IsInHole(const std::vector<std::shared_ptr<Hole>>& holes);

	inline static constexpr float radius_{ 0.0286f };

	glm::vec3 velocity_{ 0 };
	bool is_in_motion_{ false };

private:
};
