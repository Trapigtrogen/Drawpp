#include <image.hpp>
#include <debug.hpp>
#include <cassert>
#include <glad/glad.h>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#else
#pragma warning(push,1)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#else
#pragma warning(pop)
#endif

unsigned int get_max_units()
{
    int value;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&value);
    return value;
}

DImage::~DImage() 
{
	if(pixels != nullptr) free(pixels);
	if(m_texture != 0) glDeleteTextures(1, &m_texture);
}

DImage::DImage()
{
    max_texture_units = get_max_units();
}

DImage::DImage(unsigned char* _pixels, unsigned int _texture, int w, int h, int c)
{
    max_texture_units = get_max_units();
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
		pixels = (unsigned char*) malloc(other.width * other.height * other.channels);
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
	other.m_texture = 0;
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

		free(pixels); // Remove old pixels and copy new ones
        pixels = nullptr;
		if(other.pixels != nullptr) 
		{
			pixels = (unsigned char*) malloc(other.width * other.height * other.channels);
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
		free(pixels);

		pixels = other.pixels;
		m_texture = other.m_texture;
		height = other.height;
		width = other.width;
		channels = other.channels;

		other.pixels = nullptr;
		other.m_texture = 0;
		other.height = 0;
		other.width = 0;
		other.channels = 0;
	}

	return *this;
}

void DImage::bind(unsigned int unit) const
{
	assert(unit < max_texture_units);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

DImage DImage::loadImage(const std::string& fileName) 
{
	stbi_set_flip_vertically_on_load(1);

	int width, height, channels;
	unsigned char* pixels = stbi_load(fileName.c_str(), &width, &height, &channels, 4);
    channels = 4;
	if(pixels == NULL)
		dbg::error(("Image data not found: " + fileName).c_str());

	GLuint m_texture = generateTexture(width, height, pixels);

	DImage tmpImg(pixels, m_texture, width, height, channels);

	return tmpImg;
}


unsigned int DImage::generateTexture(int width, int height, unsigned char* pixels)
{
	unsigned int m_texture;
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	return m_texture;
}

unsigned int DImage::max_texture_units = 0;