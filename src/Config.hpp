#pragma once
#include <string>
#include <glm/vec3.hpp>

struct Config final
{
	Config() = delete;

	// Window
	inline static constexpr int width = 1920;
	inline static constexpr int height = 1080;
	inline static constexpr const char* const window_name = "Billiards";

	// Camera
	inline static constexpr bool bound_camera = true;
	inline static constexpr float fov = 1.3f;
	inline static constexpr float near_clip = 0.001f;
	inline static constexpr float far_clip = 1000.0f;
	inline static constexpr float movement_speed = 2.0f;
	inline static constexpr float rotation_speed = 0.05f;
	inline static constexpr glm::vec3 camera_min_position = { -1.4f, 0.25f, -0.75f };
	inline static constexpr glm::vec3 camera_max_position = { 1.4f, 1.75f, 0.75f };

	// Shaders
	inline static constexpr const char* const vertex_path = "shader.vert";
	inline static constexpr const char* const fragment_path = "shader.frag";
	inline static constexpr const char* const text_vertex_path = "text.vert";
	inline static constexpr const char* const text_fragment_path = "text.frag";
	inline static constexpr const char* const cubemap_vertex_path = "cubemap.vert";
	inline static constexpr const char* const cubemap_fragment_path = "cubemap.frag";
	inline static constexpr const char* const brdf_vertex_path = "brdf.vert";
	inline static constexpr const char* const brdf_fragment_path = "brdf.frag";
	inline static constexpr const char* const background_vertex_path = "background.vert";
	inline static constexpr const char* const background_fragment_path = "background.frag";
	inline static constexpr const char* const irradiance_fragment_path = "irradiance.frag";
	inline static constexpr const char* const prefilter_fragment_path = "prefilter.frag";

	// Model
	inline static constexpr float min_change = 0.001f;
	inline static constexpr const char* const table_path = "table.obj";
	inline static constexpr const char* const cue_path = "cue.obj";
	inline static constexpr const char* const ball_path = "ball.obj";

	// Lighting
	inline static constexpr int light_count = 3;
	inline static constexpr const char* const hdr_path = "comfy_cafe_4k.hdr";
	inline static constexpr int cube_map_size = 1024;
	inline static constexpr int irradiance_scale = 32;
	inline static constexpr int prefilter_scale = 256;
	inline static constexpr int max_mip_levels = 5;

	// Font
	inline static constexpr const char* const font_path = "Silvanowesterndemo-ALA2p.otf";
	inline static constexpr unsigned default_font_size = 40;

	// Physics
	inline static constexpr float power_coeff = 10.0f;
	inline static constexpr float velocity_multiplier = 0.985f;
};
