#pragma once
#include <glm/gtx/hash.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	int material_id;

	bool operator==(const Vertex& other) const
	{
		return position == other.position
			&& normal == other.normal
			&& uv == other.uv;
	}
};

template<>
struct std::hash<Vertex>
{
	size_t operator()(const Vertex& v) const noexcept
	{
		return std::hash<glm::vec3>()(v.position)
			^ std::hash<glm::vec3>()(v.normal)
			^ std::hash<glm::vec2>()(v.uv);
	}
};
