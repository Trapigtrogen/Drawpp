#include <stdio.h>
#include <drawpp.hpp>

void setup()
{
    size(500,500);
    setTitle("Test title");
    setResizable(true);
}

void draw()
{
    size(200,200);
}

int main() 
{
    runApp();
    return 0;
}