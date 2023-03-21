#pragma once
#include "../objects/World.hpp"
#include "../interface/Camera.hpp"
#include "../interface/Window.hpp"
#include "../interface/TextRenderer.hpp"

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
	void Init() const;

	std::unique_ptr<Window> window_ = nullptr;
	std::unique_ptr<Camera> camera_ = nullptr;
	std::unique_ptr<World> world_ = nullptr;
	std::unique_ptr<TextRenderer> text_renderer_ = nullptr;

	std::shared_ptr<Shader> shader_ = nullptr;

	float frame_time_{1.0f};
};