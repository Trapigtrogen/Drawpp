#include <drawpp.hpp>
#include <nanosvg.h>
#include <nanosvgrast.h>

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

    // Child tests
    shape2.debugName = "shape2";
    shape1.debugName = "shape1";    
    shape3.debugName = "shape3";
    shape4.debugName = "shape4";

    shape1.addChild(&shape2); // DEBUG TODO(?): Get rid of "&"
    shape1.addChild(&shape3);

    int childSize = shape1.getChildCount();

    // DEBUG:
    // Something weird about this: Randomily gives error when printing various data
    // Then usually works just fine

    // Count children
    std::cout << "Shape1 has " << childSize << " children \nThey are:\n";
    for(int i = 0; i < childSize; ++i)
    {
        std::cout << shape1.getChild(i)->debugName << "\n";
    }
    
    // Find parent
    std::cout << "\nshape2 parent: " << shape2.getParent()->debugName << "\n";
    std::cout << "shape3 parent: " << shape3.getParent()->debugName << "\n";
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