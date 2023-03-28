#pragma once
#include "Ball.hpp"

class Cue final : public Object
{
public:
	Cue();
	void Strike(const std::shared_ptr<Ball>& ball);
	void SetAngle(float angle);
	void RotateCue(float angle, glm::vec3& rotation_axis);

	float power_{ };
	glm::vec3 direction_{};

private:

};
