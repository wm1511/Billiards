#pragma once
#include <string>

struct Config
{
	// Window
	inline static constexpr int width = 1920;
	inline static constexpr int height = 1080;
	inline static const std::string window_name = "Billiards";

	// Camera
	inline static constexpr float fov = 75.0f;
	inline static constexpr float near_clip = 0.001f;
	inline static constexpr float far_clip = 1000.0f;
	inline static constexpr float movement_speed = 0.05f;
	inline static constexpr float rotation_speed = 0.0005f;

	// Shader
	inline static const std::string vertex_path = "shader.vert";
	inline static const std::string fragment_path = "shader.frag";

	// Model
	inline static constexpr float min_change = 0.01f;
	inline static const std::string table_path = "table.obj";
	inline static const std::string cue_path = "cue.obj";
	inline static const std::string ball_path = "ball.obj";
};
