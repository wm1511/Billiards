#include "stdafx.h"
#include "Cue.hpp"

Cue::Cue() : Object(Config::cue_path)
{
}

void Cue::Strike(const std::shared_ptr<Ball>& ball)
{
	//ball.Shot()
}

void Cue::RotateCue(float angle, glm::vec3& rotation_axis)
{
	
	Rotate(rotation_axis, angle);
}

