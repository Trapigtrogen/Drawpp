#include <application.hpp>
#include <drawpp.hpp>

void size(int width, int height)
{
    Application::GetInstance()->size(width,height);
}

void setTitle(const char* title)
{
    Application::GetInstance()->setTitle(title);
}

void setResizable(bool state)
{
    Application::GetInstance()->setResizable(state);
}

void exit()
{
    Application::GetInstance()->exit();
}


// Image
DImage loadImage(const std::string& fileName) 
{
    return DImage::loadImage(fileName);
}

void image(DImage image, int x, int y) 
{
    image.drawImage(x, y, image.width, image.height);
}

void image(DImage image, int x, int y, int width, int height) {
    image.drawImage(x, y, width, height);
}

void background(DImage image) 
{
    // DEBUG TODO: Set background to image.pixels
}

// Shapes
void rect(int x, int y, int width, int height)
{
    // DEBUG TEMP:
	float ratio = 200.0f / 200.0f;
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}