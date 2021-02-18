#include <stdio.h>
#include <drawpp.hpp>

DImage* imm;

void setup()
{
    size(500,500);
    setTitle("Test title");
    setResizable(true);
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