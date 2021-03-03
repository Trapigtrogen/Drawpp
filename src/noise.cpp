#include <noise.hpp>
#include <debug.hpp>

#include <application.hpp>

Noise::Noise()
{
	initNoise();
}

void Noise::initNoise()
{
	delete[] noiseSeed1D;
	noiseSeed1D = new float[outputWidth];
	delete[] perlinNoise1D;
	perlinNoise1D = new float[outputWidth];

	delete[] noiseSeed2D;
	noiseSeed2D = new float[outputWidth * outputHeight];
	delete[] perlinNoise2D;
	perlinNoise2D = new float[outputWidth * outputHeight];
}

void Noise::resize() 
{
	outputWidth = Application::GetInstance()->getWidth();
	outputHeight = Application::GetInstance()->getHeight();
	initNoise();
}

void Noise::noiseSeed(int seed)
{
	// DEBUG: how should do?
}

void Noise::randomSeed1D() 
{
	delete[] noiseSeed1D;
	noiseSeed1D = new float[outputWidth];

	for(int i = 0; i < outputWidth; i++)
	{
		noiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
	}
}

void Noise::randomSeed2D()
{
	delete[] noiseSeed2D;
	noiseSeed2D = new float[outputWidth* outputHeight];

	for(int i = 0; i < outputWidth * outputHeight; i++) 
	{
		noiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
	}
}

float Noise::pNoise(unsigned int x)
{
	// if random
	randomSeed1D();
	createPerlin1D(outputWidth, 1);

	if(x > outputWidth) x = outputWidth;
	return perlinNoise1D[x];
}

float Noise::pNoise(unsigned int x, unsigned int y)
{
	// if random
	randomSeed2D();
	createPerlin2D(outputWidth, outputHeight, 1);

	if(x > outputWidth) x = outputWidth;
	if(y > outputHeight) y = outputHeight;
	return perlinNoise1D[y * outputWidth + x];
}

void Noise::createPerlin1D(int nCount, float scale)
{
	for(int x = 0; x < nCount; x++) 
	{
		float fNoise = 0.0f;
		float fScaleAcc = 0.0f;
		float fScale = 1.0f;

		for(int o = 0; o < nOctaves; o++)
		{
			int nPitch = nCount >> o;
			int nSample1 = (x / nPitch) * nPitch;
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

void Noise::createPerlin2D(int nWidth, int nHeight, float scale)
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
				int nPitch = nWidth >> o;
				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

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