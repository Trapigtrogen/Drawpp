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

	void setVisible(bool visibility) { visible = visibility; };
	bool isVisible() { return visible; };

	char* data = nullptr;
private:
	bool visible = true;

	int renderIdx;

	DShape* parent = nullptr;
	std::vector<DShape*> children;

	void addParent(DShape* _parent);
	void removeParent();

	void LoadSVG(std::string filename);
};

#endif