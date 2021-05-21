#include <matrix4.hpp>
#include <limits>
#include <vector3.hpp>
#include <vector4.hpp>

Matrix4::Matrix4() : values{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1} {}

Matrix4::Matrix4(float n):values{n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n} {}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33):
                   values{m00,m01,m02,m03,
                          m10,m11,m12,m13,
                          m20,m21,m22,m23,
                          m30,m31,m32,m33} {}

Matrix4::Matrix4(float vals[16]) { for(unsigned int i=0;i<16;++i){values[i]=vals[i];} }

Matrix4 Matrix4::hproduct(const Matrix4& mat1,const Matrix4& mat2)
{
    Matrix4 r;
    for(unsigned int i = 0; i < 16; ++i)
        r[i] = mat1[i]*mat2[i];
    return r;
}

Matrix4 Matrix4::hdivision(const Matrix4& mat1,const Matrix4& mat2)
{
    Matrix4 r;
    for(unsigned int i = 0; i < 16; ++i)
        r[i] = mat1[i]/mat2[i];
    return r;
}

Matrix4 Matrix4::identity()
{
    return Matrix4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
}

Matrix4 Matrix4::identity(float n)
{
    return Matrix4(n,0,0,0,0,n,0,0,0,0,n,0,0,0,0,n);
}

Matrix4 Matrix4::translation(const Vector3& vec)
{
    Matrix4 r = Matrix4::identity();
    r(0,3) = vec.x;
    r(1,3) = vec.y;
    r(2,3) = vec.z;
    return r;
}

Matrix4 Matrix4::scaling(const Vector3& vec)
{
    Matrix4 r = Matrix4::identity();
    r(0,0) = vec.x;
    r(1,1) = vec.y;
    r(2,2) = vec.z;
    return r;
}

Matrix4 Matrix4::translate(const Vector3& vec) const
{
    return *this*translation(vec);
}

Matrix4 Matrix4::scale(const Vector3& vec) const
{
    return *this*scaling(vec);
}

float Matrix4::det() const
{
    return  (*this)(0,3) * (*this)(1,2) * (*this)(2,1) * (*this)(3,0)-(*this)(0,2) * (*this)(1,3) * (*this)(2,1) * (*this)(3,0)-
            (*this)(0,3) * (*this)(1,1) * (*this)(2,2) * (*this)(3,0)+(*this)(0,1) * (*this)(1,3) * (*this)(2,2) * (*this)(3,0)+
            (*this)(0,2) * (*this)(1,1) * (*this)(2,3) * (*this)(3,0)-(*this)(0,1) * (*this)(1,2) * (*this)(2,3) * (*this)(3,0)-
            (*this)(0,3) * (*this)(1,2) * (*this)(2,0) * (*this)(3,1)+(*this)(0,2) * (*this)(1,3) * (*this)(2,0) * (*this)(3,1)+
            (*this)(0,3) * (*this)(1,0) * (*this)(2,2) * (*this)(3,1)-(*this)(0,0) * (*this)(1,3) * (*this)(2,2) * (*this)(3,1)-
            (*this)(0,2) * (*this)(1,0) * (*this)(2,3) * (*this)(3,1)+(*this)(0,0) * (*this)(1,2) * (*this)(2,3) * (*this)(3,1)+
            (*this)(0,3) * (*this)(1,1) * (*this)(2,0) * (*this)(3,2)-(*this)(0,1) * (*this)(1,3) * (*this)(2,0) * (*this)(3,2)-
            (*this)(0,3) * (*this)(1,0) * (*this)(2,1) * (*this)(3,2)+(*this)(0,0) * (*this)(1,3) * (*this)(2,1) * (*this)(3,2)+
            (*this)(0,1) * (*this)(1,0) * (*this)(2,3) * (*this)(3,2)-(*this)(0,0) * (*this)(1,1) * (*this)(2,3) * (*this)(3,2)-
            (*this)(0,2) * (*this)(1,1) * (*this)(2,0) * (*this)(3,3)+(*this)(0,1) * (*this)(1,2) * (*this)(2,0) * (*this)(3,3)+
            (*this)(0,2) * (*this)(1,0) * (*this)(2,1) * (*this)(3,3)-(*this)(0,0) * (*this)(1,2) * (*this)(2,1) * (*this)(3,3)-
            (*this)(0,1) * (*this)(1,0) * (*this)(2,2) * (*this)(3,3)+(*this)(0,0) * (*this)(1,1) * (*this)(2,2) * (*this)(3,3);
}

