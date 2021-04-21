#ifndef DPP_PATH_H
#define DPP_PATH_H

#include <vector>
#include <vector3.hpp>

class Path
{
    friend struct DShape_impl;
    friend class DGraphics;

public:

    ///\brief Get the number of vertices in the path
    size_t size() const;


    ///\brief Get a reference to a vertex at \p index
    DVector& operator[](size_t index);


    ///\copydoc operator[](size_t)
    const DVector& operator[](size_t index) const;

private:

    std::vector<DVector> points;
    bool closed = false;
};

#endif