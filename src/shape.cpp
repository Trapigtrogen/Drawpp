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
}

DShape::DShape()
{
	data = new unsigned char[0];
	name = (char*)"Shape";
}

DShape::DShape(const DShape& other)
{
	delete[] data;
	data = new unsigned char[strlen((char*)other.data)];
	std::copy(other.data, other.data + strlen((char*)other.data), data);
	visible = other.visible;
	parent = other.parent;
	image = other.image;
	name = other.name;
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
	name = other.name;
	for(auto& it : other.children) 
	{
		addChild(it);
	}

	other.data = nullptr;
	other.visible = 0;
	other.parent = nullptr;
	other.children.clear();
	other.image = nullptr;
	other.name = nullptr;
}

DShape& DShape::operator=(DShape& other)
{
	if(this != &other) 
	{
		delete[] data;
		for(auto& it : children) {
			it->removeParent();
			it->children.clear();
		}
		children.clear();

		data = other.data;
		visible = other.visible;
		parent = other.parent;
		image = other.image;
		name = other.name;
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
		for(auto& it : children) {
			it->removeParent();
			it->children.clear();
		}
		children.clear();

		data = other.data;
		visible = other.visible;
		parent = other.parent;
		image = other.image;
		name = other.name;
		for(auto& it : other.children) {
			addChild(it);
		}

		other.data = nullptr;
		other.visible = 0;
		other.parent = nullptr;
		other.children.clear();
		other.image = nullptr;
		other.name = nullptr;
	}

	return *this;
}

DShape& DShape::operator=(DShape* other) 
{
	if(this != other) 
	{
		delete[] data;
		for(auto& it : children) {
			it->removeParent();
			it->children.clear();
		}
		children.clear();

		data = other->data;
		visible = other->visible;
		parent = other->parent;
		image = other->image;
		name = other->name;
		for(auto& it : other->children) 
		{
			addChild(it);
		}
	}

	return *this;
}

void DShape::addChild(DShape* child)
{
	child->renderIdx = renderIdx + 1;
	child->addParent(this);
	children.push_back(child);
}

void DShape::addChild(DShape* child, int _renderIdx)
{
	child->renderIdx = _renderIdx;
	child->addParent(this);
	children.push_back(child);
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

DShape DShape::createShape(DShape::ShapeType type)
{
	return DShape(); // DEBUG TEMP
}

//DShape DShape::createShape(DShape::ShapeType type, float[] p){}

void DShape::loadSVG(std::string filename)
{
	// Load File to object's data
	image = nsvgParseFromFile(filename.c_str(), "px", 96);

	// Empty image should not be loaded
	if(image->shapes == nullptr) 
	{
		dbg::error("Image is empty. Loading has been cancelled"); 
		nsvgDelete(image);
		image = nullptr;
		return;
	}

	// Make separate copies of child elements
	for(NSVGshape* targetChild = image->shapes; targetChild != NULL; targetChild = targetChild->next) 
	{
		DShape* childShape = new DShape;
		childShape->image = new NSVGimage;
		childShape->image->height = image->height;
		childShape->image->width = image->width;
		childShape->name = targetChild->id;
		childShape->image->shapes = targetChild;

		addChild(childShape); // Create parent-child link
	}

	// Clear dublicate data
	image = nullptr;

	// Destroy shapel chain as each child would continue it
	for(auto& it : children)
	{
		it->image->shapes->next = NULL;
	}
}