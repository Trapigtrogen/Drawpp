#include <matrix3.hpp>
#include <vector2.hpp>
#include <vector3.hpp>
#include <cmath>
#include <limits>

Matrix3::Matrix3()
: values{1,0,0,0,1,0,0,0,1}{}

Matrix3::Matrix3(float v)
: values{v,v,v,v,v,v,v,v,v} {}

Matrix3::Matrix3(float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22)
        : values{m00,m01,m02,
                 m10,m11,m12,
                 m20,m21,m22}{}

Matrix3 Matrix3::hproduct(const Matrix3& mat1, const Matrix3& mat2)
{
    Matrix3 r;
    for(unsigned int i = 0; i < 9; ++i)
        r[i] = mat1[i]*mat2[i];
    return r;
}

Matrix3 Matrix3::hdivision(const Matrix3& mat1, const Matrix3& mat2)
{
    Matrix3 r;
    for(unsigned int i = 0; i < 9; ++i)
        r[i] = mat1[i]/mat2[i];
    return r;
}

Matrix3 Matrix3::identity()
{
    return Matrix3();
}

Matrix3 Matrix3::identity(float v)
{
    return Matrix3(v,0,0,0,v,0,0,0,v);
}

Matrix3 Matrix3::rotation(float angle)
{
    return Matrix3(std::cos(angle),
                   -std::sin(angle),
                   0,
                   std::sin(angle),
                   std::cos(angle),
                   0,0,0,1);
}

Matrix3 Matrix3::translation(const Vector2& t)
{
    return Matrix3(1,0,t.x,0,1,t.y,0,0,1);
}

Matrix3 Matrix3::scaling(const Vector2& s)
{
    return Matrix3(s.x,0,0,0,s.y,0,0,0,1);
}

Matrix3 Matrix3::scaling(const Vector3& s)
{
    return Matrix3(s.x,0,0,0,s.y,0,0,0,s.z);
}

Matrix3 Matrix3::rotate(float angle) const
{
    return *this * Matrix3::rotation(angle);
}

Matrix3 Matrix3::translate(const Vector2& t) const
{
    return *this * Matrix3::translation(t);
}

Matrix3 Matrix3::scale(const Vector2& s) const
{
    return *this * Matrix3::scaling(s);
}

float Matrix3::det() const
{
    return (*this)(0,0)*(*this)(1,1)*(*this)(2,2) + 
           (*this)(0,1)*(*this)(1,2)*(*this)(2,0) + 
           (*this)(0,2)*(*this)(1,0)*(*this)(2,1) -
           (*this)(0,0)*(*this)(1,2)*(*this)(2,1) -
           (*this)(0,1)*(*this)(1,0)*(*this)(2,2) -
           (*this)(0,2)*(*this)(1,1)*(*this)(2,0); 
}

Matrix3 Matrix3::transposed() const
{
    return Matrix3((*this)(0,0), (*this)(1,0), (*this)(2,0),
                   (*this)(0,1), (*this)(1,1), (*this)(2,1),
                   (*this)(0,2), (*this)(1,2), (*this)(2,2));
}

void Matrix3::transpose()
{
    *this = transposed();
}

Matrix3 Matrix3::inverse() const
{
    float d = 1/det();
    return inverse(d);
}

Matrix3 Matrix3::inverse(float d) const
{
    return Matrix3(((*this)(1,1)*(*this)(2,2) - (*this)(1,2)*(*this)(2,1))/d,
                   ((*this)(0,2)*(*this)(2,1) - (*this)(0,1)*(*this)(2,2))/d,
                   ((*this)(0,1)*(*this)(1,2) - (*this)(0,2)*(*this)(1,1))/d,

                   ((*this)(1,2)*(*this)(2,0) - (*this)(1,0)*(*this)(2,2))/d,
                   ((*this)(0,0)*(*this)(2,2) - (*this)(0,2)*(*this)(2,0))/d,
                   ((*this)(0,2)*(*this)(1,0) - (*this)(0,0)*(*this)(1,2))/d,

                   ((*this)(1,0)*(*this)(2,1) - (*this)(1,1)*(*this)(2,0))/d,
                   ((*this)(0,1)*(*this)(2,0) - (*this)(0,0)*(*this)(2,1))/d,
                   ((*this)(0,0)*(*this)(1,1) - (*this)(0,1)*(*this)(1,0))/d);
}

bool Matrix3::invert()
{
    float d = 1/det();

    if(d <= std::numeric_limits<float>::epsilon())
    {
        return false;
    }
    else
    {
        *this = inverse(d);
        return true;
    }
}

Matrix3 Matrix3::operator+(const Matrix3& mat) const
{
    Matrix3 m;
    for(unsigned int i = 0; i < 9; ++i)
        m[i] = mat[i]+values[i];
    return m;
}

Matrix3 Matrix3::operator+(float n) const
{
    Matrix3 m;
    for(unsigned int i = 0; i < 9; ++i)
        m[i] = n+values[i];
    return m;
}

