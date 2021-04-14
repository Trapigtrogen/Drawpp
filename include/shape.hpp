#ifndef DPP_DSHAPE_H
#define DPP_DSHAPE_H

#include <string>
#include <vector>
#include <memory>
#include <path.hpp>
#include <color.hpp>

struct DShape_impl;

///\brief A shape class to draw shapes
///
/// Currently supported features:
///     - Load SVG file into shape
///     - Tools for working with the child shape hierarchy
///
/// Not supported:
///     - Creating shapes manually
///     - Modifying existing shapes
class DShape
{
    friend struct DShape_impl;
    friend class DGraphics;
    friend class ::std::shared_ptr<DShape_impl>;

public:
	DShape();
	~DShape() = default;
	DShape(DShape&& other) = default;
	DShape(const DShape&);

	DShape& operator=(DShape&& other) = default;
    DShape& operator=(const DShape& other);


    ///\brief Add a child to this shape
    ///\returns The index of the new child in the child hierarchy, 
    ///or -1 on failure.
    int addChild(DShape& other);


    ///\brief Remove a child at \p index
    ///
    ///\returns true on success, false on failure
    bool removeChild(int index);


    ///\brief Get a reference to a child at \p index
    DShape& getChild(int index);


    ///\copydoc getChild(int index)
    const DShape& getChild(int index) const;


    ///\brief Get the index of first child with matching id
    ///\returns -1 if not found
	int findChild(const std::string& id) const;


    ///\brief Get the number of children
    int getChildCount() const;


    ///\brief Get the number of paths in this shape
    int getPathCount() const;


    ///\brief Get reference to a Path object at \p index
    Path& operator[](size_t index);


    ///\copydoc operator[](size_t)
    const Path& operator[](size_t index) const;


    ///\brief Set the shape's visibility
	///
	///Changes if the shape is drawn or not
    void setVisible(bool visible);


    ///\brief Get the shape's visibility
	///
	///See if the shape is drawn or not
    bool isVisible() const;


    ///\brief Move child at \p index to \p new_index in child hierarchy
    void moveChild(int index, int newIndex);


    ///\brief Get a reference to the name of this shape
    std::string& name();


    ///\brief Set the stroke weight for this shape
    void strokeWeight(float w);


    ///\brief Set the stroke color for this shape
    void stroke(Color rgba);


    ///\brief Load SVG image as shape
    static DShape loadShape(const std::string& filename);
    
private:

    std::shared_ptr<DShape_impl> impl;
};

#endif