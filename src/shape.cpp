#include <shape.hpp>
#include <shape_impl.hpp>
#include <debug.hpp>
#include <algorithm>
#include <exception>

#pragma warning(push,1)

#define NANOSVG_ALL_COLOR_KEYWORDS	// Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION		// Expands implementation
#include <nanosvg.h>

#pragma warning(pop)

DShape_impl::DShape_impl(const DShape_impl& other)
{
    strokeColor = other.strokeColor;
    strokeWeight = other.strokeWeight;
    name = other.name;

    for(const Path& p : other.paths)
    {
        paths.push_back(p);
    }

    for(const DShape& c : other.children)
    {
        children.push_back(DShape(c));
    }
}

void DShape_impl::impl_loadShape(const NSVGshape& shape)
{
    strokeWeight = shape.strokeWidth;
    strokeColor = shape.stroke.color;
    reinterpret_cast<uint8_t*>(&strokeColor)[0] = 255/shape.opacity;
    name = std::string(shape.id);

    for(const NSVGpath* p = shape.paths; p != nullptr; p = p->next)
    {
        Path np;
        np.closed = p->closed;
        for(unsigned i = 0; i < p->npts*2-1; i+=2)
        {
            np.points.push_back({p->pts[i],p->pts[i+1]});
        }
        paths.emplace_back(std::move(np));
    }
}

void DShape_impl::loadSVG(const std::string& filename)
{
    NSVGimage* image = nsvgParseFromFile(filename.c_str(), "px", 96);

    if(image == nullptr) 
	{
		dbg::error("Failed to load svg image: ", filename);
		return;
	}
	else if(image->shapes == nullptr) // Empty image should not be loaded

	{
		dbg::error("Image is found but it's empty. Loading has been cancelled"); 
		nsvgDelete(image);
		return;
	}

    const NSVGshape* shape = image->shapes;

    impl_loadShape(*shape);

	for(shape = shape->next; shape != nullptr; shape = shape->next) 
	{
        DShape ns;
        ns.impl = std::shared_ptr<DShape_impl>(new DShape_impl);

        ns.impl->impl_loadShape(*shape);

		children.emplace_back(std::move(ns));
	}
	nsvgDelete(image);
}

DShape::DShape() : impl(new DShape_impl){}

DShape::DShape(const DShape& other)
{
    impl = std::shared_ptr<DShape_impl>(new DShape_impl(*other.impl));
}

DShape& DShape::operator=(const DShape& other)
{
    impl = std::shared_ptr<DShape_impl>(new DShape_impl(*other.impl));
    return *this;
}

int DShape::addChild(DShape& other)
{
    DShape s;
    s.impl = other.impl;

    impl->children.emplace_back(std::move(s));
    return impl->children.size()-1;
}

bool DShape::removeChild(int index)
{
    if(index < 0 || index >= impl->children.size())
    {
        return false;
    }

    impl->children.erase(impl->children.begin()+index);
    return true;
}

DShape& DShape::getChild(int index)
{
    return impl->children[index];
}

const DShape& DShape::getChild(int index) const noexcept(false)
{
    if(index < 0 || index >= impl->children.size())
    {
        throw std::out_of_range("Child index out or range");
    }
    return impl->children[index];
}

int DShape::findChild(const std::string& id) const
{
    for(size_t i = 0; i < impl->children.size(); ++i)
    {
        if(impl->children[i].impl->name == id)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int DShape::getChildCount() const
{
    return static_cast<int>(impl->children.size());
}

int DShape::getPathCount() const
{
    return static_cast<int>(impl->paths.size());
}

Path& DShape::operator[](size_t index)
{
    return impl->paths[index];
}

const Path& DShape::operator[](size_t index) const
{
    return impl->paths[index];
}

void DShape::setVisible(bool visible)
{
    impl->visible = visible;
}

bool DShape::isVisible() const
{
    return impl->visible;
}

void DShape::moveChild(int index, int newIndex)
{
    if(index == newIndex)
    {
        return;
    }

    if(newIndex > impl->children.size())
    {
        newIndex = impl->children.size()-1;
    }
    else if(newIndex < 0)
    {
        newIndex = 0;
    }

    if(index > newIndex)
    {
        std::rotate(impl->children.rend() - index - 1,
                    impl->children.rend() - index,
                    impl->children.rend() - newIndex);
    }
    else
    {
        std::rotate(impl->children.begin() + index + 1,
                    impl->children.begin() + index,
                    impl->children.begin() + newIndex);
    }
}

std::string& DShape::name()
{
    return impl->name;
}

DShape DShape::loadShape(const std::string& filename)
{
    std::shared_ptr<DShape_impl> impl = 
    std::shared_ptr<DShape_impl>(new DShape_impl);
    impl->loadSVG(filename);

    DShape s;
    s.impl = std::move(impl);
    return s;
}