#include <drawpp.hpp>

void setup() 
{
    size(500, 500);
    setTitle("Test title");
    setResizable(true);
}

void draw(float) 
{
    //fill(0, 250, 181); // Set fill colour for next shape
    //rect(0, 0, 10, 10); // Draw. Origin point and size
}

int main() 
{
    Application app(500, 300);
    return app.run(draw, setup);
}
