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

	int channels, width, height;
	const auto image_path = std::filesystem::current_path() / "assets/textures" / path;

	if (!stbi_info(image_path.string().c_str(), &width, &height, &channels))
		[[unlikely]] throw std::exception(std::string(path + " cannot be found or loaded as an image").c_str());

	unsigned char* image_data = stbi_load(image_path.string().c_str(), &width, &height, &channels, 0);

	const auto texture = std::make_shared<Texture>(image_data, width, height, channels);

	stbi_image_free(image_data);

	unique_textures_.insert({ path, texture });
	return texture;
}

std::shared_ptr<Texture> Loader::LoadEnvironment(const std::string& path)
{
	int channels, width, height;
	const auto image_path = std::filesystem::current_path() / "assets/hdr" / path;

	stbi_set_flip_vertically_on_load(true);

	if (!stbi_info(image_path.string().c_str(), &width, &height, &channels))
		[[unlikely]] throw std::exception(std::string(path + " cannot be found or loaded as an HDR image").c_str());

	float* hdr_data = stbi_loadf(image_path.string().c_str(), &width, &height, &channels, 3);

	stbi_set_flip_vertically_on_load(false);

	const auto texture = std::make_shared<Texture>(hdr_data, width, height);

	stbi_image_free(hdr_data);

	return texture;
}

void Loader::LoadMaterials(std::vector<std::shared_ptr<Material>>& materials, const std::vector<tinyobj::material_t>& temp_materials)
{
	for (const auto& material : temp_materials)
	{
		materials.push_back(std::make_shared<Material>
			(
				glm::vec3{ material.diffuse[0], material.diffuse[1], material.diffuse[2] },
				glm::vec3{ material.ambient[0], material.ambient[1], material.ambient[2] },
				material.roughness,
				material.metallic,
				LoadTexture(material.diffuse_texname),
				LoadTexture(material.ambient_texname),
				LoadTexture(material.roughness_texname),
				LoadTexture(material.metallic_texname),
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
