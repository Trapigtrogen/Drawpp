#include <drawpp.hpp>


void draw(float)
{
    background(200,255,100);
    
    strokeWeight(1);
    circle(100,100,100);

    strokeWeight(10);
    circle(350, 100, 75);

    strokeWeight(1);
    ellipse(100, 350, 100,400);

    strokeWeight(30);
    ellipse(350, 350, 500, 100);
}

int main() 
{
    Application app(1000,800);
    return app.run(draw);
}