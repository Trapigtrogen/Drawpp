#include <drawpp.hpp>

bool showImage = false;

void draw() {
    rect(10, 10, 10, 10);

    if(showImage) {
        rect(20, 20, 10, 10);
    }
    else {
        rect(10, 10, 10, 10);
    }
}


void keyPressed() {
    if(key == CODED) {
        if(keyCode == ESC) {
            exit();
        }
    }
}

void mousePressed() {
    showImage = true;
}

void mouseReleased() {
    showImage = false;
}

int main() {
    runApp();
    return 0;
}