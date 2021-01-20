#include <stdio.h>
#include <drawpp.hpp>

void setup()
{
    size(500,500);
    setTitle("Test title");
    setResizable(true);
}

void draw(float)
{
    size(200,200);
}

int main() 
{
    Application app(500,300);
    return app.run(draw,setup);
}