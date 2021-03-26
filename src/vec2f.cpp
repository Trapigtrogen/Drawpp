#include <vec2f.hpp>
#include <cmath>

float vec2f::len()
{
    return std::sqrt(x*x+y*y);
}

float vec2f::dot(const vec2f& a, const vec2f& b)
{
    return a.x*b.x+a.y*b.y;
}

vec2f vec2f::operator*(float n) const
{
    return vec2f{x*n,y*n};
}

vec2f vec2f::operator/(float n) const
{
    return vec2f{x/n,y/n};
}

vec2f vec2f::operator+(const vec2f& other) const
{
    return vec2f{x+other.x,y+other.y};
}

vec2f vec2f::operator-(const vec2f& other) const
{
    return vec2f{x-other.x,y-other.y};
}

vec2f operator*(float n, const vec2f& other)
{
    return other * n;
}

vec2f operator/(float n, const vec2f& other)
{
    return other / n;
}