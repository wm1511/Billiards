#pragma once
#include "Object.hpp"

class Ball final : public Object
{
public:
	explicit Ball(int number);

	void Shot(glm::vec3 power);
	void Roll(float dt);
	void CollideWith(const std::shared_ptr<Ball>& ball);

	[[nodiscard]] bool IsInMotion() const { return is_in_motion_; }

	inline static constexpr float radius_{ 0.0286f };

	glm::vec3 velocity_{ 0.0f };

private:
	bool is_in_motion_{ false };

};
