#include <stdio.h>
#include <drawpp.hpp>

bool showImage = false;

void draw(float d) {
    /*rect(10, 10, 10, 10);

    if(showImage) {
        rect(20, 20, 10, 10);
    }
    else {
        rect(10, 10, 10, 10);
    }*/
}

void keyPressed() {
    if(key == VK_ESC) {
        exit(1);
    }
}

void mousePressed() {
    showImage = true;
    puts("mousepress");
}

void mouseReleased() {
    showImage = false;
    puts("mouserel");
}

void mouseClicked() {
    puts("mouseclick");
}

void mouseWheel(float d) {
    printf("mousewheel %f\n", d);
}

void mouseMoved() {
    puts("mousemoved");
}

void mouseDragged() {
    puts("mousedragged");
}

int main() {
    Application app(500,300);
    app.setKeyPressed(keyPressed);
    app.setMousePressed(mousePressed);
    app.setMouseReleased(mouseReleased);
    app.setMouseClicked(mouseClicked);
    app.setMouseWheel(mouseWheel);
    app.setMouseMoved(mouseMoved);
    app.setMouseDragged(mouseDragged);
    return app.run(draw);
}