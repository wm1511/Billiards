#include "stdafx.h"
#include "CubeMap.hpp"

CubeMap::CubeMap() : frame_buffer_{}
{
	std::vector vertices
	{
		Vertex(glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-1.0f, 0.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, -1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-1.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, -1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-1.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, -1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-1.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-1.0f, 0.0f, 0.0f}),
		Vertex(glm::vec3{-1.0f, 1.0f, -1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-1.0f, 0.0f, 1.0f}),

		Vertex(glm::vec3{-1.0f, -1.0f, 1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, 1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{-1.0f, 1.0f, 1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{-1.0f, -1.0f, 1.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}),

		Vertex(glm::vec3{-1.0f, 1.0f, 1.0f}, glm::vec2{-1.0f, 0.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{-1.0f, 1.0f, -1.0f}, glm::vec2{-1.0f, 0.0f}, glm::vec3{ 0.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec2{-1.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec2{-1.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{-1.0f, -1.0f, 1.0f}, glm::vec2{-1.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f}),
		Vertex(glm::vec3{-1.0f, 1.0f, 1.0f}, glm::vec2{-1.0f, 0.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}),

		Vertex(glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{1.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, -1.0f}, glm::vec2{1.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, -1.0f}, glm::vec2{1.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, -1.0f}, glm::vec2{1.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{1.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, 1.0f}, glm::vec2{1.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}),

		Vertex(glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec2{0.0f, -1.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, -1.0f}, glm::vec2{0.0f, -1.0f}, glm::vec3{ 0.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, 1.0f}, glm::vec2{0.0f, -1.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, -1.0f, 1.0f}, glm::vec2{0.0f, -1.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{-1.0f, -1.0f, 1.0f}, glm::vec2{0.0f, -1.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f}),
		Vertex(glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec2{0.0f, -1.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f}),

		Vertex(glm::vec3{-1.0f, 1.0f, -1.0f}, glm::vec2{ 0.0f, 1.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{ 0.0f, 1.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, -1.0f}, glm::vec2{ 0.0f, 1.0f}, glm::vec3{ 0.0f, 1.0f, 1.0f}),
		Vertex(glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{ 0.0f, 1.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f}),
		Vertex(glm::vec3{-1.0f, 1.0f, -1.0f}, glm::vec2{ 0.0f, 1.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f}),
		Vertex(glm::vec3{-1.0f, 1.0f, 1.0f}, glm::vec2{ 0.0f, 1.0f}, glm::vec3{ 0.0f, 0.0f, 0.0f})
	};

	meshes_.emplace_back(std::make_shared<Mesh>(std::move(vertices)));
	materials_.emplace_back(std::make_shared<Material>(glm::vec3{0.0f}, glm::vec3{0.0f}, 0.0f, 0.0f, std::make_unique<Texture>(frame_buffer_)));
}

void CubeMap::Draw(const std::shared_ptr<Shader>& shader, const unsigned type) const
{
	glDisable(GL_CULL_FACE);
	shader->Bind();
	shader->SetBool(true, "reverse_normals");
	Object::Draw(shader);
	shader->SetBool(false, "reverse_normals");
	shader->Unbind();
    glEnable(GL_CULL_FACE);
}

void CubeMap::BindBuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
}

void CubeMap::UnbindBuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
