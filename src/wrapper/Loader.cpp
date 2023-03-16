#include "stdafx.h"
#include "Loader.hpp"

#include <stb_image.h>

glm::vec3 MapArrayToVec3(const float array[3])
{
	return {array[0], array[1], array[2]};
}

void Loader::LoadModel(const std::string& path, std::vector<std::shared_ptr<Mesh>>& meshes, std::vector<std::shared_ptr<Material>>& materials)
{
		tinyobj::ObjReaderConfig reader_config;
		reader_config.vertex_color = false;
		reader_config.triangulation_method = "earcut";
		reader_config.mtl_search_path = "assets/mtl";

		const auto model_path = std::filesystem::current_path() / "assets/obj" / path;

		tinyobj::ObjReader reader;

		if (!reader.ParseFromFile(model_path.string(), reader_config))
			[[unlikely]] throw std::exception(std::string("Failed to load model" + path).c_str());

		auto& temp_materials = reader.GetMaterials();
		auto& temp_attrib = reader.GetAttrib();
		auto& temp_shapes = reader.GetShapes();

		meshes.clear();
		materials.clear();

		LoadMaterials(materials, temp_materials);
		LoadMeshes(meshes, temp_shapes, temp_attrib);
}

void Loader::LoadImage(const std::string& path, unsigned char*& image_data, int& width, int& height, int& channels)
{
	const auto texture_path = std::filesystem::current_path() / "assets/mtl" / path;

	if (!stbi_info(texture_path.string().c_str(), &width, &height, &channels))
		[[unlikely]] throw std::exception(std::string(path + " is not a valid image file").c_str());

	image_data = stbi_load(texture_path.string().c_str(), &width, &height, &channels, 0);
}

void Loader::LoadMaterials(std::vector<std::shared_ptr<Material>>& materials, const std::vector<tinyobj::material_t>& temp_materials)
{
	for (const auto& material : temp_materials)
	{
		auto diffuse = !material.diffuse_texname.empty() ? std::make_unique<Texture>(material.diffuse_texname) : nullptr;
		auto roughness = !material.roughness_texname.empty() ? std::make_unique<Texture>(material.roughness_texname) : nullptr;
		auto normal = !material.normal_texname.empty() ? std::make_unique<Texture>(material.normal_texname) : nullptr;

		materials.push_back(std::make_shared<Material>(
			material.metallic,
			material.roughness,
			MapArrayToVec3(material.diffuse),
			std::move(diffuse),
			std::move(roughness),
			std::move(normal)));
	}
}

void Loader::LoadMeshes(std::vector<std::shared_ptr<Mesh>>& meshes, const std::vector<tinyobj::shape_t>& temp_shapes, const tinyobj::attrib_t& temp_attrib)
{
	std::unordered_map<Vertex, uint32_t> unique_vertices;
    for (const auto& shape : temp_shapes)
    {
		std::vector<Vertex> vertices{};
		std::vector<unsigned> indices{};

        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
	        for (size_t v = 0; v < 3; v++)
	        {
				Vertex vertex{};
				const auto index = shape.mesh.indices[index_offset + v];

				vertex.position =
                {
                    temp_attrib.vertices[3 * index.vertex_index + 0],
                    temp_attrib.vertices[3 * index.vertex_index + 1],
                    temp_attrib.vertices[3 * index.vertex_index + 2],
                };

				if (index.normal_index >= 0)
	            {
	                vertex.normal =
	                {
	                    temp_attrib.normals[3 * index.normal_index + 0],
	                    temp_attrib.normals[3 * index.normal_index + 1],
	                    temp_attrib.normals[3 * index.normal_index + 2],
	                };
	            }

	            if (index.texcoord_index >= 0)
	            {
	                vertex.uv =
	                {
	                    temp_attrib.texcoords[2 * index.texcoord_index + 0],
	                    temp_attrib.texcoords[2 * index.texcoord_index + 1],
	                };
	            }

				if (!unique_vertices.contains(vertex))
	            {
	                unique_vertices[vertex] = static_cast<unsigned>(vertices.size());
	                vertices.push_back(vertex);
	            }
	            indices.push_back(unique_vertices[vertex]);
	        }
	        index_offset += 3;
        }

		meshes.push_back(std::make_shared<Mesh>(vertices, indices, shape.mesh.material_ids[0]));
	}
}
