#pragma once
#include "Vertex.hpp"

class Mesh
{
public:
	explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices = {}, int material_id = 0);
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh& operator= (const Mesh&) = delete;
	Mesh& operator= (Mesh&&) = delete;

	void Bind() const;
	void Unbind() const;
	void Draw() const;
	void Clear() const;
	[[nodiscard]] int GetMaterialId() const { return material_id_; }

private:
	unsigned vao_;
	unsigned ebo_;
	unsigned vbo_;
	size_t vertex_count_;
	size_t index_count_;
	int material_id_;
};
