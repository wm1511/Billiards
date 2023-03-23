#pragma once
#include <string>
#include <glm/vec3.hpp>

struct Config
{
	// Window
	inline static constexpr int width = 1920;
	inline static constexpr int height = 1080;
	inline static constexpr const char* const window_name = "Billiards";

	// Camera
	inline static constexpr float fov = 1.3f;
	inline static constexpr float near_clip = 0.001f;
	inline static constexpr float far_clip = 1000.0f;
	inline static constexpr float movement_speed = 2.0f;
	inline static constexpr float rotation_speed = 0.02f;
	inline static constexpr glm::vec3 camera_min_position = {-2.75f, 0.5f, -1.5f};
	inline static constexpr glm::vec3 camera_max_position = {2.75f, 2.5f, 1.5f};

	// Shaders
	inline static constexpr const char* const vertex_path = "shader.vert";
	inline static constexpr const char* const fragment_path = "shader.frag";
	inline static constexpr const char* const text_vertex_path = "text.vert";
	inline static constexpr const char* const text_fragment_path = "text.frag";
	inline static constexpr const char* const shadow_vertex_path = "shadow.vert";
	inline static constexpr const char* const shadow_fragment_path = "shadow.frag";
	inline static constexpr const char* const shadow_geometry_path = "shadow.geom";

	// Model
	inline static constexpr float min_change = 0.01f;
	inline static constexpr const char* const table_path = "table.obj";
	inline static constexpr const char* const cue_path = "cue.obj";
	inline static constexpr const char* const ball_path = "ball.obj";

	// Lighting
	inline static constexpr glm::vec3 light_position = {-2.0f, 2.0f, 0.0f};
	inline static constexpr int light_count = 1;
	inline static constexpr int shadow_width = 1024;
	inline static constexpr int shadow_height = 1024;

	// Misc
	inline static constexpr const char* const font_path = "Silvanowesterndemo-ALA2p.otf";
	inline static constexpr unsigned default_font_size = 40;
};
