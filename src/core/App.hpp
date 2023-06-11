#pragma once
#include "../objects/World.hpp"
#include "../objects/Environment.hpp"
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
	void Load();
	void HandleState();

	std::unique_ptr<Window> window_ = nullptr;
	std::unique_ptr<Camera> camera_ = nullptr;
	std::unique_ptr<World> world_ = nullptr;
	std::unique_ptr<Environment> environment_ = nullptr;
	std::unique_ptr<TextRenderer> text_renderer_ = nullptr;
	std::unique_ptr<Menu> menu_ = nullptr;
	std::shared_ptr<Shader> main_shader_ = nullptr;
	std::shared_ptr<Shader> background_shader_ = nullptr;

	bool in_menu_{true};
	double delta_time_ = 0.0f;	
	double last_frame_ = 0.0f;
};
