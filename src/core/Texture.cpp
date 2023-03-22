#include "stdafx.h"
#include "Texture.hpp"

#include "Loader.hpp"

Texture::Texture(unsigned char* image_data, const int width, const int height, const int channels) : texture_{}
{
	int image_type;

	if (channels == 1)
		image_type = GL_RED;
	else if (channels == 2)
		image_type = GL_RG;
	else if (channels == 3)
		image_type = GL_RGB;
	else if (channels == 4)
		image_type = GL_RGBA;
	else
		throw std::exception("Invalid image channel count");

	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, image_type, width, height, 0, image_type, GL_UNSIGNED_BYTE, reinterpret_cast<void*>(image_data));
		glGenerateMipmap(GL_TEXTURE_2D);

		free(image_data);
	}
	else
		[[unlikely]] throw std::exception("Failed to create texture");

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(float* hdr_data, const int width, const int height) : texture_{}
{
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (hdr_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, reinterpret_cast<void*>(hdr_data));

		free(hdr_data);
	}
	else
		[[unlikely]] throw std::exception("Failed to create HDR map");

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
