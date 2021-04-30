#ifndef DPP_NOISE_H
#define DPP_NOISE_H

///\brief Noise class provides 1D and 2D fractal noise
class Noise
{
public:
	Noise();
	///\brief Reinitialies the noise
	///
	/// Can be used for example when screen size changes
	void initNoise();

	///\brief Resize noise map
	void resize(int width, int height);

	~Noise() = default;

	///\brief Set noise seed manually
	/// Also recreates noise
	void noiseSeed(int seed);

	///\brief Get 1D noise value from given coordinate
	///
	///\returns value of \p perlinNoise1D in given coodinate \p x
	float pNoise(unsigned int x);

	///\brief Get 2D noise value from given coordinate
	///
	///\returns value of \p perlinNoise2D in given coodinate \p x , \p y
	float pNoise(unsigned int x, unsigned int y);

	///\brief Set the amount of layers of noise
	/// Default is 8
	void setOctaves(int lod);

	///\brief Set the cap between layers
	/// Default is 0.5 which means halving every frame
	void setFalloff(float foff);

	///\brief Set noise scale 
	/// Default is 1.3
	/// Lower value means stronger curve and higher make it smoother
	void setScale(float _scale);

	int width() { return outputWidth; }
	int height() { return outputHeight; }

	float* perlinNoise2D = nullptr;

private:
	int nOctaves = 8;
	float falloff = 0.5;
	float scale = 1.3f;

	int outputWidth = 512;
	int outputHeight = 512;

	float* noiseSeed1D = nullptr;
	float* noiseSeed2D = nullptr;
	float* perlinNoise1D = nullptr;

	void randomSeed1D();
	void randomSeed2D();

	void createPerlin1D(int nCount, float scale);
	void createPerlin2D(int nWidth, int nHeight, float scale);
};
#endif