#include <drawpp.hpp>

void draw(float)
{
    background(200,255,100);
    
    strokeCap(ROUND);

    strokeWeight(1);
    line(100,100,200,120);

    strokeWeight(10);
    line(300, 100, 500, 300);

    strokeCap(SQUARE);

    strokeWeight(30);
    line(100, 400, 270, 600);

    strokeWeight(50);
    line(600, 400, 300, 700);

    strokeCap(ROUND);

    strokeWeight(70);
    point(700, 100);

    strokeWeight(20);
    point(700, 300);

    strokeWeight(150);
    point(800, 500);
}

int main() 
{
    Application app(1000,800);
    return app.run(draw);
}