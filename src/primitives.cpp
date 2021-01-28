#include <primitives.hpp>

float* Primitive::triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3) {
	float triangle[] = {
		x1, y1, z1,
		x2, y2, z2,
		x3, y3, z3,
	};
	return triangle;
}

float* Primitive::rectangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4) {
	float rectangle[] = {
		x1, y1, z1,
		x2, y2, z2,
		x3, y3, z3,
		x1, y1, z1,
		x3, y3, z3,
		x4, y4, z4
	};
	return rectangle;
}