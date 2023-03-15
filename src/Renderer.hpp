#pragma once
#include "Shader.hpp"
#include "Object.hpp"
#include "Camera.hpp"

class Renderer
{
public:
	static void Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Object>& object);
	static void Update(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Camera>& camera);
	static void Update(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Object>& object);
};
