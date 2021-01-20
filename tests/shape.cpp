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