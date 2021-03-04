#include <image.hpp>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

DImage::~DImage() 
{
	if(pixels != nullptr) stbi_image_free(pixels);
	if(m_texture != -1) glDeleteTextures(1, &m_texture);
}

DImage::DImage() 
{
	pixels = new unsigned char[0];
}

DImage::DImage(unsigned char* _pixels, GLuint _texture, int w, int h, int c)
{
	pixels = _pixels;
	m_texture = _texture;
	width = w;
	height = h;
	channels = c;
}

DImage::DImage(const DImage& other) 
{
	height = other.height;
	width = other.width;
	channels = other.channels;

	if(other.pixels != nullptr) 
	{
		pixels = new unsigned char[other.width * other.height * other.channels];
		std::copy(other.pixels, other.pixels + other.width * other.height * other.channels, pixels);
	}

	glDeleteTextures(1, &m_texture);
	m_texture = generateTexture(width, height, pixels);
}

DImage::DImage(DImage&& other)
{
	pixels = other.pixels;
	m_texture = other.m_texture;
	height = other.height;
	width = other.width;
	channels = other.channels;

	other.pixels = nullptr;
	other.m_texture = -1;
	other.height = 0;
	other.width = 0;
	other.channels = 0;
}

DImage& DImage::operator=(DImage& other) 
{
	if(this != &other) 
	{
		height = other.height;
		width = other.width;
		channels = other.channels;

		delete[] pixels; // Remove old pixels and copy new ones
		if(other.pixels != nullptr) 
		{
			pixels = new unsigned char[other.width * other.height * other.channels];
			std::copy(other.pixels, other.pixels + other.width * other.height * other.channels, pixels);
		}

		glDeleteTextures(1, &m_texture);
		m_texture = generateTexture(width, height, pixels);
	}

	return *this;
}

DImage& DImage::operator=(DImage&& other) 
{
	if(this != &other) 
	{
		delete[] pixels;

		pixels = other.pixels;
		m_texture = other.m_texture;
		height = other.height;
		width = other.width;
		channels = other.channels;

		other.pixels = nullptr;
		other.m_texture = -1;
		other.height = 0;
		other.width = 0;
		other.channels = 0;
	}

	return *this;
}

void DImage::bind(unsigned int unit) const
{
    //TODO:
    //unit max count is obtained from glGet using GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
    //change this accordingly, and don't call glGet every time image is bound
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

DImage DImage::loadImage(const std::string& fileName) 
{
	stbi_set_flip_vertically_on_load(1);

	int width, height, channels;
	unsigned char* pixels = stbi_load(fileName.c_str(), &width, &height, &channels, 4);
	if(pixels == NULL)
		dbg::error(("Image data not found: " + fileName).c_str());

	GLuint m_texture = generateTexture(width, height, pixels);

	DImage tmpImg(pixels, m_texture, width, height, channels);

	return tmpImg;
}

GLuint DImage::generateTexture(int width, int height, unsigned char* pixels)
{
	GLuint m_texture;
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	return m_texture;
}