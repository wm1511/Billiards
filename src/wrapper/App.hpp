#pragma once
#include "../objects/Ball.hpp"
#include "../interface//Camera.hpp"
#include "../objects/Cue.hpp"
#include "../objects/Table.hpp"
#include "../interface/Window.hpp"

class App
{
public:
	App();
	~App() = default;

	App(const App&) = delete;
	App(App&&) = delete;
	App& operator= (const App&) = delete;
	App& operator= (App&&) = delete;

	void Run();

private:
	void OnUpdate();
	void OnResize() const;

	std::unique_ptr<Window> window_ = nullptr;
	std::shared_ptr<Camera> camera_ = nullptr;
	std::shared_ptr<Shader> shader_ = nullptr;
	std::shared_ptr<Table> table_ = nullptr;
	std::shared_ptr<Cue> cue_ = nullptr;
	std::vector<std::shared_ptr<Ball>> balls_{};

	float frame_time_{1.0f};
};