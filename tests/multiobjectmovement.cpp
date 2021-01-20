void setup() {
	size(200, 200);
}

int i = 0;

void draw() {
	background(255);
	fill(0, 250, 181);
	translate(i, i);
	rotate(i);
	rect(1, 1, 10, 10);

	translate(-i, -i);
	fill(255, 250, 181);
	rect(100, 100, 10, 10);
	i++;
}