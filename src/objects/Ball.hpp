#pragma once
#include "Object.hpp"

class Ball final : public Object
{
public:
	Ball();
	explicit Ball(int number);

	void Shot(glm::vec3 power);
	void Roll(const float dt);

	inline static constexpr float radius_{ 0.0286f };

	glm::vec3 velocity{ 0 };

private:
};
