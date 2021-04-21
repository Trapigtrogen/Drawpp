#include <path.hpp>

size_t Path::size() const
{
    return points.size();
}

DVector& Path::operator[](size_t index)
{
    return points[index];
}

const DVector& Path::operator[](size_t index) const
{
    return points[index];
}