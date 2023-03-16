#pragma once
#include "Material.hpp"
#include "Mesh.hpp"

#include <tiny_obj_loader.h>

class Loader
{
public:
	static void LoadModel(const std::string& path, std::vector<std::shared_ptr<Mesh>>& meshes, std::vector<std::shared_ptr<Material>>& materials);
	static void LoadImage(const std::string& path, unsigned char*& image_data, int& width, int& height, int& channels);

private:
	static void LoadMaterials(std::vector<std::shared_ptr<Material>>& materials, const std::vector<tinyobj::material_t>& temp_materials);
	static void LoadMeshes(std::vector<std::shared_ptr<Mesh>>& meshes, const std::vector<tinyobj::shape_t>& temp_shapes, const tinyobj::attrib_t& temp_attrib);
};
