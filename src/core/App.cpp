#include "stdafx.h"
#include "App.hpp"

App::App() :
	window_(std::make_unique<Window>()),
	camera_(std::make_unique<Camera>()),
	world_(std::make_unique<World>()),
	text_renderer_(std::make_unique<TextRenderer>()),
	shader_(std::make_shared<Shader>(Config::vertex_path, Config::fragment_path))
{
	Init();
	camera_->Init();
	world_->Init();
	text_renderer_->Init();
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

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_->UpdateViewMatrix(frame_time_);
	camera_->Update(shader_);

	world_->Draw(shader_);

	text_renderer_->Render(u"Nie wiem co to złożoność obliczeniowa", 20.0f, 40.0f);

	frame_time_ = static_cast<float>(glfwGetTime() - start);
}

void App::OnResize() const
{
	const int new_width = window_->GetWidth(), new_height = window_->GetHeight();

	glViewport(0, 0, new_width, new_height);
	camera_->UpdateProjectionMatrix(new_width, new_height);

	text_renderer_->UpdateProjectionMatrix(new_width, new_height);
	text_renderer_->Update();

	window_->ResetResizedFlag();
}

void App::Init() const
{
	glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); 
	glViewport(0, 0, window_->GetWidth(), window_->GetHeight());
}
