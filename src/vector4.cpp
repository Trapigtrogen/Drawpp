#include <vector4.hpp>
#include <application.hpp>
#include <random.hpp>
#include <vectormath.hpp>
#include <cmath>

Vector4::Vector4() = default;

Vector4::Vector4(float v)
: x(v),y(v),z(v),w(v) {}

Vector4::Vector4(float _x, float _y, float _z, float _w)
: x(_x),y(_y),z(_z),w(_w) {}


Vector4 Vector4::random()
{
    return random(Application::GetInstance()->random);
}

Vector4 Vector4::random(Random& gen)
{
    return normalize(Vector4(
        gen.randomFloat(-1.0f, 1.0f),
        gen.randomFloat(-1.0f, 1.0f),
        gen.randomFloat(-1.0f, 1.0f),
        gen.randomFloat(-1.0f, 1.0f)
    ));
}


float Vector4::mag() const
{
    return std::sqrt(magSq());
}

float Vector4::magSq() const
{
    return x*x+y*y+z*z+w*w;
}

Vector4 Vector4::operator+(const Vector4& vec) const
{
    return Vector4(x+vec.x,y+vec.y,z+vec.z,w+vec.w);
}

Vector4 Vector4::operator-(const Vector4& vec) const
{
    return Vector4(x-vec.x,y-vec.y,z-vec.z,w-vec.w);
}

Vector4 Vector4::operator-()                   const
{
    return Vector4(-x,-y,-z,-w);
}

Vector4 Vector4::operator*(float n)            const
{
    return Vector4(x*n,y*n,z*n,w*n);
}

Vector4 Vector4::operator*(const Vector4& vec) const
{
    return Vector4(x*vec.x,y*vec.y,z*vec.z,w*vec.w);
}

Vector4 Vector4::operator/(float n)            const
{
    return Vector4(x/n,y/n,z/n,w/n);
}

Vector4 Vector4::operator/(const Vector4& vec) const
{
    return Vector4(x/vec.x,y/vec.y,z/vec.z,w/vec.w);
}

Vector4& Vector4::operator=(const Vector4& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
    return *this;
}

Vector4& Vector4::operator+=(const Vector4& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
    return *this;
}

Vector4& Vector4::operator*=(float n)
{
    x *= n;
    y *= n;
    z *= n;
    w *= n;
    return *this;
}

Vector4& Vector4::operator*=(const Vector4& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    w *= vec.w;
    return *this;
}

Vector4& Vector4::operator/=(float n)
{
    x /= n;
    y /= n;
    z /= n;
    w /= n;
    return *this;
}

Vector4& Vector4::operator/=(const Vector4& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    w /= vec.w;
    return *this;
}

bool Vector4::operator==(const Vector4& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

bool Vector4::operator!=(const Vector4& vec) const
{
    return !(*this == vec);
}

bool Vector4::operator<(const Vector4& vec)  const
{
    return magSq()<vec.magSq();
}

bool Vector4::operator>(const Vector4& vec)  const
{
    return magSq()>vec.magSq();
}

bool Vector4::operator<=(const Vector4& vec) const
{
    return magSq()<=vec.magSq();
}

bool Vector4::operator>=(const Vector4& vec) const
{
    return magSq()>=vec.magSq();
}

float& Vector4::operator[](unsigned int index)
{
    return (&x)[index];
}

float Vector4::operator[](unsigned int index) const
{
    return (&x)[index];
}

Vector4 operator*(float n, const Vector4& vec)
{
    return vec*n;
}