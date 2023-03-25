#pragma once

class Texture
{
public:
	Texture(int size, bool mipmap);
	Texture(unsigned char* image_data, int width, int height, int channels);
	Texture(float* image_data, int width, int height);
	~Texture() = default;

	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator= (const Texture&) = delete;
	Texture& operator= (Texture&&) = delete;

	void Bind() const;
	[[nodiscard]] int GetId() const { return static_cast<int>(texture_); }

private:
	unsigned texture_;
	int type_;
};
