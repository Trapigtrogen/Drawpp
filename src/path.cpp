#include <path.hpp>

std::size_t Path::size() const
{
    return points.size();
}

Vector2& Path::operator[](std::size_t index)
{
    return points[index];
}

const Vector2& Path::operator[](std::size_t index) const
{
    return points[index];
}