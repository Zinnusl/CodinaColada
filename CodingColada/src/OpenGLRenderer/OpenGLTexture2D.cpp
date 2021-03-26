#include "OpenGLTexture2D.h"

#include <glad/glad.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


OpenGLTexture2D::OpenGLTexture2D()
	: width_(0), height_(0), internal_format_(GL_RGB), image_format_(GL_RGB), wrap_s_(GL_REPEAT), wrap_t_(GL_REPEAT), filter_min_(GL_LINEAR), filter_max_(GL_LINEAR)
{
	glGenTextures(1, &this->id_);
}

void OpenGLTexture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->width_ = width;
	this->height_ = height;
	// create Texture
	glBindTexture(GL_TEXTURE_2D, this->id_);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format_, width, height, 0, this->image_format_, GL_UNSIGNED_BYTE, data);
	// set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max_);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id_);
}

OpenGLTexture2D OpenGLTexture2D::LoadTextureFromFile(const char* file, bool alpha)
{
	// create texture object
	OpenGLTexture2D texture;
	if (alpha)
	{
		texture.internal_format_ = GL_RGBA;
		texture.image_format_ = GL_RGBA;
	}
	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	// now generate texture
	texture.Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	return texture;
}