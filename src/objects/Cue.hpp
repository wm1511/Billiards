#pragma once
#include "Ball.hpp"

class Cue final : public Object
{
public:
	Cue();
	void HandleShot(const std::shared_ptr<Ball>& white_ball, float dt);
	void PlaceAtBall(const std::shared_ptr<Ball>& ball);

private:
	[[nodiscard]] glm::vec3 CalculateRotationAxis() const;

	bool power_changed_{false};

};
