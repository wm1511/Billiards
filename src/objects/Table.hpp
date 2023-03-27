#pragma once
#include "Object.hpp"

#pragma once
#include "Ball.hpp"

class Table final : public Object
{
public:
	Table();
	void HandleCollision(const std::shared_ptr<Ball>& ball);


private:

};
