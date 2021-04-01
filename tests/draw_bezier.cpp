#include <drawpp.hpp>

void setup()
{
    bezierDetail(30);
    strokeWeight(5);
    stroke(255,100,50);
}

void draw(float)
{
    background(200,255,100);
    
    bezier(500,100,500,900,-500,400,1500,600);
    bezier(100, 800, 900, 800, 500, 1100);
}

int main() 
{
    Application app(1000,1000);
    return app.run(draw,setup);
}