#include <drawpp.hpp>

void draw(float)
{
    background(200,255,100);
    
    strokeWeight(1);
    quad(100, 100, 250, 300, 200, 100, 200, 200);

    strokeWeight(10);
    quad(300, 100, 550, 300, 500, 100, 550, 200);

    strokeWeight(20);
    quad(100, 300, 150, 600, 290, 550, 250, 310);

    strokeWeight(5);
    quad(600, 300, 790, 550, 650, 310, 550, 600);

    strokeWeight(7);
    quad(600, 100, 750, 300, 700, 200, 700, 100);

    strokeWeight(7);
    quad(900, 200, 800, 100, 950, 300, 900, 100);

    strokeWeight(7);
    quad(800, 400, 900, 500, 950, 600, 900, 400);

}

int main() 
{
    Application app(1000,800);
    return app.run(draw);
}