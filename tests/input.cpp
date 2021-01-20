#include <drawpp.hpp>

bool showImage = false;
DImage img;

int setup() {
	img = loadImage("assets/img.jpg");
}

void draw() {
	if (showImage) {
		image(img, 0, 0);
	}
}


void keyPressed() {
	if (key == CODED) {
		if (keyCode == ESC) {
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