Matrix3 Matrix3::operator-(const Matrix3& mat) const
{
    Matrix3 m;
    for(unsigned int i = 0; i < 9; ++i)
        m[i] = values[i]-mat[i];
    return m;
}

Matrix3 Matrix3::operator-(float n) const
{
    Matrix3 m;
    for(unsigned int i = 0; i < 9; ++i)
        m[i] = values[i]-n;
    return m;
}

Matrix3 Matrix3::operator-() const
{
    Matrix3 m;
    for(unsigned int i = 0; i < 9; ++i)
        m[i] = -values[i];
    return m;
}

Matrix3 Matrix3::operator* (const Matrix3& mat) const
{
    return Matrix3(
        ((*this)(0,0)*mat(0,0)) + ((*this)(0,1)*mat(1,0)) + ((*this)(0,2)*mat(2,0)),
        ((*this)(0,0)*mat(0,1)) + ((*this)(0,1)*mat(1,1)) + ((*this)(0,2)*mat(2,1)),
        ((*this)(0,0)*mat(0,2)) + ((*this)(0,1)*mat(1,2)) + ((*this)(0,2)*mat(2,2)),

        ((*this)(1,0)*mat(0,0)) + ((*this)(1,1)*mat(1,0)) + ((*this)(1,2)*mat(2,0)),
        ((*this)(1,0)*mat(0,1)) + ((*this)(1,1)*mat(1,1)) + ((*this)(1,2)*mat(2,1)),
        ((*this)(1,0)*mat(0,2)) + ((*this)(1,1)*mat(1,2)) + ((*this)(1,2)*mat(2,2)),

        ((*this)(2,0)*mat(0,0)) + ((*this)(2,1)*mat(1,0)) + ((*this)(2,2)*mat(2,0)),
        ((*this)(2,0)*mat(0,1)) + ((*this)(2,1)*mat(1,1)) + ((*this)(2,2)*mat(2,1)),
        ((*this)(2,0)*mat(0,2)) + ((*this)(2,1)*mat(1,2)) + ((*this)(2,2)*mat(2,2))
    );
}

Vector2 Matrix3::operator*(const Vector2& vec) const
{
    return Vector2((*this)(0,0)*vec.x+(*this)(0,1)*vec.y+(*this)(0,2),
                   (*this)(1,0)*vec.x+(*this)(1,1)*vec.y+(*this)(1,2));
}

Vector3 Matrix3::operator*(const Vector3& vec) const
{
    return Vector3((*this)(0,0)*vec.x+(*this)(0,1)*vec.y+(*this)(0,2)*vec.z,
                   (*this)(1,0)*vec.x+(*this)(1,1)*vec.y+(*this)(1,2)*vec.z,
                   (*this)(2,0)*vec.x+(*this)(2,1)*vec.y+(*this)(2,2)*vec.z);
}

Matrix3 Matrix3::operator*(float n) const
{
    Matrix3 m;
    for(unsigned int i = 0; i < 9; ++i)
        m[i] = values[i]*n;
    return m;
}

Matrix3 Matrix3::operator/(float n) const
{
    Matrix3 m;
    for(unsigned int i = 0; i < 9; ++i)
        m[i] = values[i]/n;
    return m;
}

Matrix3& Matrix3::operator+=(const Matrix3& mat)
{
    return *this = *this+mat;
}

Matrix3& Matrix3::operator+=(float n)
{
    return *this = *this+n;
}

Matrix3& Matrix3::operator-=(const Matrix3& mat)
{
    return *this = *this-mat;
}

Matrix3& Matrix3::operator-=(float n)
{
    return *this = *this-n;
}

Matrix3& Matrix3::operator*=(float n)
{
    return *this = *this*n;
}

Matrix3& Matrix3::operator*=(const Matrix3& mat)
{
    return *this = *this*mat;
}

Matrix3& Matrix3::operator/=(float n)
{
    return *this = *this/n;
}

bool Matrix3::operator==(const Matrix3& mat) const
{
    for(unsigned int i = 0; i < 9; ++i)
    {
        if(values[i] != mat[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix3::operator!=(const Matrix3& mat) const
{
    return !((*this) == mat);
}

float& Matrix3::operator[](unsigned int index)
{
    return values[index];
}

float Matrix3::operator[](unsigned int index) const
{
    return values[index];
}

float& Matrix3::operator()(unsigned int row, unsigned int col)
{
    return values[row*3 + col];
}

float Matrix3::operator()(unsigned int row, unsigned int col) const
{
    return values[row*3 + col];
}


Matrix3 operator*(float n, const Matrix3& m)
{
    return m*n;
}

Vector3 operator*(const Vector3& vec, const Matrix3& m)
{
    return m*vec;
}

Vector2 operator*(const Vector2& vec, const Matrix3& m)
{
    return m*vec;
}