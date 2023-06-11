#include "stdafx.h"
#include "App.hpp"

App::App() :
	window_(std::make_unique<Window>()),
	text_renderer_(std::make_unique<TextRenderer>()),
	menu_(std::make_unique<Menu>(window_->GetWidth(), window_->GetHeight())),
	main_shader_(std::make_shared<Shader>(Config::vertex_path, Config::fragment_path)),
	background_shader_(std::make_shared<Shader>(Config::background_vertex_path, Config::background_fragment_path))
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	HandleState();

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (world_)
	{
		camera_->UpdateViewMatrix(static_cast<float>(delta_time_));
		camera_->UpdateMain(main_shader_);

		environment_->Prepare();
		world_->Update(static_cast<float>(delta_time_), !in_menu_);
		world_->Draw(main_shader_);

		camera_->UpdateBackground(background_shader_);
		environment_->Draw(background_shader_);
	}

	if (in_menu_)
		menu_->Draw();

	menu_->AddText(0.0f, 0.95f, BuildString("FPS: {}", static_cast<int>(1.0f / delta_time_), 0.75f));
	text_renderer_->Render(menu_->GetTexts());
}

void App::OnResize() const
{
	const int new_width = window_->GetWidth(), new_height = window_->GetHeight();

	glViewport(0, 0, new_width, new_height);

	if (camera_)
		camera_->UpdateProjectionMatrix(new_width, new_height);

	menu_->Update(new_width, new_height);

	text_renderer_->UpdateProjectionMatrix(new_width, new_height);
	text_renderer_->Update();

	window_->ResetResizedFlag();
}

void App::Load()
{
	camera_ = std::make_unique<Camera>();
	world_ = std::make_unique<World>();
	environment_ = std::make_unique<Environment>();

	camera_->Init();
	world_->Init();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_MULTISAMPLE);
	glViewport(0, 0, window_->GetWidth(), window_->GetHeight());

	main_shader_->Bind();
	main_shader_->SetInt(1, "irradianceMap");
	main_shader_->SetInt(2, "prefilterMap");
	main_shader_->SetInt(3, "brdfLUT");
	main_shader_->SetInt(4, "material.diffuseMap");
	main_shader_->SetInt(5, "material.roughnessMap");
	main_shader_->SetInt(6, "material.normalMap");
	main_shader_->SetInt(7, "material.aoMap");
	main_shader_->SetInt(8, "material.metallicMap");
	main_shader_->Unbind();
}

void App::HandleState()
{
	GLFWwindow* window = window_->GetGLFWWindow();
	const int selected = menu_->GetSelected();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		in_menu_ = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (selected == 1)
	{
		menu_->DrawHelp();
	}
	else if (selected == 3)
	{
		menu_->AddText(0.6f, 0.4f, BuildString(": {}", Config::power_coeff), 0.75f);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			Config::power_coeff -= 0.02f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			Config::power_coeff += 0.02f; 
	}
	else if (selected == 4)
	{
		menu_->AddText(0.6f, 0.3f, BuildString(": {}", 1.0f / Config::velocity_multiplier), 0.75f);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			Config::velocity_multiplier += 0.0001f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			Config::velocity_multiplier -= 0.0001f;
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		if (selected == 0)
		{
			in_menu_ = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (!world_)
				Load();
		}
		else if (selected == 2)
		{
			if (world_)
			{
				world_->Reset();
				in_menu_ = false;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
		}
		else if (selected == 6)
		{
			window_->SetCloseFlag();
		}
	}
}
