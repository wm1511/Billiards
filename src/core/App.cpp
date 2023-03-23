#include "stdafx.h"
#include "App.hpp"

App::App() :
	window_(std::make_unique<Window>()),
	camera_(std::make_unique<Camera>()),
	world_(std::make_unique<World>()),
	text_renderer_(std::make_unique<TextRenderer>()),
	cube_map_(std::make_unique<CubeMap>()),
	shader_(std::make_shared<Shader>(Config::vertex_path, Config::fragment_path)),
	shadow_shader_(std::make_shared<Shader>(Config::shadow_vertex_path, Config::shadow_fragment_path, Config::shadow_geometry_path))
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

	const glm::mat4 shadow_proj = glm::perspective(Config::fov, static_cast<float>(Config::shadow_width) / static_cast<float>(Config::shadow_height), Config::near_clip, Config::far_clip);
    std::vector<glm::mat4> shadow_transforms;
    shadow_transforms.push_back(shadow_proj * glm::lookAt(Config::light_position, Config::light_position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadow_transforms.push_back(shadow_proj * glm::lookAt(Config::light_position, Config::light_position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadow_transforms.push_back(shadow_proj * glm::lookAt(Config::light_position, Config::light_position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadow_transforms.push_back(shadow_proj * glm::lookAt(Config::light_position, Config::light_position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadow_transforms.push_back(shadow_proj * glm::lookAt(Config::light_position, Config::light_position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadow_transforms.push_back(shadow_proj * glm::lookAt(Config::light_position, Config::light_position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	glViewport(0, 0, Config::shadow_width, Config::shadow_height);
    cube_map_->BindBuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    shadow_shader_->Bind();
    for (unsigned int i = 0; i < 6; ++i)
        shadow_shader_->SetMat4( shadow_transforms[i], "shadowMatrices[" + std::to_string(i) + "]");
    shadow_shader_->SetFloat(Config::far_clip, "far_plane");
    shadow_shader_->SetVec3(Config::light_position, "lightPos");

	cube_map_->Draw(shadow_shader_);
	world_->Draw(shadow_shader_);

	shadow_shader_->Unbind();
	cube_map_->UnbindBuffer();

	glViewport(0, 0, window_->GetWidth(), window_->GetHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_->UpdateViewMatrix(static_cast<float>(delta_time_));
	camera_->Update(shader_);

	cube_map_->Draw(shader_, GL_TEXTURE_CUBE_MAP);
	world_->Draw(shader_);

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
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glViewport(0, 0, window_->GetWidth(), window_->GetHeight());

	cube_map_->Scale(glm::vec3{ 10.0f });
}
