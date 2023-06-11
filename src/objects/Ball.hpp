#pragma once
#include "Object.hpp"

class Ball final : public Object
{
public:
	explicit Ball(int number);

	void Shot(glm::vec3 power);
	void Roll(float dt);
	void CollideWith(const std::shared_ptr<Ball>& ball);
	void BounceOffBound(glm::vec3 surface_normal, float bound_x, float bound_z);
	void BounceOffHole(glm::vec2 surface_normal, float hole_radius);
	void TakeFromHole();
	void SetDrawn(bool drawn);

	[[nodiscard]] bool IsInHole(const std::vector<glm::vec3>& holes, float hole_radius);
	[[nodiscard]] bool IsInMotion() const { return glm::length(velocity_) > 0.01f; }
	[[nodiscard]] bool IsDrawn() const { return is_drawn_; }
	[[nodiscard]] const glm::vec3& GetHole() const { return hole_; }

	inline static constexpr float radius_{ 0.0286f };

private:
	bool is_in_hole_{false};
	bool is_drawn_{true};
	glm::vec3 velocity_{ 0.0f };
	glm::vec3 hole_{};
};
