#ifndef DPP_IMAGE_H
#define DPP_IMAGE_H

#include <string>

///  DImage is an object that textures can be loaded to from image or pixel set
class DImage
{
    friend class DGraphics;
    friend class Application;

public:

	DImage();
	~DImage();

	DImage(const DImage&);
	DImage(DImage&& other);

	DImage& operator=(const DImage& other);
	DImage& operator=(DImage&& other);


    ///\brief Load an image from a file
	static DImage loadImage(const std::string& fileName);


    ///\brief Load an image from an svg file
    static DImage loadSVGImage(const std::string& filename, float scale = 1.0f);


    ///\brief Get image width
    int width() const;


    ///\brief Get image height
    int height() const;


    ///\brief Get the pixel array of this image
    unsigned char* pixels();


    ///\copydoc pixels()
    const unsigned char* pixels() const;


    ///\brief Push the pixel array to the gpu
    void apply();

private:

    unsigned char* m_pixels = nullptr;
	int m_width = 0;
	int m_height = 0;
	unsigned int m_texture = 0;

    static unsigned int max_texture_units;

	DImage(unsigned char* _pixels, unsigned int _texture, int w, int h);
	void bind(unsigned int unit) const;
	static unsigned int generateTexture(int w, int h, unsigned char* pixels);
};

#endif