Matrix4 Matrix4::transposed() const
{
    Matrix4 m;
    for(unsigned int i = 0; i<4; ++i){
        for(int j = 0; j<4; j++)
            m(i,j) = (*this)(j,i);
    }
    return m;
}

void Matrix4::transpose()
{
    for(unsigned int i = 0; i<3; ++i){
        for(int j = i+1; j<4; j++){
            float t = (*this)(i,j);
            (*this)(i,j) = (*this)(j,i);
            (*this)(j,i) = t;
        }
    }
}

Matrix4 Matrix4::inverse() const
{
    float d = 1/det();
    return inverse(d);
}

Matrix4 Matrix4::inverse(float s) const
{
    return Matrix4(((*this)(1,2)*(*this)(2,3)*(*this)(3,1)-(*this)(1,3)*(*this)(2,2)*(*this)(3,1)+(*this)(1,3)*(*this)(2,1)*(*this)(3,2)-(*this)(1,1)*(*this)(2,3)*(*this)(3,2)-(*this)(1,2)*(*this)(2,1)*(*this)(3,3)+(*this)(1,1)*(*this)(2,2)*(*this)(3,3))*s,
                ((*this)(0,3)*(*this)(2,2)*(*this)(3,1)-(*this)(0,2)*(*this)(2,3)*(*this)(3,1)-(*this)(0,3)*(*this)(2,1)*(*this)(3,2)+(*this)(0,1)*(*this)(2,3)*(*this)(3,2)+(*this)(0,2)*(*this)(2,1)*(*this)(3,3)-(*this)(0,1)*(*this)(2,2)*(*this)(3,3))*s,
                ((*this)(0,2)*(*this)(1,3)*(*this)(3,1)-(*this)(0,3)*(*this)(1,2)*(*this)(3,1)+(*this)(0,3)*(*this)(1,1)*(*this)(3,2)-(*this)(0,1)*(*this)(1,3)*(*this)(3,2)-(*this)(0,2)*(*this)(1,1)*(*this)(3,3)+(*this)(0,1)*(*this)(1,2)*(*this)(3,3))*s,
                ((*this)(0,3)*(*this)(1,2)*(*this)(2,1)-(*this)(0,2)*(*this)(1,3)*(*this)(2,1)-(*this)(0,3)*(*this)(1,1)*(*this)(2,2)+(*this)(0,1)*(*this)(1,3)*(*this)(2,2)+(*this)(0,2)*(*this)(1,1)*(*this)(2,3)-(*this)(0,1)*(*this)(1,2)*(*this)(2,3))*s,
                ((*this)(1,3)*(*this)(2,2)*(*this)(3,0)-(*this)(1,2)*(*this)(2,3)*(*this)(3,0)-(*this)(1,3)*(*this)(2,0)*(*this)(3,2)+(*this)(1,0)*(*this)(2,3)*(*this)(3,2)+(*this)(1,2)*(*this)(2,0)*(*this)(3,3)-(*this)(1,0)*(*this)(2,2)*(*this)(3,3))*s,
                ((*this)(0,2)*(*this)(2,3)*(*this)(3,0)-(*this)(0,3)*(*this)(2,2)*(*this)(3,0)+(*this)(0,3)*(*this)(2,0)*(*this)(3,2)-(*this)(0,0)*(*this)(2,3)*(*this)(3,2)-(*this)(0,2)*(*this)(2,0)*(*this)(3,3)+(*this)(0,0)*(*this)(2,2)*(*this)(3,3))*s,
                ((*this)(0,3)*(*this)(1,2)*(*this)(3,0)-(*this)(0,2)*(*this)(1,3)*(*this)(3,0)-(*this)(0,3)*(*this)(1,0)*(*this)(3,2)+(*this)(0,0)*(*this)(1,3)*(*this)(3,2)+(*this)(0,2)*(*this)(1,0)*(*this)(3,3)-(*this)(0,0)*(*this)(1,2)*(*this)(3,3))*s,
                ((*this)(0,2)*(*this)(1,3)*(*this)(2,0)-(*this)(0,3)*(*this)(1,2)*(*this)(2,0)+(*this)(0,3)*(*this)(1,0)*(*this)(2,2)-(*this)(0,0)*(*this)(1,3)*(*this)(2,2)-(*this)(0,2)*(*this)(1,0)*(*this)(2,3)+(*this)(0,0)*(*this)(1,2)*(*this)(2,3))*s,
                ((*this)(1,1)*(*this)(2,3)*(*this)(3,0)-(*this)(1,3)*(*this)(2,1)*(*this)(3,0)+(*this)(1,3)*(*this)(2,0)*(*this)(3,1)-(*this)(1,0)*(*this)(2,3)*(*this)(3,1)-(*this)(1,1)*(*this)(2,0)*(*this)(3,3)+(*this)(1,0)*(*this)(2,1)*(*this)(3,3))*s,
                ((*this)(0,3)*(*this)(2,1)*(*this)(3,0)-(*this)(0,1)*(*this)(2,3)*(*this)(3,0)-(*this)(0,3)*(*this)(2,0)*(*this)(3,1)+(*this)(0,0)*(*this)(2,3)*(*this)(3,1)+(*this)(0,1)*(*this)(2,0)*(*this)(3,3)-(*this)(0,0)*(*this)(2,1)*(*this)(3,3))*s,
                ((*this)(0,1)*(*this)(1,3)*(*this)(3,0)-(*this)(0,3)*(*this)(1,1)*(*this)(3,0)+(*this)(0,3)*(*this)(1,0)*(*this)(3,1)-(*this)(0,0)*(*this)(1,3)*(*this)(3,1)-(*this)(0,1)*(*this)(1,0)*(*this)(3,3)+(*this)(0,0)*(*this)(1,1)*(*this)(3,3))*s,
                ((*this)(0,3)*(*this)(1,1)*(*this)(2,0)-(*this)(0,1)*(*this)(1,3)*(*this)(2,0)-(*this)(0,3)*(*this)(1,0)*(*this)(2,1)+(*this)(0,0)*(*this)(1,3)*(*this)(2,1)+(*this)(0,1)*(*this)(1,0)*(*this)(2,3)-(*this)(0,0)*(*this)(1,1)*(*this)(2,3))*s,
                ((*this)(1,2)*(*this)(2,1)*(*this)(3,0)-(*this)(1,1)*(*this)(2,2)*(*this)(3,0)-(*this)(1,2)*(*this)(2,0)*(*this)(3,1)+(*this)(1,0)*(*this)(2,2)*(*this)(3,1)+(*this)(1,1)*(*this)(2,0)*(*this)(3,2)-(*this)(1,0)*(*this)(2,1)*(*this)(3,2))*s,
                ((*this)(0,1)*(*this)(2,2)*(*this)(3,0)-(*this)(0,2)*(*this)(2,1)*(*this)(3,0)+(*this)(0,2)*(*this)(2,0)*(*this)(3,1)-(*this)(0,0)*(*this)(2,2)*(*this)(3,1)-(*this)(0,1)*(*this)(2,0)*(*this)(3,2)+(*this)(0,0)*(*this)(2,1)*(*this)(3,2))*s,
                ((*this)(0,2)*(*this)(1,1)*(*this)(3,0)-(*this)(0,1)*(*this)(1,2)*(*this)(3,0)-(*this)(0,2)*(*this)(1,0)*(*this)(3,1)+(*this)(0,0)*(*this)(1,2)*(*this)(3,1)+(*this)(0,1)*(*this)(1,0)*(*this)(3,2)-(*this)(0,0)*(*this)(1,1)*(*this)(3,2))*s,
                ((*this)(0,1)*(*this)(1,2)*(*this)(2,0)-(*this)(0,2)*(*this)(1,1)*(*this)(2,0)+(*this)(0,2)*(*this)(1,0)*(*this)(2,1)-(*this)(0,0)*(*this)(1,2)*(*this)(2,1)-(*this)(0,1)*(*this)(1,0)*(*this)(2,2)+(*this)(0,0)*(*this)(1,1)*(*this)(2,2))*s);
    
}

