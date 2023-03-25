#include "stdafx.h"
#include "App.hpp"

App::App() :
	window_(std::make_unique<Window>()),
	camera_(std::make_unique<Camera>()),
	world_(std::make_unique<World>()),
	environment_(std::make_unique<Environment>()),
	text_renderer_(std::make_unique<TextRenderer>()),
	main_shader_(std::make_shared<Shader>(Config::vertex_path, Config::fragment_path)),
	background_shader_(std::make_shared<Shader>(Config::background_vertex_path, Config::background_fragment_path))
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
	const double current_frame = glfwGetTime();
	delta_time_ = current_frame - last_frame_;
	last_frame_ = current_frame;

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	main_shader_->Bind();

	main_shader_->SetInt(1, "irradianceMap");
    main_shader_->SetInt(2, "prefilterMap");
    main_shader_->SetInt(3, "brdfLUT");
	main_shader_->SetInt(4, "material.diffuseMap");
	main_shader_->SetInt(5, "material.roughnessMap");
	main_shader_->SetInt(6, "material.normalMap");
	main_shader_->SetInt(7, "material.aoMap");
	main_shader_->SetInt(8, "material.metallicMap");

	camera_->UpdateViewMatrix(static_cast<float>(delta_time_));
	camera_->UpdateMain(main_shader_);

	//environment_->Prepare();

	world_->Draw(main_shader_);

	background_shader_->Bind();

	camera_->UpdateBackground(background_shader_);

	environment_->Draw(background_shader_);

	text_renderer_->Render(0.0f, static_cast<float>(window_->GetHeight() - Config::default_font_size), "FPS: {}", static_cast<int>(1.0 / delta_time_));
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_MULTISAMPLE);
	glViewport(0, 0, window_->GetWidth(), window_->GetHeight());
}
