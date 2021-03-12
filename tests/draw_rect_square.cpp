#include <drawpp.hpp>

void draw(float)
{
    background(200,255,100);
    
    strokeWeight(1);
    square(100,100,100);

    strokeWeight(10);
    rect(300, 100, 300, 150);

    strokeWeight(0);
    rect(100, 400, 150, 150, 40);

    strokeWeight(30);
    rect(300, 400, 500, 200, 10, 30, 50, 70);
}

int main() 
{
    Application app(1000,800);
    return app.run(draw);
}