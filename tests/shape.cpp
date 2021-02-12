#include <drawpp.hpp>

DShape shape1; // 1 element image
DShape shape2; // no image. child of 1
DShape shape3; // 2 custom named element image
DShape shape4; // empty image

void setup() 
{
    size(500, 500);
    setTitle("Vertex Shaping");
    setResizable(true);

    // Empty images are not allowed and system should revert the load after loading svg with no elements
    printf("Loading empty image to shape4...\n");
    shape4 = loadShape("../../tests/assets/empty.svg"); 

    // Normal image containing 1 element
    printf("Loading image (1 element) to shape1...\n");
    shape1 = loadShape("../../tests/assets/archlinux-logo-black.svg");

    // Normal image containing 2 elements with names/ids
    printf("Loading image (multiple elements) to shape3...\n\n");
    shape3 = loadShape("../../tests/assets/starstripe.svg");

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
    //fill(0, 250, 181); // Set fill colour for next shape
    //rect(0, 0, 10, 10); // Draw. Origin point and size
    
    shape(shape1, 10, 10, 80, 80);
}

int main() 
{
    Application app(500, 300);
    return app.run(draw, setup);
}