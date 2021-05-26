#ifndef DPP_PATH_H
#define DPP_PATH_H

#include <vector>
#include <vector2.hpp>

class Path
{
    friend struct DShape_impl;
    friend class DGraphics;

public:

    ///\brief Get the number of vertices in the path
    std::size_t size() const;


    ///\brief Get a reference to a vertex at \p index
    Vector2& operator[](std::size_t index);


    ///\copydoc operator[](size_t)
    const Vector2& operator[](std::size_t index) const;

private:

    std::vector<Vector2> points;
    bool closed = false;
};

#endif