#ifndef DPP_DSHAPE_H
#define DPP_DSHAPE_H

#include <string>
#include <vector>

class DShape
{
public:
	DShape();
	~DShape();

	DShape(const DShape&);
	DShape(DShape&& other);

	DShape& operator=(DShape& other);
	DShape& operator=(DShape&& other);
	DShape& operator=(DShape* other);

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
	static DShape createShape(DShape::ShapeType type);
	//static DShape createShape(DShape::ShapeType type, float[] p);

	void addChild(DShape* child);
	void addChild(DShape* child, int _idx);
	void removeChild(DShape* child);

	DShape* getChild(int idx);
	DShape* getChild(std::string);
	size_t getChildCount();
	DShape* getParent();

	void setVisible(bool visibility) { visible = visibility; };
	bool isVisible() { return visible; };

	// Drawable objects are in image->shapes. If image == NULL go through children's images
	struct NSVGimage* image;

	std::string name;
private:
	bool visible = true;

	int renderIdx = 0;

	DShape* parent = nullptr;
	std::vector<DShape*> children;

	void addParent(DShape* _parent);
	void removeParent();

	void loadSVG(std::string filename);
};

#endif