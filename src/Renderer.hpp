#pragma once
#include "Shader.hpp"
#include "VertexIndexBuffer.hpp"
#include "Camera.hpp"

#include <memory>

class Renderer
{
public:
	static void Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexIndexBuffer>& model);
	static void Update(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Camera>& camera);
};
