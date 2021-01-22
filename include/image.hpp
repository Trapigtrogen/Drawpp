#ifndef DPP_IMAGE_H
#define DPP_IMAGE_H

#include <glad/glad.h>

#include <string>
#include <debug.hpp>

class DImage
{
public:
	DImage();
	virtual ~DImage();

	void operator=(const DImage&& other);

	static DImage loadImage(const std::string& fileName);
	void image(DImage image, int x, int y);

	void bind(unsigned int unit);

	unsigned char* pixels;
	unsigned int width, height;

private:
	GLuint m_texture;
	DImage(const DImage&& other);
};

#endif