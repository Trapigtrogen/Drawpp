#include <vector3.hpp>
#include <cmath>
#include <application.hpp>

DVector::DVector():x(0),y(0),z(0){}
DVector::DVector(float n):x(n),y(n),z(n){}
DVector::DVector(float x, float y):x(x),y(y),z(0){}
DVector::DVector(float x, float y, float z):x(x),y(y),z(z){}

DVector& DVector::set(float x, float y, float z)
{
    DVector::x = x;
    DVector::y = y;
    DVector::z = z;
    return *this;
}

DVector& DVector::set(float x, float y)
{
    DVector::x = x;
    DVector::y = y;
    DVector::z = 0;
    return *this;
}

DVector& DVector::set(const DVector& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

DVector DVector::random2D()
{
    return random2D(Application::GetInstance()->random);
}

DVector DVector::random2D(Random& gen)
{
    DVector res;
    return random2D(res,Application::GetInstance()->random);
}

DVector& DVector::random2D(DVector& target)
{
    return random2D(target,Application::GetInstance()->random);
}

///TODO: replace high with 2pi constant once it exists
DVector& DVector::random2D(DVector& target, Random& gen)
{
    float angle = gen.random() * 6.283185307179f;

    return target.set(fromAngle(angle));
}

DVector DVector::random3D()
{
    return random3D(Application::GetInstance()->random);
}

DVector DVector::random3D(Random& gen)
{
    DVector res;
    return random3D(res,Application::GetInstance()->random);
}

DVector& DVector::random3D(DVector& target)
{
    return random3D(target,Application::GetInstance()->random);
}

///TODO: replace high with 2pi constant once it exists
DVector& DVector::random3D(DVector& target, Random& gen)
{
    float angle = gen.randomf(0.0f,6.283185307179f);
    float _z = gen.randomf(-1.0f, 1.0f);
    float p = std::sqrt(1 - _z*_z);

    return target.set(std::cos(angle) * p, std::sin(angle) * p, _z);
}

DVector DVector::fromAngle(float angle)
{
    return DVector(std::cos(angle),std::sin(angle));
}

DVector& DVector::fromAngle(float angle, DVector& target)
{
    return target.set(std::cos(angle),std::sin(angle));
}

DVector DVector::copy() const
{
    return *this;
}

float DVector::mag() const 
{ 
    return std::sqrt(x*x+y*y+z*z);
}

float DVector::magSq() const 
{
    return DVector::dot(*this,*this);
}

DVector& DVector::add(const DVector& v1)
{
    x += v1.x;
    y += v1.y;
    z += v1.z;
    return *this;
}

DVector& DVector::add(float x, float y)
{
    DVector::x += x;
    DVector::y += y;
    return *this;
}

DVector& DVector::add(float x, float y, float z)
{
    DVector::x += x;
    DVector::y += y;
    DVector::z += z;
    return *this;
}

DVector DVector::add(const DVector& v1, const DVector& v2)
{
    return DVector(v1).add(v2);
}

DVector& DVector::add(const DVector& v1, const DVector& v2, DVector& target)
{
    return target.set(v1).add(v2);
}

DVector& DVector::sub(const DVector& v1)
{
    x -= v1.x;
    y -= v1.y;
    z -= v1.z;
    return *this;
}

DVector& DVector::sub(float x, float y)
{
    DVector::x -= x;
    DVector::y -= y;
    return *this;
}

DVector& DVector::sub(float x, float y, float z)
{
    DVector::x -= x;
    DVector::y -= y;
    DVector::z -= z;
    return *this;
}

DVector DVector::sub(const DVector& v1, const DVector& v2)
{
    return DVector(v1).sub(v2);
}

DVector& DVector::sub(const DVector& v1, const DVector& v2, DVector& target)
{
    return target.set(v1).sub(v2);
}

DVector& DVector::mult(float n)
{
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

DVector DVector::mult(const DVector& v1, float n)
{
    return DVector(v1).mult(n);
}

DVector& DVector::mult(const DVector& v1, float n, DVector& target)
{
    return target.set(v1).mult(n);
}

DVector& DVector::div(float n)
{
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

DVector DVector::div(const DVector& v1, float n)
{
    return DVector(v1).div(n);
}

DVector& DVector::div(const DVector& v1, float n, DVector& target)
{
    return target.set(v1).div(n);
}

float DVector::dist(const DVector& v1) const
{
    return dist(*this,v1);
}

float DVector::dist(const DVector& v1, const DVector& v2)
{
    float xd = v1.x-v2.x;
    float yd = v1.y-v2.y;
    float zd = v1.z-v2.z;
    return std::sqrt(xd*xd + yd*yd + zd*zd);
}

float DVector::dot(const DVector& v1) const
{
    return dot(*this,v1);
}

float DVector::dot(float x, float y, float z) const
{
    return DVector::x*x+DVector::y*y+DVector::z*z;
}

float DVector::dot(const DVector& v1, const DVector& v2) 
{
     return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z; 
}

DVector DVector::cross(const DVector& v1) const
{
    return cross(*this,v1);
}

DVector& DVector::cross(const DVector& v1, DVector& target) const
{
    return cross(*this,v1,target);
}

DVector& DVector::cross(const DVector& v1, const DVector& v2, DVector& target)
{
    return target.set(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x* v2.z, v1.x*v2.y - v1.y*v2.x);
}

DVector DVector::cross(const DVector& v1, const DVector& v2) 
{ 
    return DVector(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x* v2.z, v1.x*v2.y - v1.y*v2.x);
}

DVector& DVector::normalize()
{ 
    float m = mag();
    x /= m;
    y /= m;
    z /= m;
    return *this;
}

DVector& DVector::normalize(DVector& target) const
{
    return target.set(*this).normalize();
}

DVector DVector::normalized() const
{
    DVector r(*this);
    float m = mag();
    r.x /= m;
    r.y /= m;
    r.z /= m;
    return r;
}

DVector& DVector::limit(float max)
{
    float m = mag();

    if(m > max)
    {
        (void)mult(max / m);
    }

    return *this;
}

DVector& DVector::setMag(float len)
{
    return mult(len / mag());
}

DVector& DVector::setMag(DVector& target, float len) const
{
    return target.set(*this).setMag(len);
}

float DVector::heading() const
{
    return std::atan2(x,y);
}

DVector& DVector::rotate(float theta)
{
    float _x = x, _y = y;
    
    x = _x * std::cos(theta) - _y * std::sin(theta);
    y = _x * std::sin(theta) + _y * std::cos(theta);

    return *this;
}

DVector& DVector::lerp(const DVector& v1, float t)
{
    x = x + (v1.x - x) * t;
    y = y + (v1.y - y) * t;
    z = z + (v1.z - z) * t;
    return *this;
}

DVector& DVector::lerp(float x, float y, float z, float t)
{
    DVector::x = DVector::x + (x - DVector::x) * t;
    DVector::y = DVector::y + (y - DVector::y) * t;
    DVector::z = DVector::z + (z - DVector::z) * t;
    return *this;
}

DVector DVector::lerp(const DVector& v1, const DVector& v2, float t)
{
    return DVector(v1).lerp(v2,t);
}

float DVector::angleBetween(const DVector& v1, const DVector& v2)
{
    return std::atan2(dot(v1,v2),v1.x * v2.y - v1.y * v2.x);
}

std::vector<float> DVector::array() const
{
    return std::vector<float>({x,y,z});
}

DVector DVector::operator+(const DVector& vec) const { return DVector(x+vec.x,y+vec.y,z+vec.z); }
DVector DVector::operator-(const DVector& vec) const { return DVector(x-vec.x,y-vec.y,z-vec.z); }
DVector DVector::operator-()                   const { return DVector(-x,-y,-z); }
DVector DVector::operator*(float n)            const { return DVector(x*n,y*n,z*n); }
DVector DVector::operator/(float n)            const { return DVector(x/n,y/n,z/n); }

DVector& DVector::operator= (const DVector& vec) { return set(vec); }
DVector& DVector::operator+=(const DVector& vec) { return add(vec); }
DVector& DVector::operator-=(const DVector& vec) { return sub(vec); }
DVector& DVector::operator*=(float n)            { return mult(n);  }
DVector& DVector::operator*=(const DVector& vec) { x *= vec.x;y *= vec.y;z *= vec.z; return *this; }
DVector& DVector::operator/=(float n)            { return div(n);   }
DVector& DVector::operator/=(const DVector& vec) { x /= vec.x;y /= vec.y;z /= vec.z; return *this; }

bool DVector::operator==(const DVector& vec) const { return x==vec.x&&y==vec.y&&z==vec.z; }
bool DVector::operator!=(const DVector& vec) const { return !(*this==vec); }
bool DVector::operator<(const DVector& vec)  const { return mag()<vec.mag(); }
bool DVector::operator>(const DVector& vec)  const { return mag()>vec.mag(); }
bool DVector::operator<=(const DVector& vec) const { return mag()<=vec.mag(); }
bool DVector::operator>=(const DVector& vec) const { return mag()>=vec.mag(); }

float& DVector::operator[](size_t index) { return static_cast<float*>(&x)[index]; }
float  DVector::operator[](size_t index) const { return static_cast<const float*>(&x)[index]; }

DVector operator*(float n, const DVector& vec) { return vec*n; }