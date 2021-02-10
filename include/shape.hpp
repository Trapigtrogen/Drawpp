#ifndef DPP_DSHAPE_H
#define DPP_DSHAPE_H

#include <string>
#include <vector>
#include <algorithm>

class DShape
{
public:
	DShape();
	~DShape();

	DShape(const DShape&);
	DShape(DShape&& other);

	DShape& operator=(DShape& other);
	DShape& operator=(DShape&& other);

	enum ShapeType
	{
		POINT,
		LINE,
		TRIANGLE,
		QUAD,
		RECT,
		ELLIPSE,
		ARC,
		BOX,
		SPHERE
	};

	static DShape loadShape(std::string filename);
	static DShape createShape();
	static DShape createShape(ShapeType type);
	//static DShape createShape(ShapeType type, float[] p);

	void addChild(DShape* child);
	void addChild(DShape* child, int _idx);
	void removeChild(DShape* child);

	DShape* getChild(int idx);
	DShape* getChild(std::string);
	size_t getChildCount();
	DShape* getParent();

	void setVisible(bool visibility) { visible = visibility; };
	bool isVisible() { return visible; };

	unsigned char* data = nullptr;

	// Drawable objects are in image->shapes
	struct NSVGimage* image;

	char* name;
private:
	bool visible = true;

	int renderIdx;

	DShape* parent = nullptr;
	std::vector<DShape*> children;

	void addParent(DShape* _parent);
	void removeParent();

	void loadSVG(std::string filename);
};

#endif