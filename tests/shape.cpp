#include <drawpp.hpp>

DShape shape1;
DShape shape2;
DShape shape3;
DShape shape4;

void setup() 
{
    size(500, 500);
    setTitle("Test title");
    setResizable(true);

    shape1 = loadShape("D:/Projects/CPP/graphics-library/tests/assets/archlinux-logo-block.svg");

    shape1.addChild(&shape2); // DEBUG TODO: Get rid of "&"
    
    //std::cout << shape1.getChild(0)->data << "\n";
}

void draw(float) 
{
    //fill(0, 250, 181); // Set fill colour for next shape
    //rect(0, 0, 10, 10); // Draw. Origin point and size
    
    shape(shape1, 10, 10, 80, 80);
}

int main() 
{
    Application app(500, 300);
    return app.run(draw, setup);
}