#pragma once
#include "Object.hpp"

class Ball final : public Object
{
public:
	Ball();
	explicit Ball(int number);

	inline static constexpr float radius_{0.0286f};

private:
};
