#pragma once
#include "../core/Shader.hpp"
#include "../core/Mesh.hpp"
#include "../core/Texture.hpp"

class Environment final
{
public:
	Environment();

	void Prepare() const;
	void Draw(const std::shared_ptr<Shader>& background_shader) const;

private:
	void CreateBuffers();
	void CreateCube();
	void CreateQuad();

	void RenderCubeMap(const glm::mat4& capture_projection, const glm::mat4 capture_views[6]) const;
	void RenderIrradianceMap(const glm::mat4& capture_projection, const glm::mat4 capture_views[6]) const;
	void RenderPrefilterMap(const glm::mat4& capture_projection, const glm::mat4 capture_views[6]) const;
	void RenderBrdfLut() const;

	unsigned fbo_;
	unsigned rbo_;

	std::unique_ptr<Mesh> cube_ = nullptr;
	std::unique_ptr<Mesh> quad_ = nullptr;

	std::shared_ptr<Texture> hdr_texture_ = nullptr;
	std::shared_ptr<Texture> cube_map_ = nullptr;
	std::shared_ptr<Texture> irradiance_map_ = nullptr;
	std::shared_ptr<Texture> prefilter_map_ = nullptr;
	std::shared_ptr<Texture> brdf_lut_ = nullptr;

	std::unique_ptr<Shader> cube_map_shader_ = nullptr;
	std::unique_ptr<Shader> brdf_shader_ = nullptr;
	std::unique_ptr<Shader> irradiance_shader_ = nullptr;
	std::unique_ptr<Shader> prefilter_shader_ = nullptr;
};
