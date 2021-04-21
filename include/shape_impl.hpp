#ifndef DPP_SHAPE_IMPL_H
#define DPP_SHAPE_IMPL_H

#include <vector>
#include <path.hpp>
#include <color.hpp>
#include <string>

class DShape;

///\private
struct DShape_impl
{
    DShape_impl() = default;
    DShape_impl(DShape_impl&&) = default;
    DShape_impl(const DShape_impl&);

    //internal func for loading shape info
    void impl_loadShape(const struct NSVGshape& shape);

    //load svg file into a shape hierarchy
	void loadSVG(const std::string& filename);

    Color strokeColor;
    float strokeWeight = 1.0f;
    bool visible = true;
    std::vector<Path> paths;
    std::vector<DShape> children;
    std::string name;
};

#endif