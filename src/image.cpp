#include <image.hpp>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

DImage::~DImage() 
{
	stbi_image_free(pixels);
	if(m_texture != -1) glDeleteTextures(1, &m_texture);
}

DImage::DImage()
{
	pixels = new unsigned char[0];
}

DImage::DImage(unsigned char* _pixels, GLuint _texture)
{
	pixels = _pixels;
	m_texture = _texture;
}

DImage::DImage(const DImage& other)
{
	pixels = new unsigned char[other.width*other.height];
	std::copy(other.pixels, other.pixels + other.width*other.height, pixels);
	m_texture = other.m_texture;
	height = other.height;
	width = other.width;
}

DImage::DImage(DImage&& other)
{
	pixels = other.pixels;
	m_texture = other.m_texture;
	height = other.height;
	width = other.width;

	other.pixels = nullptr;
	other.m_texture = -1;
	other.height = 0;
	other.width = 0;
}

DImage& DImage::operator=(DImage& other)
{
	if(this != &other) 
	{
		delete[] pixels;

		pixels = other.pixels;
		m_texture = other.m_texture;
		height = other.height;
		width = other.width;
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

		other.pixels = nullptr;
		other.m_texture = -1;
		other.height = 0;
		other.width = 0;
	}

	return *this;
}

void DImage::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

DImage DImage::loadImage(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* pixels = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
	if(pixels == NULL) 
		dbg::error(("Image data not found: " + fileName).c_str());

	GLuint m_texture;
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	stbi_set_flip_vertically_on_load(1);

	return DImage(pixels, m_texture);

}

void DImage::drawImage(int x, int y, unsigned int w, unsigned int h) {
	bind(m_texture-1);
	// Debug todo: Draw image
}

void DImage::background(DImage* image) 
{

}

void DImage::imageMode(ImgMode mode)
{

}