#include <drawpp.hpp>

void setup() 
{
	size(200, 200);
}

int i = 0;

void draw(float) 
{
	background(255);
	translate(i, i);
	rotate(i);
	rect(0, 0, 10, 10);
	i++;
}

int main()
{
	Application app(500, 300);
	return app.run(draw, setup);
}