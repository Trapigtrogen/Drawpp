#include <matrix2.hpp>
#include <vector2.hpp>
#include <cmath>
#include <limits>

Matrix2::Matrix2()
: values{1,0,0,1}{}

Matrix2::Matrix2(float v)
: values{v,v,v,v} {}

Matrix2::Matrix2(float m00, float m01,
        float m10, float m11)
        : values{m00,m01,
                 m10,m11}{}

Matrix2 Matrix2::hproduct(const Matrix2& mat1, const Matrix2& mat2)
{
    Matrix2 r;
    for(unsigned int i = 0; i < 4; ++i)
        r[i] = mat1[i]*mat2[i];
    return r;
}

Matrix2 Matrix2::hdivision(const Matrix2& mat1, const Matrix2& mat2)
{
    Matrix2 r;
    for(unsigned int i = 0; i < 4; ++i)
        r[i] = mat1[i]/mat2[i];
    return r;
}

Matrix2 Matrix2::identity()
{
    return Matrix2();
}

Matrix2 Matrix2::identity(float v)
{
    return Matrix2(v,0,0,v);
}

Matrix2 Matrix2::rotation(float angle)
{
    return Matrix2(std::cos(angle),
                   -std::sin(angle),
                   std::sin(angle),
                   std::cos(angle));
}


Matrix2 Matrix2::scaling(const Vector2& s)
{
    return Matrix2(s.x,0,0,s.y);
}

Matrix2 Matrix2::rotate(float angle) const
{
    return *this * Matrix2::rotation(angle);
}

Matrix2 Matrix2::scale(const Vector2& s) const
{
    return *this * Matrix2::scaling(s);
}

float Matrix2::det() const
{
    return values[0]*values[3] - values[1]*values[2];
}

Matrix2 Matrix2::transposed() const
{
    return Matrix2((*this)(0,0), (*this)(1,0),
                   (*this)(0,1), (*this)(1,1));
}

void Matrix2::transpose()
{
    *this = transposed();
}

Matrix2 Matrix2::inverse() const
{
    float d = 1/det();
    return inverse(d);
}

Matrix2 Matrix2::inverse(float d) const
{
    return Matrix2(values[3]/d,-values[1]/d,-values[2]/d,values[0]/d);
}

bool Matrix2::invert()
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

Matrix2 Matrix2::operator+(const Matrix2& mat) const
{
    Matrix2 m;
    for(unsigned int i = 0; i < 4; ++i)
        m[i] = mat[i]+values[i];
    return m;
}

Matrix2 Matrix2::operator+(float n) const
{
    Matrix2 m;
    for(unsigned int i = 0; i < 4; ++i)
        m[i] = n+values[i];
    return m;
}

Matrix2 Matrix2::operator-(const Matrix2& mat) const
{
    Matrix2 m;
    for(unsigned int i = 0; i < 4; ++i)
        m[i] = values[i]-mat[i];
    return m;
}

Matrix2 Matrix2::operator-(float n) const
{
    Matrix2 m;
    for(unsigned int i = 0; i < 4; ++i)
        m[i] = values[i]-n;
    return m;
}

Matrix2 Matrix2::operator-() const
{
    Matrix2 m;
    for(unsigned int i = 0; i < 4; ++i)
        m[i] = -values[i];
    return m;
}

Matrix2 Matrix2::operator* (const Matrix2& mat) const
{
    return Matrix2(
        values[0]*mat[0]+values[1]*mat[2],
        values[0]*mat[1]+values[1]*mat[3],
        values[2]*mat[0]+values[3]*mat[2],
        values[2]*mat[1]+values[1]*mat[3]
    );
}

Vector2 Matrix2::operator*(const Vector2& vec) const
{
    return Vector2((*this)(0,0)*vec.x+(*this)(0,1)*vec.y,
                   (*this)(1,0)*vec.x+(*this)(1,1)*vec.y);
}

Matrix2 Matrix2::operator*(float n) const
{
    Matrix2 m;
    for(unsigned int i = 0; i < 4; ++i)
        m[i] = values[i]*n;
    return m;
}

Matrix2 Matrix2::operator/(float n) const
{
    Matrix2 m;
    for(unsigned int i = 0; i < 4; ++i)
        m[i] = values[i]/n;
    return m;
}

Matrix2& Matrix2::operator+=(const Matrix2& mat)
{
    return *this = *this+mat;
}

Matrix2& Matrix2::operator+=(float n)
{
    return *this = *this+n;
}

Matrix2& Matrix2::operator-=(const Matrix2& mat)
{
    return *this = *this-mat;
}

Matrix2& Matrix2::operator-=(float n)
{
    return *this = *this-n;
}

Matrix2& Matrix2::operator*=(float n)
{
    return *this = *this*n;
}

Matrix2& Matrix2::operator*=(const Matrix2& mat)
{
    return *this = *this*mat;
}

Matrix2& Matrix2::operator/=(float n)
{
    return *this = *this/n;
}

bool Matrix2::operator==(const Matrix2& mat) const
{
    return values[0] == mat[0] && 
        values[1] == mat[1] && 
        values[2] == mat[2] && 
        values[3] == mat[3];
}

bool Matrix2::operator!=(const Matrix2& mat) const
{
    return !((*this) == mat);
}

float& Matrix2::operator[](unsigned int index)
{
    return values[index];
}

float Matrix2::operator[](unsigned int index) const
{
    return values[index];
}

float& Matrix2::operator()(unsigned int row, unsigned int col)
{
    return values[row*2 + col];
}

float Matrix2::operator()(unsigned int row, unsigned int col) const
{
    return values[row*2 + col];
}


Matrix2 operator*(float n, const Matrix2& m)
{
    return m*n;
}

Vector2 operator*(const Vector2& vec, const Matrix2& m)
{
    return m*vec;
}