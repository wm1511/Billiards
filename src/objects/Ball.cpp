#include "stdafx.h"
#include "Ball.hpp"

#include "../wrapper/Loader.hpp"

Ball::Ball() : Object(Config::ball_path) { }

Ball::Ball(const int number) : Object(Config::ball_path)
{
	const auto path = std::filesystem::current_path() / ("assets/mtl/ball" + (number < 10 ? "0" + std::to_string(number) : std::to_string(number)) + ".jpg");
	materials_[0]->diffuse_texture = Loader::LoadTexture(path.string());
}
