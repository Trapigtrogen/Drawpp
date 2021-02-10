#include <shape.hpp>
#include <debug.hpp>

#define NANOSVG_ALL_COLOR_KEYWORDS	// Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION		// Expands implementation
#include "nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

DShape::~DShape()
{
	delete[] data;
	for(auto& it : children) 
	{
		it->removeParent();
	}
	children.clear();
	//nsvgDelete(image); // DEBUG NOT TESTED
}

DShape::DShape()
{
	data = new unsigned char[0];
}

DShape::DShape(const DShape& other)
{
	delete[] data;
	data = new unsigned char[strlen((char*)other.data)];
	std::copy(other.data, other.data + strlen((char*)other.data), data);
	visible = other.visible;
	parent = other.parent;
	image = other.image;
	for(auto& it : other.children)
	{
		addChild(it);
	}

}

DShape::DShape(DShape&& other)
{
	data = other.data;
	visible = other.visible;
	parent = other.parent;
	image = other.image;
	for(auto& it : other.children) 
	{
		addChild(it);
		other.removeChild(it);
	}

	other.data = nullptr;
	other.visible = 0;
	other.parent = nullptr;
	other.image = nullptr;
}

DShape& DShape::operator=(DShape& other)
{
	if(this != &other) 
	{
		delete[] data;

		data = other.data;
		visible = other.visible;
		parent = other.parent;
		image = other.image;
		for(auto& it : other.children) 
		{
			addChild(it);
		}
	}

	return *this;
}

DShape& DShape::operator=(DShape&& other) 
{
	if(this != &other)
	{
		delete[] data;

		data = other.data;
		visible = other.visible;
		parent = other.parent;
		image = other.image;
		for(auto& it : other.children) {
			addChild(it);
			other.removeChild(it);
		}

		other.data = nullptr;
		other.visible = 0;
		other.parent = nullptr;
		other.image = nullptr;
	}

	return *this;
}

void DShape::addChild(DShape* child)
{
	child->renderIdx = renderIdx + 1;
	children.push_back(child);
	child->addParent(this);
}

void DShape::addChild(DShape* child, int _renderIdx)
{
	child->renderIdx = _renderIdx;
	children.push_back(child);
	child->addParent(this);
}

void DShape::removeChild(DShape* child)
{
	std::vector<DShape*>::iterator it = std::find(children.begin(), children.end(), child);
	if(it != children.end()) 
	{
		children.erase(it);
		child->removeParent();
	}
	else dbg::error("Given object is not child of this object");
}

void DShape::addParent(DShape* _parent)
{
	parent = _parent;
}

void DShape::removeParent()
{
	parent = nullptr;
}

size_t DShape::getChildCount()
{
	return children.size();
}

DShape* DShape::getChild(int idx) 
{
	std::vector<DShape*>::iterator it = children.begin() + idx;
	return *it;
}

DShape* DShape::getParent()
{
	return parent;
}

DShape DShape::loadShape(std::string filename)
{
	DShape tempShape;
	tempShape.loadSVG(filename);

	return tempShape;
}

DShape DShape::createShape()
{
	return DShape(); // DEBUG TEMP
}

DShape DShape::createShape(ShapeType type)
{
	return DShape(); // DEBUG TEMP
}

//DShape DShape::createShape(ShapeType type, float[] p){}

void DShape::loadSVG(std::string filename)
{
	DShape tempShape;

	// Load File
	image = nsvgParseFromFile(filename.c_str(), "px", 96);
	int i = 1;
	for(; image->shapes->next != NULL; ++i) {}
	printf("children: %i", i);

	for(NSVGshape* targetChild = image->shapes; targetChild->next != NULL; targetChild = targetChild->next)
	{
		DShape* childShape = new DShape;
		childShape->image = new NSVGimage;
		childShape->image->height = image->height;
		childShape->image->width = image->width;
		childShape->name = targetChild->id;
		childShape->image->shapes = targetChild;

		addChild(childShape);
	}
}