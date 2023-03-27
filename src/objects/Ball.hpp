#pragma once
#include "Object.hpp"

class Ball final : public Object
{
public:
	Ball();
	explicit Ball(int number);

	void Shot(const float power, float angle);
	void Roll(const float dt);

	inline static constexpr float radius_{ 0.0286f };

	glm::vec3 velocity{ 0 };
	glm::vec3 angular_velocity{ 0 };

private:
};
