#pragma once
#include "Material.hpp"
#include "Mesh.hpp"

class Object
{
public:
	void Bind() const;
	void Unbind() const;
	void Draw() const;
	std::shared_ptr<Material> GetMaterial();

protected:
	std::vector<std::shared_ptr<Material>> materials_{};
	std::shared_ptr<Mesh> mesh_ = nullptr;
};
