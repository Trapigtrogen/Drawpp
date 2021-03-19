#include <drawpp.hpp>
#include <iostream>

DShape shape1; // 1 element image
DShape shape2; // no image. child of 3
DShape shape3; // 2 custom named element image
DShape shape4; // empty image

void setup() 
{
    setResizable(true);
    size(1000, 1000);
    setTitle("Vertex Shaping");

    // Empty images are not allowed and system should revert the load after loading svg with no elements
    printf("Loading empty image to shape4...\n");
    shape4 = loadShape("assets/empty.svg"); 

    // Normal image containing 1 element
    // DEBUG seems like all the images  with 1 element will break
    printf("Loading image (1 element) to shape1...\n");
    shape1 = loadShape("assets/circleimage.svg");

    // Normal image containing 2 elements with names/ids
    printf("Loading image (multiple elements) to shape3...\n\n");
    shape3 = loadShape("assets/starstripe.svg");

    // Naming
    shape1.name = "shape1";
    shape2.name = "shape2";
    shape3.name = "shape3";
    shape4.name = "shape4";

    // Manual childing tests 
    shape1.addChild(&shape4); // DEBUG TODO(?): Get rid of "&"

    // Count shape1 children
    int childSize = shape1.getChildCount();
    std::cout << "Shape1 has " << childSize << " children \nThey are:\n";
    for(int i = 0; i < childSize; ++i)
    {
        std::cout << shape1.getChild(i)->name << "\n";
    }
    printf("\n\n\n");

    shape2 = shape1.getChild(0);
    shape2 = shape3.getChild("star");
    std::cout << "shape2 name: " << shape2.name << "\n";
    
    // Find parent
    std::cout << "shape2 parent: " << shape2.getParent()->name << "\n";

    printf("\n\n\n");

    // Count shape3 children
    childSize = shape3.getChildCount();
    std::cout << "Shape3 has " << childSize << " children \nThey are:\n";
    for(int i = 0; i < childSize; ++i) {
        std::cout << shape3.getChild(i)->name << "\n";
    }
}

void draw(float) 
{
    background(255,255,255);
    //shape(shape3);
    strokeWeight(7);
    shape(shape3, mouseX, mouseY, 1, 1);
}

int main() 
{
    Application app(500, 300);
    return app.run(draw, setup);
}