#pragma once
#include "Vertex.hpp"

class VertexIndexBuffer
{
public:
	VertexIndexBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices);
	~VertexIndexBuffer();
	void Bind() const;
	void Unbind() const;
	void Draw() const;
	void Clear() const;

private:
	unsigned vao_;
	unsigned ebo_;
	unsigned vbo_;
	size_t vertex_count_;
	size_t index_count_;
};