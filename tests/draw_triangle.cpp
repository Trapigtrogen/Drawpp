#include <drawpp.hpp>

void draw(float)
{
    background(200,255,100);
    
    strokeWeight(1);
    triangle(100,100,200,200,200,100);

    strokeWeight(10);
    triangle(300, 100, 400, 200, 400, 100);

    strokeWeight(0);
    triangle(300, 500, 420, 400, 100, 300);

    strokeWeight(30);
    triangle(800, 500, 700, 200, 400, 780);
}

int main() 
{
    Application app(1000,800);
    return app.run(draw);
}