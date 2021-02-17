#include <drawpp.hpp>

void setup() 
{
}

void draw(float)
{
	//line(30, 20, 85, 75);
}

int main()
{
	Application app(500, 300);
	return app.run(draw, setup);
}