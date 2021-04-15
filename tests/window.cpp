#include <stdio.h>
#include <drawpp.hpp>

void setup()
{
    size(500,500);
    setTitle("Test title");
    printf("setup");
}

void draw(float)
{
    background(200,255,100);
    size(200,200);
}

int main() 
{
    Application app(500,300);
    return app.run(draw,setup);
}