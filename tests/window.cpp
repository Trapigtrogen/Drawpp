#include <stdio.h>
#include <drawpp.hpp>

void setup()
{
    size(500,500);
    setTitle("Test title");
    printf("setup");
    setLocation(getMonitorWidth(0) / 2 - 250, getMonitorHeight(0) / 2 - 250);
}

void draw(float)
{
    background(200,255,100);
    //size(200,200);
}

int main() 
{
    Application app(500,300);
    return app.run(draw,setup);
}