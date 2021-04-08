#include <image.hpp>
#include <debug.hpp>
#include <cassert>
#include <glad/glad.h>
#include <cstring>

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

#include <nanosvg.h>
#define NANOSVGRAST_IMPLEMENTATION
#include <nanosvgrast.h>

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#else
#pragma warning(pop)
#endif

unsigned int get_max_units()
{
    int value = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&value);
    return value;
}

DImage::~DImage() 
{
	if(m_pixels != nullptr) free(m_pixels);
	if(m_texture != 0) glDeleteTextures(1, &m_texture);
}

DImage::DImage() = default;

DImage::DImage(unsigned char* _pixels, unsigned int _texture, int w, int h, int c)
{
	m_pixels = _pixels;
    max_texture_units = get_max_units();
	m_texture = _texture;
	m_width = w;
	m_height = h;
	m_channels = c;
}

DImage::DImage(const DImage& other) 
{
	m_height = other.m_height;
	m_width = other.m_width;
	m_channels = other.m_channels;

	if(other.m_pixels != nullptr) 
	{
        unsigned size = other.m_width * other.m_height * other.m_channels;
		m_pixels = static_cast<unsigned char*>(malloc(size));
        std::memcpy(m_pixels,other.m_pixels,size);
	}

	apply();
}

DImage::DImage(DImage&& other)
{
	m_pixels = other.m_pixels;
	m_texture = other.m_texture;
	m_height = other.m_height;
	m_width = other.m_width;
	m_channels = other.m_channels;

	other.m_pixels = nullptr;
	other.m_texture = 0;
	other.m_height = 0;
	other.m_width = 0;
	other.m_channels = 0;
}

DImage& DImage::operator=(const DImage& other) 
{
	if(this != &other) 
	{
		m_height = other.m_height;
		m_width = other.m_width;
		m_channels = other.m_channels;

		free(m_pixels); // Remove old pixels and copy new ones
        m_pixels = nullptr;

		if(other.m_pixels != nullptr) 
		{
            unsigned size = other.m_width * other.m_height * other.m_channels;
			m_pixels = static_cast<unsigned char*>(malloc(size));
            std::memcpy(m_pixels,other.m_pixels,size);
		}

		apply();
	}

	return *this;
}

DImage& DImage::operator=(DImage&& other) 
{
	if(this != &other) 
	{
		free(m_pixels);

		m_pixels = other.m_pixels;
		m_texture = other.m_texture;
		m_height = other.m_height;
		m_width = other.m_width;
		m_channels = other.m_channels;

		other.m_pixels = nullptr;
		other.m_texture = 0;
		other.m_height = 0;
		other.m_width = 0;
		other.m_channels = 0;
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

DImage DImage::loadSVGImage(const std::string& filename, float scale)
{
    NSVGimage* image = nsvgParseFromFile(filename.c_str(), "px", 96);

    if(image == nullptr) 
	{
        dbg::error("Failed to load svg image: ", filename);
        return DImage();
    }

    NSVGrasterizer* raster = nsvgCreateRasterizer();

    int width = (image->width*scale);
    int height = (image->height*scale);
    unsigned int w4 = width*4;

    unsigned char* imgdata = static_cast<unsigned char*>(malloc(w4*height));

    nsvgRasterize(raster,image,0,0,scale,imgdata,width,height,w4);

    //rasterizer creates upside down image for some reason, so flip pixels here
    unsigned char* tmp = static_cast<unsigned char*>(malloc(w4));
    unsigned char* last_line = imgdata + (height-1)*w4;
    for(unsigned i = 0; i < height/2; ++i)
    {
        unsigned char* upper = imgdata+i*w4;
        unsigned char* lower = last_line-i*w4;
        std::memcpy(tmp,upper,w4);
        std::memcpy(upper,lower,w4);
        std::memcpy(lower,tmp,w4);
    }
    free(tmp);

    GLuint texture = generateTexture(width,height,imgdata);

    nsvgDelete(image);
    nsvgDeleteRasterizer(raster);

    return DImage(imgdata,texture,width,height,4);
}

unsigned int DImage::generateTexture(int width, int height, unsigned char* pixels)
{
	unsigned int m_texture;
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	return m_texture;
}

int DImage::width() const
{
    return m_width;
}

int DImage::height() const
{
    return m_height;
}

int DImage::channels() const
{
    return m_channels;
}

unsigned char* DImage::pixels()
{
    return m_pixels;
}

const unsigned char* DImage::pixels() const
{
    return m_pixels;
}

void DImage::apply()
{
	if(m_texture != 0)
    {
        glDeleteTextures(1, &m_texture);
        m_texture = 0;
    }

    if(m_pixels != nullptr)
    {
        m_texture = generateTexture(m_width,m_height,m_pixels);
    }
}

unsigned int DImage::max_tex_units = 32;
unsigned int DImage::max_texture_units = 0;
