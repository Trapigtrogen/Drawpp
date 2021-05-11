#include <matrix4.hpp>
#include <limits>

DMatrix4::DMatrix4() : values{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1} {}

DMatrix4::DMatrix4(float n):values{n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n} {}

DMatrix4::DMatrix4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33):
                   values{m00,m01,m02,m03,
                          m10,m11,m12,m13,
                          m20,m21,m22,m23,
                          m30,m31,m32,m33} {}

DMatrix4::DMatrix4(float vals[16]) { for(int i=0;i<16;i++){values[i]=vals[i];} }

DMatrix4 DMatrix4::hproduct(const DMatrix4& mat1,const DMatrix4& mat2)
{
    DMatrix4 r;
    for(int i = 0; i < 16; i++)
        r[i] = mat1[i]*mat2[i];
    return r;
}

DMatrix4 DMatrix4::hdivision(const DMatrix4& mat1,const DMatrix4& mat2)
{
    DMatrix4 r;
    for(int i = 0; i < 16; i++)
        r[i] = mat1[i]/mat2[i];
    return r;
}

DMatrix4 DMatrix4::identity()
{
    return DMatrix4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
}

DMatrix4 DMatrix4::identity(float n)
{
    return DMatrix4(n,0,0,0,0,n,0,0,0,0,n,0,0,0,0,n);
}

DMatrix4 DMatrix4::translation(const DVector& vec)
{
    DMatrix4 r = DMatrix4::identity();
    r(0,3) = vec.x;
    r(1,3) = vec.y;
    r(2,3) = vec.z;
    return r;
}

DMatrix4 DMatrix4::scaling(const DVector& vec)
{
    DMatrix4 r = DMatrix4::identity();
    r(0,0) = vec.x;
    r(1,1) = vec.y;
    r(2,2) = vec.z;
    return r;
}

DMatrix4 DMatrix4::translate(const DVector& vec) const
{
    return *this*translation(vec);
}

DMatrix4 DMatrix4::scale(const DVector& vec) const
{
    return *this*scaling(vec);
}

float DMatrix4::det()
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

DMatrix4 DMatrix4::transposed()
{
    DMatrix4 m;
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++)
            m(i,j) = (*this)(j,i);
    }
    return m;
}

void DMatrix4::transpose()
{
    for(int i = 0; i<3; i++){
        for(int j = i+1; j<4; j++){
            float t = (*this)(i,j);
            (*this)(i,j) = (*this)(j,i);
            (*this)(j,i) = t;
        }
    }
}

DMatrix4 DMatrix4::inverse()
{
    float d = 1/det();
    return inverse(d);
}

