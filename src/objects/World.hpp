#pragma once
#include "Cue.hpp"
#include "Table.hpp"
#include "Object.hpp"
#include "Ball.hpp"

class World
{
public:
	World();
	void Update(float dt);
	void Draw(const std::shared_ptr<Shader>& shader) const;
	void Init() const;
	void KeyListener() const;
	void HandleBallsCollision() const;
	[[nodiscard]] bool AreBallsInMotion() const;

private:
	std::shared_ptr<Table> table_ = nullptr;
	std::shared_ptr<Cue> cue_ = nullptr;
	std::vector<std::shared_ptr<Ball>> balls_{};
};
