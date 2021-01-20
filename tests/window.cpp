#include <stdio.h>
#include <drawpp.hpp>

void setup()
{
    printf("setup");
}

void draw()
{
    printf("draw");
}

int main() 
{
    runApp();
    return 0;
}