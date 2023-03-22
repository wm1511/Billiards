#pragma once
#include <string>
#include <glm/vec3.hpp>

struct Config
{
	// Window
	inline static constexpr int width = 1920;
	inline static constexpr int height = 1080;
	inline static const std::string window_name = "Billiards";

	// Camera
	inline static constexpr int light_count = 3;
	inline static constexpr float fov = 1.3f;
	inline static constexpr float near_clip = 0.001f;
	inline static constexpr float far_clip = 1000.0f;
	inline static constexpr float movement_speed = 2.0f;
	inline static constexpr float rotation_speed = 0.02f;
	inline static constexpr glm::vec3 camera_min_position = {-2.75f, 0.5f, -1.5f};
	inline static constexpr glm::vec3 camera_max_position = {2.75f, 2.5f, 1.5f};

	// Shaders
	inline static const std::string vertex_path = "shader.vert";
	inline static const std::string fragment_path = "shader.frag";
	inline static const std::string text_vertex_path = "text.vert";
	inline static const std::string text_fragment_path = "text.frag";

	// Model
	inline static constexpr float min_change = 0.01f;
	inline static const std::string table_path = "table.obj";
	inline static const std::string cue_path = "cue.obj";
	inline static const std::string ball_path = "ball.obj";

	// Misc
	inline static const std::string font_path = "Silvanowesterndemo-ALA2p.otf";
	inline static constexpr unsigned default_font_size = 40;
};
