#include "stdafx.h"
#include "VertexIndexBuffer.hpp"

VertexIndexBuffer::VertexIndexBuffer(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) :
	vao_{},
	ebo_{},
	vbo_{},
	vertex_count_(vertices.size()),
	index_count_(indices.size())
{
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertex_count_ * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	if (index_count_ > 0)
	{
		glGenBuffers(1, &ebo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count_ * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

VertexIndexBuffer::~VertexIndexBuffer()
{
	Clear();
}

void VertexIndexBuffer::Bind() const
{
    glBindVertexArray(vao_);
}

void VertexIndexBuffer::Unbind() const
{
    glBindVertexArray(0);
}

void VertexIndexBuffer::Draw() const
{
	if (index_count_ == 0)
		glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertex_count_));
	else
		glDrawElements(GL_TRIANGLES, static_cast<int>(index_count_), GL_UNSIGNED_INT, nullptr);
}

void VertexIndexBuffer::Clear() const
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &ebo_);
}