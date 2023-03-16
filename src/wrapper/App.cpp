#include "stdafx.h"
#include "App.hpp"

App::App() :
	window_(std::make_unique<Window>()),
	camera_(std::make_shared<Camera>()),
	shader_(std::make_shared<Shader>()),
	table_(std::make_shared<Table>()),
	cue_(std::make_unique<Cue>())
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); 
	glViewport(0, 0, window_->GetWidth(), window_->GetHeight());

	//for (int i = 0; i < 16; i++)
		balls_.emplace_back(std::make_shared<Ball>(1));

	balls_[0]->Translate(glm::vec3(0.0f, 0.4f, -0.5f));

	cue_->Rotate(glm::vec3(1.57f, 0.0f, 0.0f));
	cue_->Translate(glm::vec3(1.0f, 1.0f, 0.0f));
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
	camera_->UpdateShader(shader_);

	table_->Draw(shader_);
	cue_->Draw(shader_);
	balls_[0]->Draw(shader_);

	frame_time_ = static_cast<float>(glfwGetTime() - start);
}

void App::OnResize() const
{
	const int new_width = window_->GetWidth(), new_height = window_->GetHeight();

	glViewport(0, 0, new_width, new_height);
	camera_->UpdateProjectionMatrix(new_width, new_height);
	window_->ResetResizedFlag();
}
