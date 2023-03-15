#pragma once
#include "Vertex.hpp"

class Loader
{
public:
	static void LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<unsigned>& indices);
	static void LoadImage(const std::string& path, unsigned char*& image_data, int& width, int& height, int& channels);
};
