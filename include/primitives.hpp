#ifndef DPP_SHAPE_H
#define DPP_SHAPE_H

#include <debug.hpp>

class Shape
{
public:
	Shape();
	~Shape();

	float triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3);

	float rectangle();

private:
};

#endif