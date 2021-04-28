#include <drawpp.hpp>

DImage img;
DImage emptyImg;
DImage bg_img;

DFilter pixelate_filter;

void setup() 
{
	img = loadImage("assets/img.jpg");
	bg_img = loadImage("assets/bg_img.jpg");

	pixelate_filter = DFilter::loadFilter(R"(
    void main()
    {
        vec2 p = gl_FragCoord.xy/source_size;

        p.x -= mod(p.x, 20.0 / source_size.x);
        p.y -= mod(p.y, 20.0 / source_size.y);
        
        vec3 col = texture2D(source, p).rgb;
        gl_FragColor = vec4(col, 1.0);
    })");
}

void draw(float t) 
{
	background(bg_img);
	imageMode(CORNER);
	image(img, 0, 0, 300, 300);
	image(bg_img, 500, 300, 100, 100);

	filter(pixelate_filter);
}

int main()
{
	Application app(1000, 700);
	return app.run(draw, setup);
}