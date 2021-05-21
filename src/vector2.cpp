#include <vector2.hpp>
#include <random.hpp>
#include <application.hpp>
#include <constants.hpp>
#include <cmath>


Vector2::Vector2() = default;

Vector2::Vector2(float v) 
: x(v),y(v) {}

Vector2::Vector2(float _x, float _y) 
: x(_x),y(_y) {}


Vector2 Vector2::random()
{
    return random(Application::GetInstance()->random);
}

Vector2 Vector2::random(Random& gen)
{
    return fromAngle(gen.randomFloat01() * TWO_PI);
}

Vector2 Vector2::fromAngle(float angle)
{
    return Vector2(std::cos(angle),std::sin(angle));
}


float Vector2::mag() const
{
    return std::sqrt(magSq());
}

float Vector2::magSq() const
{
    return x*x+y*y;
}

float Vector2::heading() const
{
    return std::atan2(x,y);
}

Vector2 Vector2::rotate(float angle) const
{
    return Vector2(x * std::cos(angle) - y * std::sin(angle),
                   x * std::sin(angle) + y * std::cos(angle));

}


Vector2 Vector2::operator+(const Vector2& vec) const
{
    return Vector2(x+vec.x,y+vec.y);
}

Vector2 Vector2::operator-(const Vector2& vec) const
{
    return Vector2(x-vec.x,y-vec.y);
}

Vector2 Vector2::operator-()                   const
{
    return Vector2(-x,-y);
}

Vector2 Vector2::operator*(float n)            const
{
    return Vector2(x*n,y*n);
}

Vector2 Vector2::operator*(const Vector2& vec) const
{
    return Vector2(x*vec.x,y*vec.y);
}

Vector2 Vector2::operator/(float n)            const
{
    return Vector2(x/n,y/n);
}

Vector2 Vector2::operator/(const Vector2& vec) const
{
    return Vector2(x/vec.x,y/vec.y);
}

Vector2& Vector2::operator=(const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2& Vector2::operator*=(float n)
{
    x *= n;
    y *= n;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
    x *= vec.x;
    y *= vec.y;
    return *this;
}

Vector2& Vector2::operator/=(float n)
{
    x /= n;
    y /= n;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
    x /= vec.x;
    y /= vec.y;
    return *this;
}

bool Vector2::operator==(const Vector2& vec) const
{
    return x == vec.x && y == vec.y;
}

bool Vector2::operator!=(const Vector2& vec) const
{
    return !(*this==vec);
}

bool Vector2::operator<(const Vector2& vec)  const
{
    return magSq()<vec.magSq();
}

bool Vector2::operator>(const Vector2& vec)  const
{
    return magSq()>vec.magSq(); 
}

bool Vector2::operator<=(const Vector2& vec) const
{
    return magSq()<=vec.magSq(); 
}

bool Vector2::operator>=(const Vector2& vec) const
{
    return magSq()>=vec.magSq(); 
}


float& Vector2::operator[](unsigned int index)
{
    return (&x)[index];
}

float Vector2::operator[](unsigned int index) const
{
    return (&x)[index];
}

Vector2 operator*(float n, const Vector2& vec)
{
    return vec*n;
}