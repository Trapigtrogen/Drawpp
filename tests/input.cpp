#include <drawpp.hpp>

bool showImage = false;

void draw(float d) {
    rect(10, 10, 10, 10);

    if(showImage) {
        rect(20, 20, 10, 10);
    }
    else {
        rect(10, 10, 10, 10);
    }
}

void keyPressed() {
    if(key == VK_ESC) {
        exit();
    }
}

void mousePressed() {
    showImage = true;
}

void mouseReleased() {
    showImage = false;
}

int main() {
    Application app(500,300);
    app.setKeyPressed(keyPressed);
    return app.run(draw);
}