DMatrix4 DMatrix4::inverse(float s)
{
    return DMatrix4(((*this)(1,2)*(*this)(2,3)*(*this)(3,1)-(*this)(1,3)*(*this)(2,2)*(*this)(3,1)+(*this)(1,3)*(*this)(2,1)*(*this)(3,2)-(*this)(1,1)*(*this)(2,3)*(*this)(3,2)-(*this)(1,2)*(*this)(2,1)*(*this)(3,3)+(*this)(1,1)*(*this)(2,2)*(*this)(3,3))*s,
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

bool DMatrix4::invert()
{
    float d = 1/det();

    if(d <= std::numeric_limits<float>::epsilon())
    {
        return false;
    }
    else
    {
        *this = inverse();
        return true;
    }
}

DMatrix4 DMatrix4::operator+(const DMatrix4& mat) const
{
    DMatrix4 m;
    for(int i = 0; i < 16; i++)
        m[i] = mat[i]+values[i];
    return m;
}

DMatrix4 DMatrix4::operator+(float n) const
{
    DMatrix4 m;
    for(int i = 0; i < 16; i++)
        m[i] = n+values[i];
    return m;
}

DMatrix4 DMatrix4::operator-(const DMatrix4& mat) const
{
    DMatrix4 m;
    for(int i = 0; i < 16; i++)
        m[i] = mat[i]-values[i];
    return m;
}

DMatrix4 DMatrix4::operator-(float n) const
{
    DMatrix4 m;
    for(int i = 0; i < 16; i++)
        m[i] = values[i]-n;
    return m;
}

DMatrix4 DMatrix4::operator-() const
{
    DMatrix4 m;
    for(int i = 0; i < 16; i++)
        m[i] = -values[i];
    return m;
}

DMatrix4 DMatrix4::operator* (const DMatrix4& mat) const
{
    return DMatrix4 ((*this)(0,0)*mat(0,0)+(*this)(0,1)*mat(1,0)+(*this)(0,2)*mat(2,0)+(*this)(0,3)*mat(3,0),(*this)(0,0)*mat(0,1)+(*this)(0,1)*mat(1,1)+(*this)(0,2)*mat(2,1)+(*this)(0,3)*mat(3,1),(*this)(0,0)*mat(0,2)+(*this)(0,1)*mat(1,2)+(*this)(0,2)*mat(2,2)+(*this)(0,3)*mat(3,2),(*this)(0,0)*mat(0,3)+(*this)(0,1)*mat(1,3)+(*this)(0,2)*mat(2,3)+(*this)(0,3)*mat(3,3),
                (*this)(1,0)*mat(0,0)+(*this)(1,1)*mat(1,0)+(*this)(1,2)*mat(2,0)+(*this)(1,3)*mat(3,0),(*this)(1,0)*mat(0,1)+(*this)(1,1)*mat(1,1)+(*this)(1,2)*mat(2,1)+(*this)(1,3)*mat(3,1),(*this)(1,0)*mat(0,2)+(*this)(1,1)*mat(1,2)+(*this)(1,2)*mat(2,2)+(*this)(1,3)*mat(3,2),(*this)(1,0)*mat(0,3)+(*this)(1,1)*mat(1,3)+(*this)(1,2)*mat(2,3)+(*this)(1,3)*mat(3,3),
                (*this)(2,0)*mat(0,0)+(*this)(2,1)*mat(1,0)+(*this)(2,2)*mat(2,0)+(*this)(2,3)*mat(3,0),(*this)(2,0)*mat(0,1)+(*this)(2,1)*mat(1,1)+(*this)(2,2)*mat(2,1)+(*this)(2,3)*mat(3,1),(*this)(2,0)*mat(0,2)+(*this)(2,1)*mat(1,2)+(*this)(2,2)*mat(2,2)+(*this)(2,3)*mat(3,2),(*this)(2,0)*mat(0,3)+(*this)(2,1)*mat(1,3)+(*this)(2,2)*mat(2,3)+(*this)(2,3)*mat(3,3),
                (*this)(3,0)*mat(0,0)+(*this)(3,1)*mat(1,0)+(*this)(3,2)*mat(2,0)+(*this)(3,3)*mat(3,0),(*this)(3,0)*mat(0,1)+(*this)(3,1)*mat(1,1)+(*this)(3,2)*mat(2,1)+(*this)(3,3)*mat(3,1),(*this)(3,0)*mat(0,2)+(*this)(3,1)*mat(1,2)+(*this)(3,2)*mat(2,2)+(*this)(3,3)*mat(3,2),(*this)(3,0)*mat(0,3)+(*this)(3,1)*mat(1,3)+(*this)(3,2)*mat(2,3)+(*this)(3,3)*mat(3,3));
}

DVector DMatrix4::operator*(const DVector& vec) const
{
    return DVector(vec.x*(*this)(0,0) + vec.y*(*this)(0,1) + vec.z*(*this)(0,2) + (*this)(0,3),
                vec.x*(*this)(1,0) + vec.y*(*this)(1,1) + vec.z*(*this)(1,2) + (*this)(1,3),
                vec.x*(*this)(2,0) + vec.y*(*this)(2,1) + vec.z*(*this)(2,2) + (*this)(2,3));
}

DMatrix4 DMatrix4::operator*(float n) const
{
    DMatrix4 rm;
    for(int i = 0; i < 16; i++)
        rm[i] = values[i]*n;
    return rm;
}

DMatrix4 DMatrix4::operator/(float n) const
{
    DMatrix4 m;
    for(int i = 0; i < 16; i++)
        m[i] = values[i]/n;
    return m;
}

DMatrix4& DMatrix4::operator+=(const DMatrix4& mat){
    *this = *this+mat;
    return *this;
}

DMatrix4& DMatrix4::operator+=(float n){
    *this = *this+n;
    return *this;
}

DMatrix4& DMatrix4::operator-=(const DMatrix4& mat){
    *this = *this-mat;
    return *this;
}

DMatrix4& DMatrix4::operator-=(float n){
    *this = *this-n;
    return *this;
}

DMatrix4& DMatrix4::operator*=(float n){
    *this = *this*n;
    return *this;
}

DMatrix4& DMatrix4::operator*=(const DMatrix4& mat)
{
    *this = *this*mat;
    return *this;
}

DMatrix4& DMatrix4::operator/=(float n){
    *this = *this/n;
    return *this;
}

bool DMatrix4::operator==(const DMatrix4& mat) const
{
    for(int i= 0; i < 16; i++)
    {
        if(values[i] != mat[i])
            return false;
    }
    return true;
}

bool DMatrix4::operator!=(const DMatrix4& mat) const
{
    return !((*this)==mat);
}

float& DMatrix4::operator[](size_t index) { return values[index]; }
float DMatrix4::operator[](size_t index) const { return values[index]; }
float& DMatrix4::operator()(size_t row, size_t col){ return values[row*4 + col]; }
float DMatrix4::operator()(size_t row, size_t col) const { return values[row*4 + col]; }

DMatrix4 operator*(float n, const DMatrix4& m) { return m*n; }
DVector operator*(const DVector& vec, const DMatrix4& m) { return m*vec; }

