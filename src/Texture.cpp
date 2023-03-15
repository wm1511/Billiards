#include "stdafx.h"
#include "Texture.hpp"

#include "Loader.hpp"

Texture::Texture(const std::string& path) : texture_{}
{
	unsigned char* image_data;
	int channels;

	Loader::LoadImage(path, image_data, width_, height_, channels);

	const int image_type = channels == 4 ? GL_RGBA : GL_RGB;

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, image_type, width_, height_, 0, image_type, GL_UNSIGNED_BYTE, reinterpret_cast<void*>(image_data));
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		[[unlikely]] throw std::exception("Failed to load texture");

	free(image_data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, texture_);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
