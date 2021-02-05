#include <shape.hpp>
#include <debug.hpp>

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
	data = new char[0];
}

DShape::DShape(const DShape& other)
{
	delete[] data;
	data = new char[strlen(other.data)];
	std::copy(other.data, other.data + strlen(other.data), data);
	visible = other.visible;
	parent = other.parent;
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
	parent = other.parent;
	for(auto& it : other.children) 
	{
		addChild(it);
		other.removeChild(it);
	}

	other.data = nullptr;
	other.visible = 0;
	other.parent = nullptr;
}

DShape& DShape::operator=(DShape& other)
{
	if(this != &other) 
	{
		delete[] data;

		data = other.data;
		visible = other.visible;
		parent = other.parent;
		parent = other.parent;
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
		parent = other.parent;
		for(auto& it : other.children) {
			addChild(it);
			other.removeChild(it);
		}

		other.data = nullptr;
		other.visible = 0;
		other.parent = nullptr;
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

	const char* str = "vectorigraffaa ja sillee";
	size_t strLen = std::strlen(str);
	memcpy(tempShape.data, str, strLen + 1);

	return tempShape; // DEBUG TEMP
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

void DShape::LoadSVG(std::string filename)
{

}