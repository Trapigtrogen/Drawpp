#include <drawpp.hpp>

void setup() {
	size(100, 100);
}

void draw(float) {
	//fill(0, 250, 181); // Set fill colour for next shape
	rect(0, 0, 10, 10); // Draw. Origin point and size
}

int main() {
	Application app(500, 300);
	return app.run(draw, setup);
}