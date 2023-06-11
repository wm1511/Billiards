#pragma once
#include "Cue.hpp"
#include "Table.hpp"
#include "Object.hpp"
#include "Ball.hpp"

class World
{
public:
	World();
	void Update(float dt, bool in_game) const;
	void Draw(const std::shared_ptr<Shader>& shader) const;
	void Init() const;
	void Reset() const;
	void HandleBallsCollision(int number) const;
	void HandleHolesFall(int number) const;
	void HandleBoundsCollision(int number) const;
	[[nodiscard]] bool AreBallsInMotion() const;

private:
	std::shared_ptr<Table> table_ = nullptr;
	std::shared_ptr<Cue> cue_ = nullptr;
	std::vector<std::shared_ptr<Ball>> balls_{};
};
