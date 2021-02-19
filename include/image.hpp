#ifndef DPP_IMAGE_H
#define DPP_IMAGE_H

#include <glad/glad.h>

#include <string>
#include <debug.hpp>

///  DImage is an object that textures can be loaded to from image or pixel set
class DImage
{
public:
	DImage();
	~DImage();

	DImage(const DImage&);
	DImage(DImage&& other);

	DImage& operator=(DImage& other);
	DImage& operator=(DImage&& other);

	enum ImgMode
	{
		CORNER,	// Attach from top-left corner
		CORNERS, // Draw to given corners
		CENTER // Attach to center
	};

	static DImage loadImage(const std::string& fileName);

	void imageMode(ImgMode mode);

	void drawImage(int x, int y, unsigned int w, unsigned int h);

	void background(DImage* image);

	void bind(unsigned int unit);

	unsigned char* pixels = nullptr;
	int width = 0;
	int height = 0;
	int channels = 0;

private:
	GLuint m_texture = 0;
	DImage(unsigned char* _pixels, GLuint _texture, int w, int h, int c);
	static GLuint generateTexture(int w, int h, unsigned char* pixels);
};

#endif