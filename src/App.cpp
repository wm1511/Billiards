#include "stdafx.h"
#include "App.hpp"
#include "Loader.hpp"

App::App() :
	window_(std::make_unique<Window>(1920, 1080, "Billiards")),
	camera_(std::make_shared<Camera>(90.0f, 0.001f, 1000.0f, 100.0f, 1.0f)),
	shader_(std::make_shared<Shader>("vertex.glsl", "fragment.glsl"))
{
	auto vertices = std::vector<Vertex>();
	auto indices = std::vector<unsigned>();

	Loader::Load("test.obj", vertices, indices);

	model_ = std::make_shared<VertexIndexBuffer>(vertices, indices);

	glViewport(0, 0, window_->GetWidth(), window_->GetHeight());
}

void App::Run()
{
	while (!window_->ShouldClose())
	{
		glfwPollEvents();

		if (window_->Resized())
			OnResize();

		OnUpdate();

		glfwSwapBuffers(window_->GetGLFWWindow());
	}
}

void App::OnUpdate()
{
	const auto start = std::chrono::high_resolution_clock::now();

	camera_->UpdateView(frame_time_);
	Renderer::Update(shader_, camera_);
	Renderer::Render(shader_, model_);

	frame_time_ = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - start).count();
}

void App::OnResize() const
{
	const int new_width = window_->GetWidth(), new_height = window_->GetHeight();

	glViewport(0, 0, new_width, new_height);
	camera_->UpdateProjection(new_width, new_height);
	window_->ResetResizedFlag();
}
