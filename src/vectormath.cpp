#include <vectormath.hpp>
#include <cmath>


float dot(const Vector2& a, const Vector2& b)
{
    return a.x*b.x+a.y*b.y;
}

float dot(const Vector3& a, const Vector3& b)
{
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

float dot(const Vector4& a, const Vector4& b)
{
    return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
}


float cross(const Vector2& a, const Vector2& b)
{
    return a.x * b.y - a.y * b.x;
}

Vector3 cross(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x* b.z, a.x*b.y - a.y*b.x);
}


float angleBetween(const Vector2& a, const Vector2& b)
{
    //return std::atan2(dot(a,b),cross(a,b));
    return std::acos(dot(a,b)/(a.mag()*b.mag()));
}

float angleBetween(const Vector3& a, const Vector3& b)
{
    return std::acos(dot(a,b)/(a.mag()*b.mag()));
}

float angleBetween(const Vector4& a, const Vector4& b)
{
    return std::acos(dot(a,b)/(a.mag()*b.mag()));
}


Vector2 lerp(const Vector2& a, const Vector2& b, float t)
{
    return Vector2(a.x + (b.x - a.x) * t,
                   a.y + (b.y - a.y) * t);
}

Vector3 lerp(const Vector3& a, const Vector3& b, float t)
{
    return Vector3(a.x + (b.x - a.x) * t,
                   a.y + (b.y - a.y) * t,
                   a.z + (b.z - a.z) * t);
}

Vector4 lerp(const Vector4& a, const Vector4& b, float t)
{
    return Vector4(a.x + (b.x - a.x) * t,
                   a.y + (b.y - a.y) * t,
                   a.z + (b.z - a.z) * t,
                   a.w + (b.w - a.w) * t);
}


Vector2 normalize(const Vector2& vec)
{
    float l = vec.mag();
    return Vector2(vec.x/l,vec.y/l);
}

Vector3 normalize(const Vector3& vec)
{
    float l = vec.mag();
    return Vector3(vec.x/l,vec.y/l,vec.z/l);
}

Vector4 normalize(const Vector4& vec)
{
    float l = vec.mag();
    return Vector4(vec.x/l,vec.y/l,vec.z/l,vec.w/l);
}


Vector2 setMag(const Vector2& vec, float m)
{
    return vec * (m/vec.mag());
}

Vector3 setMag(const Vector3& vec, float m)
{
    return vec * (m/vec.mag());
}

Vector4 setMag(const Vector4& vec, float m)
{
    return vec * (m/vec.mag());
}


Vector2 limit(const Vector2& vec, float m)
{
    float mg = vec.mag();

    if(mg > m)
    {
        return vec * (m/vec.mag());
    }

    return vec;
}

Vector3 limit(const Vector3& vec, float m)
{
    float mg = vec.mag();

    if(mg > m)
    {
        return vec * (m/vec.mag());
    }

    return vec;
}

Vector4 limit(const Vector4& vec, float m)
{
    float mg = vec.mag();

    if(mg > m)
    {
        return vec * (m/vec.mag());
    }

    return vec;
}


Vector2 abs(const Vector2& vec)
{
    return Vector2(std::abs(vec.x),std::abs(vec.y));
}

Vector3 abs(const Vector3& vec)
{
    return Vector3(std::abs(vec.x),std::abs(vec.y),std::abs(vec.z));
}

Vector4 abs(const Vector4& vec)
{
    return Vector4(std::abs(vec.x),std::abs(vec.y),std::abs(vec.z),std::abs(vec.w));
}
