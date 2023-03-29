#pragma once
#include "Ball.hpp"

class Cue final : public Object
{
public:
	Cue();
	void Strike(const std::shared_ptr<Ball>& ball, glm::vec3 power);

private:

};