bool Matrix4::invert()
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

Matrix4 Matrix4::operator+(const Matrix4& mat) const
{
    Matrix4 m;
    for(unsigned int i = 0; i < 16; ++i)
        m[i] = mat[i]+values[i];
    return m;
}

Matrix4 Matrix4::operator+(float n) const
{
    Matrix4 m;
    for(unsigned int i = 0; i < 16; ++i)
        m[i] = n+values[i];
    return m;
}

Matrix4 Matrix4::operator-(const Matrix4& mat) const
{
    Matrix4 m;
    for(unsigned int i = 0; i < 16; ++i)
        m[i] = values[i]-mat[i];
    return m;
}

Matrix4 Matrix4::operator-(float n) const
{
    Matrix4 m;
    for(unsigned int i = 0; i < 16; ++i)
        m[i] = values[i]-n;
    return m;
}

Matrix4 Matrix4::operator-() const
{
    Matrix4 m;
    for(unsigned int i = 0; i < 16; ++i)
        m[i] = -values[i];
    return m;
}

Matrix4 Matrix4::operator* (const Matrix4& mat) const
{
    return Matrix4 ((*this)(0,0)*mat(0,0)+(*this)(0,1)*mat(1,0)+(*this)(0,2)*mat(2,0)+(*this)(0,3)*mat(3,0),(*this)(0,0)*mat(0,1)+(*this)(0,1)*mat(1,1)+(*this)(0,2)*mat(2,1)+(*this)(0,3)*mat(3,1),(*this)(0,0)*mat(0,2)+(*this)(0,1)*mat(1,2)+(*this)(0,2)*mat(2,2)+(*this)(0,3)*mat(3,2),(*this)(0,0)*mat(0,3)+(*this)(0,1)*mat(1,3)+(*this)(0,2)*mat(2,3)+(*this)(0,3)*mat(3,3),
                (*this)(1,0)*mat(0,0)+(*this)(1,1)*mat(1,0)+(*this)(1,2)*mat(2,0)+(*this)(1,3)*mat(3,0),(*this)(1,0)*mat(0,1)+(*this)(1,1)*mat(1,1)+(*this)(1,2)*mat(2,1)+(*this)(1,3)*mat(3,1),(*this)(1,0)*mat(0,2)+(*this)(1,1)*mat(1,2)+(*this)(1,2)*mat(2,2)+(*this)(1,3)*mat(3,2),(*this)(1,0)*mat(0,3)+(*this)(1,1)*mat(1,3)+(*this)(1,2)*mat(2,3)+(*this)(1,3)*mat(3,3),
                (*this)(2,0)*mat(0,0)+(*this)(2,1)*mat(1,0)+(*this)(2,2)*mat(2,0)+(*this)(2,3)*mat(3,0),(*this)(2,0)*mat(0,1)+(*this)(2,1)*mat(1,1)+(*this)(2,2)*mat(2,1)+(*this)(2,3)*mat(3,1),(*this)(2,0)*mat(0,2)+(*this)(2,1)*mat(1,2)+(*this)(2,2)*mat(2,2)+(*this)(2,3)*mat(3,2),(*this)(2,0)*mat(0,3)+(*this)(2,1)*mat(1,3)+(*this)(2,2)*mat(2,3)+(*this)(2,3)*mat(3,3),
                (*this)(3,0)*mat(0,0)+(*this)(3,1)*mat(1,0)+(*this)(3,2)*mat(2,0)+(*this)(3,3)*mat(3,0),(*this)(3,0)*mat(0,1)+(*this)(3,1)*mat(1,1)+(*this)(3,2)*mat(2,1)+(*this)(3,3)*mat(3,1),(*this)(3,0)*mat(0,2)+(*this)(3,1)*mat(1,2)+(*this)(3,2)*mat(2,2)+(*this)(3,3)*mat(3,2),(*this)(3,0)*mat(0,3)+(*this)(3,1)*mat(1,3)+(*this)(3,2)*mat(2,3)+(*this)(3,3)*mat(3,3));
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
    return Vector3(vec.x*(*this)(0,0) + vec.y*(*this)(0,1) + vec.z*(*this)(0,2) + (*this)(0,3),
                   vec.x*(*this)(1,0) + vec.y*(*this)(1,1) + vec.z*(*this)(1,2) + (*this)(1,3),
                   vec.x*(*this)(2,0) + vec.y*(*this)(2,1) + vec.z*(*this)(2,2) + (*this)(2,3));
}

