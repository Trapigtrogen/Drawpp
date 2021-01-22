#include <image.hpp>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

DImage::~DImage() 
{
	printf("destructor\n");
	//delete pixels;
	//glDeleteTextures(1, &m_texture);
}

DImage::DImage()
{
	printf("constructor\n");
	pixels = new unsigned char;
}

DImage::DImage(const DImage&& other):pixels(other.pixels), m_texture(other.m_texture)
{
	printf("move constructor\n");
}

void DImage::operator=(const DImage&& other)
{
	this->pixels = other.pixels;
	this->m_texture = other.m_texture;
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	DImage tmpImage;
	tmpImage.pixels = pixels;
	tmpImage.m_texture = m_texture;

	stbi_image_free(pixels);

	return tmpImage;
}

void image(DImage image, int x, int y)
{
	//bind(0);
	// Debug todo: Draw image
}