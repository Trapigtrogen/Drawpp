#ifndef DPP_NOISE_H
#define DPP_NOISE_H

class Noise
{
public:
	Noise();
	///\brief Reinitialies the noise
	///
	/// Can be used for example when screen size changes
	void initNoise();

	///\brief Resize noise map to match window size
	void resize();

	~Noise() = default;

	///\brief Set noise seed manually
	void noiseSeed(int seed);

	///\brief Get 1D noise value from given coordinate
	float pNoise(unsigned int x);

	///\brief Get 2D noise value from given coordinate
	float pNoise(unsigned int x, unsigned int y);

	///\brief Set the amount of layers of noise
	/// Default is 8
	void setOctaves(int lod) { nOctaves = lod; }

	///\brief Set the cap between layers
	/// Default is 0.5 which means halving every frame
	void setFalloff(float foff) { falloff = foff; }

private:
	int nOctaves = 8;
	float falloff = 0.5;

	int outputWidth = 0;
	int outputHeight = 0;

	float* noiseSeed1D = nullptr;
	float* perlinNoise1D = nullptr;

	float* noiseSeed2D = nullptr;
	float* perlinNoise2D = nullptr;


	void randomSeed1D();
	void randomSeed2D();

	void createPerlin1D(int nCount, float scale);
	void createPerlin2D(int nWidth, int nHeight, float scale);
};
#endif