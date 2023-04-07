#pragma once
#include "Ball.hpp"

class Table final : public Object
{
public:
	Table();

	[[nodiscard]] const std::vector<glm::vec3>& GetHoles() const { return holes_; }

	inline static constexpr float hole_radius_{ 0.07f };
	inline static constexpr float hole_bottom_{ -0.14324f };
	inline static constexpr float bound_x_{1.35f - Ball::radius_ - 0.042f};
	inline static constexpr float bound_z_{0.7f - Ball::radius_ - 0.042f};

private:
	std::vector<glm::vec3> holes_{};
};
