#ifndef DPP_IMAGE_H
#define DPP_IMAGE_H

#include <glad/glad.h>

#include <string>
#include <debug.hpp>

class DImage
{
public:
	DImage();
	DImage(const DImage& other);
	DImage(DImage&& other);
	~DImage();

	DImage& operator=(DImage&& other);

	enum ImageMode 
	{
		CORNER,	// Attach from top-left corner
		CORNERS, // Draw to given corners
		CENTER // Attach to center
	};

	static DImage loadImage(const std::string& fileName);

	void imageMode(ImageMode mode);

	void drawImage(int x, int y, unsigned int w, unsigned int h);

	void background(DImage* image);

	void bind(unsigned int unit);

	unsigned char* pixels = nullptr;
	unsigned int width = 0;
	unsigned int height = 0;

private:
	GLuint m_texture = 0;
	DImage(unsigned char* _pixels, GLuint _texture);
};

#endif