#include <image.hpp>
#include <debug.hpp>
#include <cassert>
#include <glad.h>
#include <cstring>
#include <color.hpp>

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

DImage::~DImage() 
{
	if(m_pixels != nullptr) free(m_pixels);
	if(m_texture != 0) glDeleteTextures(1, &m_texture);
}

DImage::DImage() = default;

DImage::DImage(int width, int height)
{
    m_width = width;
    m_height = height;

    m_pixels = static_cast<Color*>(malloc(width * height * 4));

    for(unsigned i = 0; i < width*height; ++i)
    {
        (m_pixels + i)->red     = 255;
        (m_pixels + i)->green   = 255;
        (m_pixels + i)->blue    = 255;
        (m_pixels + i)->alpha   = 255;
    }

    m_texture = generateTexture(width, height, m_pixels);
}

DImage::DImage(Color* _pixels, unsigned int _texture, int w, int h)
{
	m_pixels = _pixels;
	m_texture = _texture;
	m_width = w;
	m_height = h;
}

DImage::DImage(const DImage& other) 
{
	m_height = other.m_height;
	m_width = other.m_width;

	if(other.m_pixels != nullptr) 
	{
        unsigned size = other.m_width * other.m_height * 4;
		m_pixels = static_cast<Color*>(malloc(size));
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

	other.m_pixels = nullptr;
	other.m_texture = 0;
	other.m_height = 0;
	other.m_width = 0;
}

DImage& DImage::operator=(const DImage& other) 
{
	if(this != &other) 
	{
		m_height = other.m_height;
		m_width = other.m_width;

		free(m_pixels); // Remove old pixels and copy new ones
        m_pixels = nullptr;

		if(other.m_pixels != nullptr) 
		{
            unsigned size = other.m_width * other.m_height * 4;
			m_pixels = static_cast<Color*>(malloc(size));
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
		if (m_pixels != nullptr) free(m_pixels);
		if (m_texture != 0) glDeleteTextures(1, &m_texture);

		m_pixels = other.m_pixels;
		m_texture = other.m_texture;
		m_height = other.m_height;
		m_width = other.m_width;

		other.m_pixels = nullptr;
		other.m_texture = 0;
		other.m_height = 0;
		other.m_width = 0;
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
	stbi_set_flip_vertically_on_load(0);

	int width, height, channels;
	Color* pixels = reinterpret_cast<Color*>(stbi_load(fileName.c_str(), &width, &height, &channels, 4));

	if(pixels == NULL)
		dbg::error(("Image data not found: " + fileName).c_str());

	GLuint m_texture = generateTexture(width, height, pixels);

	DImage tmpImg(pixels, m_texture, width, height);

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

    Color* imgdata = static_cast<Color*>(malloc(w4*height));

    nsvgRasterize(raster,image,0,0,scale,reinterpret_cast<unsigned char*>(imgdata),width,height,w4);

    GLuint texture = generateTexture(width,height,imgdata);

    nsvgDelete(image);
    nsvgDeleteRasterizer(raster);

    return DImage(imgdata,texture,width,height);
}

DImage DImage::createImage(Color* pixelData, int width, int height)
{
    unsigned size = width * height * 4;
    Color* pixels = static_cast<Color*>(malloc(size));
    std::memcpy(pixels,pixelData,size);

	GLuint m_texture = generateTexture(width, height, pixels);

	DImage tmpImg(pixels, m_texture, width, height);

	return tmpImg;
}

unsigned int DImage::generateTexture(int width, int height, Color* pixels)
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

Color* DImage::pixels()
{
    return reinterpret_cast<Color*>(m_pixels);
}

const Color* DImage::pixels() const
{
    return reinterpret_cast<Color*>(m_pixels);
}

Color& DImage::operator[](size_t index)
{
    return pixels()[index];
}

const Color& DImage::operator[](size_t index) const
{
    return pixels()[index];
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

unsigned int DImage::max_texture_units = 32;
