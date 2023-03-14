#pragma once
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

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
	std::shared_ptr<VertexIndexBuffer> model_ = nullptr;

	float frame_time_{1.0f};
};