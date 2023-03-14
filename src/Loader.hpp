#pragma once
#include "Vertex.hpp"

class Loader
{
public:
	static void Load(const std::string& path, std::vector<Vertex>& vertices, std::vector<unsigned>& indices);
};
