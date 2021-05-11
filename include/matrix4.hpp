#ifndef DPP_MATRIX4_H
#define DPP_MATRIX4_H

#include <cmath>
#include <vector3.hpp>

enum Axis
{
    X,
    Y,
    Z
};

///\brief A basic 4x4 matrix class
class DMatrix4
{
public:

    ///\brief Initialized matrix to identity
    DMatrix4();


    ///\brief Initialize matrix to \p n indentity
    DMatrix4(float n);


    ///\brief Initialize matrix values
    DMatrix4(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);


    ///\brief Initialize matrix values from a array
    DMatrix4(float vals[16]);


    ~DMatrix4() = default;


    ///\brief Hadamard product
    ///
    ///Multiply values in \p mat1 by values in \p mat2
    static DMatrix4 hproduct(const DMatrix4& mat1,const DMatrix4& mat2);


    ///\brief Hadamard division
    ///
    ///Divide values in \p mat1 by values in \p mat2
    static DMatrix4 hdivision(const DMatrix4& mat1,const DMatrix4& mat2);


    ///\brief Create a identity matrix
    static DMatrix4 identity();


    ///\brief Create a \p n identity matrix
    static DMatrix4 identity(float n);


    ///\brief Create a rotation matrix in axis \p A by \p angleRad
    template<Axis A> static DMatrix4 rotation(float angleRad)
    {
        DMatrix4 r = DMatrix4::identity();

        switch (A)
        {
        case Axis::X:
            {
                r(1,1) = std::cos(angleRad);
                r(1,2) = -std::sin(angleRad);
                r(2,1) = std::sin(angleRad);
                r(2,2) = std::cos(angleRad);
                break;
            }
        case Axis::Y:
            {
                r(0,0) = std::cos(angleRad);
                r(0,2) = std::sin(angleRad);
                r(2,0) = -std::sin(angleRad);
                r(2,2) = std::cos(angleRad);
                break;
            }
        case Axis::Z:
            {
                r(0,0) = std::cos(angleRad);
                r(0,1) = -std::sin(angleRad);
                r(1,0) = std::sin(angleRad);
                r(1,1) = std::cos(angleRad);
                break;
            }
        }
        return r;
    }


    ///\brief Create a translation matrix from \p vec
    static DMatrix4 translation(const DVector& vec);


    ///\brief Create a scaling matrix from \p vec
    static DMatrix4 scaling(const DVector& vec);


    ///\brief Rotate this matrix by \p angleRad
    ///
    ///\return A copy of this matrix rotated
    template<Axis A> DMatrix4 rotate(float angleRad) const
    {
        return *this*rotation<A>(angleRad);
    }


    ///\brief Translate this matrix by \p vec
    ///
    ///\return A copy of this matrix translated
    DMatrix4 translate(const DVector& vec) const;


    ///\brief Scale this matrix by \p vec
    ///
    ///\return A copy of this matrix scaled
    DMatrix4 scale(const DVector& vec) const;


    ///\brief Get the determinant of this matrix
    float det();


    ///\brief Get a copy of this matrix transposed
    DMatrix4 transposed();


    ///\brief Transpose this matrix
    void transpose();


    ///\brief Get a copy of this matrix inversed
    DMatrix4 inverse();


    ///\brief Invert this matrix
    ///\return true if matrix was invertable, false otherwise.
    bool invert();


    ///\brief Add values of \p mat and values of this matrix
    DMatrix4 operator+(const DMatrix4& mat) const;


    ///\brief Add \p n to all values of this matrix
    DMatrix4 operator+(float n) const;


    ///\brief Substract values of \p mat from values of this matrix
    DMatrix4 operator-(const DMatrix4& mat) const;


    ///\brief Substract \p n from all values of this matrix
    DMatrix4 operator-(float n) const;


    ///\brief Invert all values of this matrix
    ///
    ///This is \b not the same as invert().
    DMatrix4 operator-() const;


    ///\brief Multipy this matrix by \p mat
    DMatrix4 operator* (const DMatrix4& mat) const;


    ///\brief Multiply \p vec by this matrix
    DVector operator*(const DVector& vec) const;


    ///\brief Multiply all values of this matrix by \p n
    DMatrix4 operator*(float n) const;


    ///\brief Divide all values of this matrix by \p n
    DMatrix4 operator/(float n) const;


    ///\brief Add values of \p mat and values of this matrix, and assing result to this matrix
    DMatrix4& operator+=(const DMatrix4& mat);


    ///\brief Add \p n to all values of this matrix, and assing result to this matrix
    DMatrix4& operator+=(float n);


    ///\brief Substract values of \p mat from values of this matrix, and assing result to this matrix
    DMatrix4& operator-=(const DMatrix4& mat);


    ///\brief Substract \p n from all values of this matrix, and assing result to this matrix
    DMatrix4& operator-=(float n);


    ///\brief Multiply all values of this matrix by \p n, and assing result to this matrix
    DMatrix4& operator*=(float n);


    ///\brief Multipy this matrix by \p mat, and assing result to this matrix
    DMatrix4& operator*=(const DMatrix4& mat);


    ///\brief Divide all values of this matrix by \p n, and assing result to this matrix
    DMatrix4& operator/=(float n);


    ///\brief Compare this matrix and \p mat
    bool operator==(const DMatrix4& mat) const;


    ///\brief Compare this matrix and \p mat
    bool operator!=(const DMatrix4& mat) const;


    ///\brief access matrix elements by index
    float& operator[](size_t index);


    ///\copydoc operator[](size_t index)
    float operator[](size_t index) const;


    ///\copydoc operator[](size_t index)
    float& operator()(size_t row, size_t col);


    ///\copydoc operator[](size_t index)
    float operator()(size_t row, size_t col) const;


    ///\copydoc operator*(float n) const
    friend DMatrix4 operator*(float n, const DMatrix4& m);


    ///\copydoc operator*(const DVector&) const
    friend DVector operator*(const DVector& vec, const DMatrix4& m);


    float values[16];

private:
    
    DMatrix4 inverse(float);
};

#endif