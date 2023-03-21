#include "stdafx.h"
#include "Loader.hpp"

#include <stb_image.h>

void Loader::LoadModel(const std::string& path, std::vector<std::shared_ptr<Mesh>>& meshes, std::vector<std::shared_ptr<Material>>& materials)
{
	tinyobj::ObjReaderConfig reader_config;
	reader_config.vertex_color = false;
	reader_config.triangulation_method = "earcut";

	const auto model_path = std::filesystem::current_path() / "assets/models" / path;

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(model_path.string(), reader_config))
		[[unlikely]] throw std::exception(std::string("Failed to load model " + path).c_str());

	auto& temp_materials = reader.GetMaterials();
	auto& temp_attrib = reader.GetAttrib();
	auto& temp_shapes = reader.GetShapes();

	meshes.clear();
	materials.clear();

	LoadMaterials(materials, temp_materials);
	LoadMeshes(meshes, temp_shapes, temp_attrib);
}

std::shared_ptr<Texture> Loader::LoadTexture(const std::string& path)
{
	if (path.empty())
		return nullptr;
	
	if (unique_textures_.contains(path))
		return unique_textures_[path];

	unsigned char* image_data;
	int channels, width, height;

	LoadImage(path, image_data, width, height, channels);

	const auto texture = std::make_shared<Texture>(image_data, width, height, channels);
	unique_textures_.insert({ path, texture });
	return texture;
}

void Loader::LoadMaterials(std::vector<std::shared_ptr<Material>>& materials, const std::vector<tinyobj::material_t>& temp_materials)
{
	for (const auto& material : temp_materials)
	{
		materials.push_back(std::make_shared<Material>
		(
			material.metallic,
			material.roughness,
			glm::vec3{material.diffuse[0], material.diffuse[1], material.diffuse[2]},
			LoadTexture(material.diffuse_texname),
			LoadTexture(material.roughness_texname),
			LoadTexture(material.normal_texname)
		));
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

void Loader::LoadImage(const std::string& path, unsigned char*& image_data, int& width, int& height, int& channels)
{
	const auto image_path = std::filesystem::current_path() / "assets/textures" / path;

	if (!stbi_info(image_path.string().c_str(), &width, &height, &channels))
		[[unlikely]] throw std::exception(std::string(path + " is not a valid image file").c_str());

	image_data = stbi_load(image_path.string().c_str(), &width, &height, &channels, 0);
}

void Loader::LoadHdr(const std::string& path, float*& hdr_data, int& width, int& height)
{
	int channels{};
	const auto image_path = std::filesystem::current_path() / "assets/hdr" / path;

	if (!stbi_info(image_path.string().c_str(), &width, &height, &channels))
		[[unlikely]] throw std::exception(std::string(path + " is not a valid HDR file").c_str());

	hdr_data = stbi_loadf(image_path.string().c_str(), &width, &height, &channels, 3);
}
