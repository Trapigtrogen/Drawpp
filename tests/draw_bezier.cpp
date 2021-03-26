#include <drawpp.hpp>


void draw(float)
{
    background(200,255,100);
    
    strokeWeight(5);
    stroke(255,100,50);
    bezier(500,100,500,900,-500,400,1500,600);
}

int main() 
{
    Application app(1000,1000);
    return app.run(draw);
}