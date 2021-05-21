#ifndef DPP_MATRIX2_H
#define DPP_MATRIX2_H

struct Vector2;

///\brief 2x2 matrix class
class Matrix2
{
public:

    ///\brief Initialize matrix to identity
    Matrix2();


    ///\brief Initialize all matrix values to \p v
    Matrix2(float v);


    ///\brief Initialize matrix values
    Matrix2(float m00, float m01,
            float m10, float m11);


    ///\brief Hadamard product
    ///
    ///Multiply values in \p mat1 by values in \p mat2
    static Matrix2 hproduct(const Matrix2& mat1, const Matrix2& mat2);


    ///\brief Hadamard division
    ///
    ///Divide values in \p mat1 by values in \p mat2
    static Matrix2 hdivision(const Matrix2& mat1, const Matrix2& mat2);


    ///\brief Create an identity matrix
    static Matrix2 identity();


    ///\brief Create a \p v identity matrix
    static Matrix2 identity(float v);


    ///\brief Create a rotation matrix from \p angle (radians)
    static Matrix2 rotation(float angle);


    ///\brief Create a scaling matrix from \p s
    static Matrix2 scaling(const Vector2& s);


    ///\brief Rotate matrix by \p angle (radians)
    ///
    ///\return A copy of this matrix rotated
    Matrix2 rotate(float angle) const;


    ///\brief Scale this matrix by \p s
    ///
    ///\return A copy of this matrix scaled
    Matrix2 scale(const Vector2& s) const;


    ///\brief Get the determinant of this matrix
    float det() const;


    ///\brief Get a copy of this matrix transposed
    Matrix2 transposed() const;


    ///\brief Transpose this matrix
    void transpose();


    ///\brief Get a copy of this matrix inversed
    Matrix2 inverse() const;


    ///\brief Invert this matrix
    ///\return true if matrix was invertable, false otherwise.
    bool invert();


    ///\brief Add values of \p mat and values of this matrix
    Matrix2 operator+(const Matrix2& mat) const;


    ///\brief Add \p n to all values of this matrix
    Matrix2 operator+(float n) const;


    ///\brief Substract values of \p mat from values of this matrix
    Matrix2 operator-(const Matrix2& mat) const;


    ///\brief Substract \p n from all values of this matrix
    Matrix2 operator-(float n) const;


    ///\brief Invert all values of this matrix
    ///
    ///This is \b not the same as invert().
    Matrix2 operator-() const;


    ///\brief Multipy this matrix by \p mat
    Matrix2 operator* (const Matrix2& mat) const;


    ///\brief Multiply \p vec by this matrix
    Vector2 operator*(const Vector2& vec) const;


    ///\brief Multiply all values of this matrix by \p n
    Matrix2 operator*(float n) const;


    ///\brief Divide all values of this matrix by \p n
    Matrix2 operator/(float n) const;


    ///\brief Add values of \p mat and values of this matrix, and assing result to this matrix
    Matrix2& operator+=(const Matrix2& mat);


    ///\brief Add \p n to all values of this matrix, and assing result to this matrix
    Matrix2& operator+=(float n);


    ///\brief Substract values of \p mat from values of this matrix, and assing result to this matrix
    Matrix2& operator-=(const Matrix2& mat);


    ///\brief Substract \p n from all values of this matrix, and assing result to this matrix
    Matrix2& operator-=(float n);


    ///\brief Multiply all values of this matrix by \p n, and assing result to this matrix
    Matrix2& operator*=(float n);


    ///\brief Multipy this matrix by \p mat, and assing result to this matrix
    Matrix2& operator*=(const Matrix2& mat);


    ///\brief Divide all values of this matrix by \p n, and assing result to this matrix
    Matrix2& operator/=(float n);


    ///\brief Compare this matrix and \p mat
    bool operator==(const Matrix2& mat) const;


    ///\brief Compare this matrix and \p mat
    bool operator!=(const Matrix2& mat) const;


    ///\brief access matrix elements by index
    float& operator[](unsigned int index);


    ///\copydoc operator[](unsigned int)
    float operator[](unsigned int index) const;


    ///\copydoc operator[](unsigned int)
    float& operator()(unsigned int row, unsigned int col);


    ///\copydoc operator[](unsigned int)
    float operator()(unsigned int row, unsigned int col) const;


    ///\copydoc operator*(float n) const
    friend Matrix2 operator*(float n, const Matrix2& m);


    ///\copydoc operator*(const Vector2&) const
    friend Vector2 operator*(const Vector2& vec, const Matrix2& m);


    float values[4];
    
private:
    
    Matrix2 inverse(float) const;
};

#endif