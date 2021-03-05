#ifndef DPP_DSHAPE_H
#define DPP_DSHAPE_H

#include <string>
#include <vector>

/// Shape objects are vector graphics that have GameObject like parent-child hierarcy. Also includes SVG loader
class DShape
{
public:
	///\brief create empty Shape
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

	struct CombinedImage
	{
		std::vector<float*> vectors;
		std::vector<int> fills;
		std::vector<int> strokes;
	};

	///\brief Load SVG image as shape
	static DShape loadShape(std::string filename);

	static DShape createShape();

	///\brief Create shape from given primitive
	///
	/// Type is one of the following: POINT, LINE, TRIANGLE, QUAD, RECT, ELLIPSE, ARC, BOX, SPHERE
	static DShape createShape(DShape::ShapeType type);

	//static DShape createShape(DShape::ShapeType type, float[] p); // DEBUG: From processing reference

	///\brief Add a child to this shape
	///
	/// The child will move, rotate anmd scale with this object
	void addChild(DShape* child);

	///\brief Add a child to this shape and give it z-index \p _idx
	///
	/// The child will move, rotate anmd scale with this object. 
	/// Z-index will affect the drawing order. Shape with higher index will be drawn on top
	void addChild(DShape* child, int _idx);

	///\brief remove the child from this shape
	void removeChild(DShape* child);


	///\brief Get child by index
	/// 
	/// The index is the order that children are added starting from 0
	///\returns Pointer to the child object with given index
	DShape* getChild(int idx);

	///\brief Get child by index
	/// 
	/// The index is the order that children are added starting from 0
	///\returns Pointer to the child object with given name
	DShape* getChild(std::string);

	///\brief Get the number of attached children
	///
	///\returns the number of \p children
	size_t getChildCount();

	///\brief Get this hape's parent
	/// 
	///\returns Pointer to the parent of this shape
	DShape* getParent();


	///\brief Set the shape's visibility
	///
	/// Changes if the shape is drawn or not
	void setVisible(bool visibility) { visible = visibility; };

	///\brief Get the shape's visibility
	///
	/// See if the shape is drawn or not
	///\returns \p visible
	bool isVisible() { return visible; };

	// Drawable objects are in image->shapes. If image == NULL go through children's images
	///\brief the image loaded with nanoSVG
	struct NSVGimage* image;

	///\brief The name of the shape
	///
	/// By default this is empty. You can change it yourself.
	/// When SVG file is loaded the name of the path is copied here.
	std::string name;
private:
	bool visible = true;

	int renderIdx = 0;

	DShape* parent = nullptr;
	std::vector<DShape*> children;

	// internal parent handling
	void addParent(DShape* _parent);
	void removeParent();

	// internal svg loader
	void loadSVG(std::string filename);
};

#endif