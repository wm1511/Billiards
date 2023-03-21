#pragma once
#include "../objects/Cue.hpp"
#include "../objects/Table.hpp"
#include "../objects/Object.hpp"
#include "../objects/Ball.hpp"

class World
{
public:
	World();

	void Draw(const std::shared_ptr<Shader>& shader) const;
	void Init() const;
	
private:
	std::shared_ptr<Table> table_ = nullptr;
	std::shared_ptr<Cue> cue_ = nullptr;
	std::vector<std::shared_ptr<Ball>> balls_{};
};