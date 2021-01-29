#ifndef DPP_PRIMITIVES_H
#define DPP_PRIMITIVES_H

/// Primitive class includes vertices for basic shapes
class Primitive
{
public:
	static float* triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	static float* rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
private:
};

#endif