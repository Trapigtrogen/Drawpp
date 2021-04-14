#include <drawpp.hpp>
#include <iostream>

DShape shape1; // 1 element image
DShape shape2; // no image. child of 3
DShape shape3; // 2 custom named element image
DShape shape4; // empty image

DImage img;
DImage img2;

void setup() 
{
    setResizable(true);
    size(1000, 1000);
    setTitle("Vertex Shaping");

    // Empty images are not allowed and system should revert the load after loading svg with no elements
    printf("Loading empty image to shape4...\n");
    //shape4 = loadShape("assets/empty.svg"); 

    // Normal image containing 1 element
    // DEBUG seems like all the images  with 1 element will break
    printf("Loading image (1 element) to shape1...\n");
    shape1 = loadShape("assets/circleimage.svg");

    // Normal image containing multiple elements with names/ids
    printf("Loading image (multiple elements) to shape3...\n\n");
    shape3 = loadShape("assets/bot1.svg");

    
    // Naming
    shape1.name() = "shape1";
    shape2.name() = "shape2";
    shape3.name() = "shape3";
    shape4.name() = "shape4";

    
    // Manual childing tests 
    shape1.addChild(shape4);

    // Count shape1 children
    int childSize = shape1.getChildCount();
    std::cout << "Shape1 has " << childSize << " children \nThey are:\n";
    for(int i = 0; i < childSize; ++i)
    {
        std::cout << shape1.getChild(i).name() << "\n";
    }
    printf("\n\n\n");

    shape2 = shape1.getChild(0);
    
    int sh_ix = shape3.findChild("star");
    if (sh_ix >= 0)
    {
        shape2 = shape3.getChild(sh_ix);
    }
    std::cout << "shape2 name: " << shape2.name() << "\n";
    
    printf("\n\n\n");

    // Count shape3 children
    childSize = shape3.getChildCount();
    std::cout << "Shape3 has " << childSize << " children \nThey are:\n";
    for(int i = 0; i < childSize; ++i)
    {
        std::cout << shape3.getChild(i).name() << "\n";
    }

    // Load svg as an image
    img = loadSVGImage("assets/bot1.svg");

    img2 = img;
}

void draw(float) 
{
    background(255,255,255);
    shape(shape3, 10.0f, 10.0f);
    shape(shape1, 10.0f, 10.0f,2,1);
    image(img, 20 + img.width(), 10);
    image(img2, 30 + img.width()*2, 10);
}

int main() 
{
    Application app(500, 300);
    return app.run(draw, setup);
}