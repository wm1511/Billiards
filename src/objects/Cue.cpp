#include "stdafx.h"
#include "Cue.hpp"

Cue::Cue() : Object(Config::cue_path)
{
}

void Cue::Strike(const std::shared_ptr<Ball>& ball, glm::vec3 power)
{
	ball->Shot(power);
}