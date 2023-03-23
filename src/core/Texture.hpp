#pragma once

class Texture
{
public:
	explicit Texture(unsigned& frame_buffer);
	Texture(unsigned char* image_data, int width, int height, int channels, bool stbi_imported = true);
	Texture(float* hdr_data, int width, int height);
	~Texture() = default;

	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator= (const Texture&) = delete;
	Texture& operator= (Texture&&) = delete;

	void Bind(unsigned type = GL_TEXTURE_2D) const;
	void Unbind() const;
	[[nodiscard]] int GetId() const { return static_cast<int>(texture_); }

private:
	unsigned texture_;
};
