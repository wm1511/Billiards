#pragma once

class Mesh
{
public:
	explicit Mesh(const std::string& path);
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh& operator= (const Mesh&) = delete;
	Mesh& operator= (Mesh&&) = delete;

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