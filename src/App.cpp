#include "stdafx.h"
#include "App.hpp"

App::App() :
	window_(std::make_unique<Window>(1920, 1080, "Billiards")),
	camera_(std::make_shared<Camera>(90.0f, 0.001f, 1000.0f, 0.1f, 0.001f)),
	shader_(std::make_shared<Shader>("vertex.glsl", "fragment.glsl")),
	table_(std::make_shared<Table>())
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); 
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
	const auto start = glfwGetTime();

	camera_->UpdateView(frame_time_);
	Renderer::Update(shader_, camera_);
	Renderer::Update(shader_, table_);
	Renderer::Render(shader_, table_);

	frame_time_ = static_cast<float>(glfwGetTime() - start);
}

void App::OnResize() const
{
	const int new_width = window_->GetWidth(), new_height = window_->GetHeight();

	glViewport(0, 0, new_width, new_height);
	camera_->UpdateProjection(new_width, new_height);
	window_->ResetResizedFlag();
}
