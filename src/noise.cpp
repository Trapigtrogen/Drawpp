#include <noise.hpp>
#include <debug.hpp>
#include <application.hpp>
#include <random.hpp>

static Random noiseRandom;
static int current_noise_seed = 1234;

Noise::Noise()
{
	initNoise();
}

Noise::~Noise()
{
    delete[] perlinNoise1D;
    delete[] perlinNoise2D;
    delete[] noiseSeed1D;
    delete[] noiseSeed2D;
}

void Noise::initNoise()
{
    noiseRandom.randomSeed(current_noise_seed);

	randomSeed1D();

	delete[] perlinNoise1D;
	perlinNoise1D = new float[outputWidth];
	createPerlin1D(outputWidth);

	randomSeed2D();

	delete[] perlinNoise2D;
	perlinNoise2D = new float[outputWidth * outputHeight];
	createPerlin2D(outputWidth, outputHeight);
}

void Noise::resize(int width, int height) 
{
	outputWidth = width;
	outputHeight = height;
	initNoise();
}

void Noise::noiseSeed(int seed)
{
    current_noise_seed = seed;
    noiseRandom.randomSeed(current_noise_seed);

	randomSeed1D();
	randomSeed2D();
	createPerlin1D(outputWidth);
	createPerlin2D(outputWidth, outputHeight);
}

void Noise::randomSeed1D() 
{
	delete[] noiseSeed1D;
	noiseSeed1D = new float[outputWidth];

	for(int i = 0; i < outputWidth; i++)
	{
        noiseSeed1D[i] = noiseRandom.randomFloat01();
	}
}

void Noise::randomSeed2D()
{
	delete[] noiseSeed2D;
	noiseSeed2D = new float[outputWidth* outputHeight];

	for(int i = 0; i < outputWidth * outputHeight; i++) 
	{
        noiseSeed2D[i] = noiseRandom.randomFloat01();
	}
}

float Noise::pNoise(unsigned int x)
{
    x %= static_cast<unsigned int>(outputWidth);
	return perlinNoise1D[x];
}

float Noise::pNoise(unsigned int x, unsigned int y)
{
    x %= static_cast<unsigned int>(outputWidth);
    y %= static_cast<unsigned int>(outputHeight);
	return perlinNoise2D[y * outputWidth + x];
}

void Noise::createPerlin1D(int nCount)
{
	for(int x = 0; x < nCount; x++) 
	{
		float fNoise = 0.0f;
		float fScaleAcc = 0.0f;
		float fScale = 1.0f;

		for(int o = 0; o < nOctaves; o++)
		{
			int nPitch = nCount;
			for (int i = 0; i < o; i++)
			{
				nPitch = static_cast<int>(nPitch * falloff);
			}
			int nSample1 = x;
			if(nPitch != 0)
			{
				nSample1 = (x / nPitch) * nPitch;
			}
			int nSample2 = (nSample1 + nPitch) % nCount;

			float fBlend = (float)(x - nSample1) / (float)nPitch;

			float fSample = (1.0f - fBlend) * noiseSeed1D[nSample1] + fBlend * noiseSeed1D[nSample2];

			fScaleAcc += fScale;
			fNoise += fSample * fScale;
			fScale = fScale / scale;
		}

		// Scale to seed range
		perlinNoise1D[x] = fNoise / fScaleAcc;
	}
}

void Noise::createPerlin2D(int nWidth, int nHeight)
{
	for(int x = 0; x < nWidth; x++)
	{
		for(int y = 0; y < nHeight; y++) 		
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for(int o = 0; o < nOctaves; o++)
			{
				int nPitch = nWidth;
				for (int i = 0; i < o; i++)
				{
					nPitch = static_cast<int>(nPitch * falloff);
				}
				int nSampleX1 = x;
				int nSampleY1 = y;
				if(nPitch != 0) 
				{
					nSampleX1 = (x / nPitch) * nPitch;
					nSampleY1 = (y / nPitch) * nPitch;
				}

				int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
				int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = (1.0f - fBlendX) * noiseSeed2D[nSampleY1 * nWidth + nSampleX1] + fBlendX * noiseSeed2D[nSampleY1 * nWidth + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * noiseSeed2D[nSampleY2 * nWidth + nSampleX1] + fBlendX * noiseSeed2D[nSampleY2 * nWidth + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / scale;
			}

			// Scale to seed range
			perlinNoise2D[y * nWidth + x] = fNoise / fScaleAcc;
		}
	}
}

void Noise::setOctaves(int lod)
{ 
	nOctaves = lod;
	createPerlin1D(outputWidth);
	createPerlin2D(outputWidth, outputHeight);
}

void Noise::setFalloff(float foff)
{
	falloff = foff;
	createPerlin1D(outputWidth);
	createPerlin2D(outputWidth, outputHeight);
}

void Noise::setScale(float _scale)
{
	scale = _scale;
	createPerlin1D(outputWidth);
	createPerlin2D(outputWidth, outputHeight);
}