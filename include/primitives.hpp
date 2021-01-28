#ifndef DPP_PRIMITIVES_H
#define DPP_PRIMITIVES_H

/// Primitive class includes vertices for basic shapes
class Primitive
{
public:
	static float* triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3);
	static float* rectangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4);
private:
};

#endif