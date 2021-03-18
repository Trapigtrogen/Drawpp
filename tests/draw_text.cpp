#include <drawpp.hpp>

void setup()
{
    fill(color(100,0,200));
    textFont(loadFont("assets/Tuffy.ttf",100));
}

void draw(float)
{
    background(200,255,100);
    
    text("Test text\nSecond line",100,100);
}

int main() 
{
    Application app(1000,800);
    return app.run(draw,setup);
}