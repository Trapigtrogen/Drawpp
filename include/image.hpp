#ifndef DPP_IMAGE_H
#define DPP_IMAGE_H

#include <string>

class Color;

///  DImage is an object that textures can be loaded to from image or pixel set
class DImage
{
    friend class DGraphics;
    friend class Application;

public:

	DImage();
	~DImage();


    ///\brief Create an empty white image of size ( \p width, \p height )
    DImage(int width, int height);


	DImage(const DImage&);
	DImage(DImage&& other);

	DImage& operator=(const DImage& other);
	DImage& operator=(DImage&& other);


    ///\brief Load an image from a file
	static DImage loadImage(const std::string& fileName);


	///\brief Create custom image with \p pixels
	static DImage createImage(Color* pixels, int width, int height);
    

    ///\brief Load an image from an svg file
    static DImage loadSVGImage(const std::string& filename, float scale = 1.0f);


    ///\brief Get image width
    int width() const;


    ///\brief Get image height
    int height() const;


    ///\brief Get the pixel array of this image
    Color* pixels();


    ///\copydoc pixels()
    const Color* pixels() const;

    Color& operator[](size_t index);
    const Color& operator[](size_t index) const;


    ///\brief Push the pixel array to the gpu
    void apply();

private:

    Color* m_pixels = nullptr;
	int m_width = 0;
	int m_height = 0;
	unsigned int m_texture = 0;

    static unsigned int max_texture_units;

	DImage(Color* _pixels, unsigned int _texture, int w, int h);
	void bind(unsigned int unit) const;
	static unsigned int generateTexture(int w, int h, Color* pixels);
};

#endif