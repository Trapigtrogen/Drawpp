#include <drawpp.hpp>

void draw(float)
{
    background(200,255,100);
    
    strokeWeight(1);
    quad(100, 100, 250, 300, 200, 100, 200, 200);

}

int main() 
{
    Application app(1000,800);
    return app.run(draw);
}