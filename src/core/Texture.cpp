#include "stdafx.h"
#include "Texture.hpp"

Texture::Texture(unsigned char* image_data, const int width, const int height, const int channels) :
	texture_{}, type_{GL_TEXTURE_2D}
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

	glTexImage2D(GL_TEXTURE_2D, 0, image_type, width, height, 0, image_type, GL_UNSIGNED_BYTE, reinterpret_cast<void*>(image_data));
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(const int size, const bool mipmap) :
	texture_{}, type_{GL_TEXTURE_CUBE_MAP}
{
	const unsigned filter = mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;

	glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);

    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, size, size, 0, GL_RGB, GL_FLOAT, nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(float* image_data, const int width, const int height) :
	texture_{}, type_(GL_TEXTURE_2D)
{
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image_data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, reinterpret_cast<void*>(image_data));
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, width, height, 0, GL_RG, GL_FLOAT, nullptr);
}

void Texture::Bind() const
{
	glBindTexture(type_, texture_);
}

//void Texture::Unbind() const
//{
//	glBindTexture(type_, 0);
//}
