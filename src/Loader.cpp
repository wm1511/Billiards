#include "stdafx.h"
#include "Loader.hpp"

#include <tiny_obj_loader.h>
#include <stb_image.h>

void Loader::LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
		tinyobj::ObjReaderConfig reader_config;
		reader_config.vertex_color = false;
		reader_config.triangulation_method = "earcut";
		reader_config.mtl_search_path = "assets/mtl";

		const auto model_path = std::filesystem::current_path() / "assets/obj" / path;

		tinyobj::ObjReader reader;

		if (!reader.ParseFromFile(model_path.string(), reader_config))
			[[unlikely]] throw std::exception(std::string("Failed to load model" + path).c_str());
		
		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();

		vertices.clear();
	    indices.clear();

	    std::unordered_map<Vertex, uint32_t> unique_vertices;
	    for (const auto& shape : shapes)
	    {  
	        for (const auto& index : shape.mesh.indices)
	        {
	            Vertex vertex{};

	            if (index.vertex_index >= 0)
	            {
	                vertex.position =
	                {
	                    attrib.vertices[3 * index.vertex_index + 0],
	                    attrib.vertices[3 * index.vertex_index + 1],
	                    attrib.vertices[3 * index.vertex_index + 2],
	                };
	            }

	            if (index.normal_index >= 0)
	            {
	                vertex.normal =
	                {
	                    attrib.normals[3 * index.normal_index + 0],
	                    attrib.normals[3 * index.normal_index + 1],
	                    attrib.normals[3 * index.normal_index + 2],
	                };
	            }

	            if (index.texcoord_index >= 0)
	            {
	                vertex.uv =
	                {
	                    attrib.texcoords[2 * index.texcoord_index + 0],
	                    attrib.texcoords[2 * index.texcoord_index + 1],
	                };
	            }

	            if (!unique_vertices.contains(vertex))
	            {
	                unique_vertices[vertex] = static_cast<unsigned>(vertices.size());
	                vertices.push_back(vertex);
	            }
	            indices.push_back(unique_vertices[vertex]);
	        }
	    }
	}

void Loader::LoadImage(const std::string& path, unsigned char*& image_data, int& width, int& height, int& channels)
{
	const auto texture_path = std::filesystem::current_path() / "assets/mtl" / path;

	if (!stbi_info(texture_path.string().c_str(), &width, &height, &channels))
		[[unlikely]] throw std::exception(std::string(path + " is not a valid image file").c_str());

	image_data = stbi_load(texture_path.string().c_str(), &width, &height, &channels, 0);
}