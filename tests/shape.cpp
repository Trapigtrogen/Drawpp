#include <drawpp.hpp>

void setup() {
	size(100, 100);
}

void draw() {
	fill(0, 250, 181); // Set fill colour for next shape
	rect(50, 50, 10, 10); // Draw. Origin point and size
}

int main() {
	runApp();
	return 0;
}

void rect(float x, float y, float w, float h) {
	float vertices[] = {
		-w/2 + x, h/2 + y, // Vertex 1 (X, Y)
		-w/2 + x, -h/2 + y, // Vertex 2 (X, Y)
		w/2 + x, -h/2 + y,  // Vertex 3 (X, Y)
		-w/2 + x, h/2 + y, // Vertex 1 (X, Y)
		w/2 + x, -h/2 + y,  // Vertex 3 (X, Y)
		w/2 + x, h/2 + y  // Vertex 3 (X, Y)
	};

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	float vertices[] = {
		x1, y1, // Vertex 1 (X, Y)
		x2, y2, // Vertex 2 (X, Y)
		x3, y3  // Vertex 3 (X, Y)
	};
}