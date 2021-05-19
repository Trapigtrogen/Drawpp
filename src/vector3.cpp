#include <vector3.hpp>
#include <application.hpp>
#include <random.hpp>
#include <vectormath.hpp>
#include <cmath>

Vector3::Vector3() = default;

Vector3::Vector3(float v)
: x(v),y(v),z(v) {}

Vector3::Vector3(float _x, float _y, float _z)
: x(_x),y(_y),z(_z) {}


Vector3 Vector3::random()
{
    return random(Application::GetInstance()->random);
}

Vector3 Vector3::random(Random& gen)
{
    return normalize(Vector3(
        gen.randomFloat(-1.0f, 1.0f),
        gen.randomFloat(-1.0f, 1.0f),
        gen.randomFloat(-1.0f, 1.0f)
    ));
}


float Vector3::mag() const
{
    return std::sqrt(magSq());
}

float Vector3::magSq() const
{
    return x*x+y*y+z*z;
}

Vector3 Vector3::operator+(const Vector3& vec) const
{
    return Vector3(x+vec.x,y+vec.y,z+vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
    return Vector3(x-vec.x,y-vec.y,z-vec.z);
}

Vector3 Vector3::operator-()                   const
{
    return Vector3(-x,-y,-z);
}

Vector3 Vector3::operator*(float n)            const
{
    return Vector3(x*n,y*n,z*n);
}

Vector3 Vector3::operator*(const Vector3& vec) const
{
    return Vector3(x*vec.x,y*vec.y,z*vec.z);
}

Vector3 Vector3::operator/(float n)            const
{
    return Vector3(x/n,y/n,z/n);
}

Vector3 Vector3::operator/(const Vector3& vec) const
{
    return Vector3(x/vec.x,y/vec.y,z/vec.z);
}

Vector3& Vector3::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector3& Vector3::operator*=(float n)
{
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Vector3& Vector3::operator/=(float n)
{
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

bool Vector3::operator==(const Vector3& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector3::operator!=(const Vector3& vec) const
{
    return !(*this == vec);
}

bool Vector3::operator<(const Vector3& vec)  const
{
    return magSq()<vec.magSq();
}

bool Vector3::operator>(const Vector3& vec)  const
{
    return magSq()>vec.magSq();
}

bool Vector3::operator<=(const Vector3& vec) const
{
    return magSq()<=vec.magSq();
}

bool Vector3::operator>=(const Vector3& vec) const
{
    return magSq()>=vec.magSq();
}

float& Vector3::operator[](unsigned int index)
{
    return (&x)[index];
}

float Vector3::operator[](unsigned int index) const
{
    return (&x)[index];
}

Vector3 operator*(float n, const Vector3& vec)
{
    return vec*n;
}