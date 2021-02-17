#include <drawpp.hpp>


void draw(float)
{
    background(200,255,100);
    
    strokeWeight(1);
    circle(150,150,100);

    strokeWeight(10);
    circle(390, 150, 75);

    strokeWeight(1);
    ellipse(150, 550, 100,400);

    strokeWeight(30);
    ellipse(600, 400, 500, 100);
}

int main() 
{
    Application app(1000,800);
    return app.run(draw);
}