Vector4 Matrix4::operator*(const Vector4& vec) const
{
    return Vector4(vec.x*(*this)(0,0) + vec.y*(*this)(0,1) + vec.z*(*this)(0,2) + vec.w*(*this)(0,3),
                   vec.x*(*this)(1,0) + vec.y*(*this)(1,1) + vec.z*(*this)(1,2) + vec.w*(*this)(1,3),
                   vec.x*(*this)(2,0) + vec.y*(*this)(2,1) + vec.z*(*this)(2,2) + vec.w*(*this)(2,3),
                   vec.x*(*this)(3,0) + vec.y*(*this)(3,1) + vec.z*(*this)(3,2) + vec.w*(*this)(3,3));
}

Matrix4 Matrix4::operator*(float n) const
{
    Matrix4 rm;
    for(unsigned int i = 0; i < 16; ++i)
        rm[i] = values[i]*n;
    return rm;
}

Matrix4 Matrix4::operator/(float n) const
{
    Matrix4 m;
    for(unsigned int i = 0; i < 16; ++i)
        m[i] = values[i]/n;
    return m;
}

Matrix4& Matrix4::operator+=(const Matrix4& mat){
    *this = *this+mat;
    return *this;
}

Matrix4& Matrix4::operator+=(float n){
    *this = *this+n;
    return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& mat){
    *this = *this-mat;
    return *this;
}

Matrix4& Matrix4::operator-=(float n){
    *this = *this-n;
    return *this;
}

Matrix4& Matrix4::operator*=(float n){
    *this = *this*n;
    return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& mat)
{
    *this = *this*mat;
    return *this;
}

Matrix4& Matrix4::operator/=(float n){
    *this = *this/n;
    return *this;
}

bool Matrix4::operator==(const Matrix4& mat) const
{
    for(unsigned int i= 0; i < 16; ++i)
    {
        if(values[i] != mat[i])
            return false;
    }
    return true;
}

bool Matrix4::operator!=(const Matrix4& mat) const
{
    return !((*this)==mat);
}

float& Matrix4::operator[](unsigned int index) { return values[index]; }
float Matrix4::operator[](unsigned int index) const { return values[index]; }
float& Matrix4::operator()(unsigned int row, unsigned int col){ return values[row*4 + col]; }
float Matrix4::operator()(unsigned int row, unsigned int col) const { return values[row*4 + col]; }

Matrix4 operator*(float n, const Matrix4& m) { return m*n; }
Vector3 operator*(const Vector3& vec, const Matrix4& m) { return m*vec; }
Vector4 operator*(const Vector4& vec, const Matrix4& m) { return m*vec; }

