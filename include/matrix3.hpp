#ifndef DPP_MATRIX3_H
#define DPP_MATRIX3_H


struct Vector2;
struct Vector3;

///\brief 3x3 matrix class
class Matrix3
{
public:

    ///\brief Initialize matrix to identity
    Matrix3();


    ///\brief Initialize all matrix values to \p v
    Matrix3(float v);


    ///\brief Initialize matrix values
    Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22);


    ///\brief Hadamard product
    ///
    ///Multiply values in \p mat1 by values in \p mat2
    static Matrix3 hproduct(const Matrix3& mat1, const Matrix3& mat2);


    ///\brief Hadamard division
    ///
    ///Divide values in \p mat1 by values in \p mat2
    static Matrix3 hdivision(const Matrix3& mat1, const Matrix3& mat2);


    ///\brief Create an identity matrix
    static Matrix3 identity();


    ///\brief Create a \p v identity matrix
    static Matrix3 identity(float v);


    ///\brief Create a rotation matrix from \p angle (radians)
    static Matrix3 rotation(float angle);


    ///\brief Create a translation matrix from \p t
    static Matrix3 translation(const Vector2& t);


    ///\brief Create a scaling matrix from \p s
    static Matrix3 scaling(const Vector2& s);


    ///\brief Create a scaling matrix from \p s
    static Matrix3 scaling(const Vector3& s);


    ///\brief Rotate matrix by \p angle (radians)
    ///
    ///\return A copy of this matrix rotated
    Matrix3 rotate(float angle) const;


    ///\brief Translate this matrix by \p t
    ///
    ///\return A copy of this matrix translated
    Matrix3 translate(const Vector2& t) const;


    ///\brief Scale this matrix by \p s
    ///
    ///\return A copy of this matrix scaled
    Matrix3 scale(const Vector2& s) const;


    ///\brief Get the determinant of this matrix
    float det() const;


    ///\brief Get a copy of this matrix transposed
    Matrix3 transposed() const;


    ///\brief Transpose this matrix
    void transpose();


    ///\brief Get a copy of this matrix inversed
    Matrix3 inverse() const;


    ///\brief Invert this matrix
    ///\return true if matrix was invertable, false otherwise.
    bool invert();


    ///\brief Add values of \p mat and values of this matrix
    Matrix3 operator+(const Matrix3& mat) const;


    ///\brief Add \p n to all values of this matrix
    Matrix3 operator+(float n) const;


    ///\brief Substract values of \p mat from values of this matrix
    Matrix3 operator-(const Matrix3& mat) const;


    ///\brief Substract \p n from all values of this matrix
    Matrix3 operator-(float n) const;


    ///\brief Invert all values of this matrix
    ///
    ///This is \b not the same as invert().
    Matrix3 operator-() const;


    ///\brief Multipy this matrix by \p mat
    Matrix3 operator* (const Matrix3& mat) const;


    ///\brief Multiply \p vec by this matrix
    Vector2 operator*(const Vector2& vec) const;


    ///\brief Multiply \p vec by this matrix
    Vector3 operator*(const Vector3& vec) const;


    ///\brief Multiply all values of this matrix by \p n
    Matrix3 operator*(float n) const;


    ///\brief Divide all values of this matrix by \p n
    Matrix3 operator/(float n) const;


    ///\brief Add values of \p mat and values of this matrix, and assing result to this matrix
    Matrix3& operator+=(const Matrix3& mat);


    ///\brief Add \p n to all values of this matrix, and assing result to this matrix
    Matrix3& operator+=(float n);


    ///\brief Substract values of \p mat from values of this matrix, and assing result to this matrix
    Matrix3& operator-=(const Matrix3& mat);


    ///\brief Substract \p n from all values of this matrix, and assing result to this matrix
    Matrix3& operator-=(float n);


    ///\brief Multiply all values of this matrix by \p n, and assing result to this matrix
    Matrix3& operator*=(float n);


    ///\brief Multipy this matrix by \p mat, and assing result to this matrix
    Matrix3& operator*=(const Matrix3& mat);


    ///\brief Divide all values of this matrix by \p n, and assing result to this matrix
    Matrix3& operator/=(float n);


    ///\brief Compare this matrix and \p mat
    bool operator==(const Matrix3& mat) const;


    ///\brief Compare this matrix and \p mat
    bool operator!=(const Matrix3& mat) const;


    ///\brief access matrix elements by index
    float& operator[](unsigned int index);


    ///\copydoc operator[](unsigned int)
    float operator[](unsigned int index) const;


    ///\copydoc operator[](unsigned int)
    float& operator()(unsigned int row, unsigned int col);


    ///\copydoc operator[](unsigned int)
    float operator()(unsigned int row, unsigned int col) const;


    ///\copydoc operator*(float n) const
    friend Matrix3 operator*(float n, const Matrix3& m);


    ///\copydoc operator*(const Vector3&) const
    friend Vector3 operator*(const Vector3& vec, const Matrix3& m);


    ///\copydoc operator*(const Vector2&) const
    friend Vector2 operator*(const Vector2& vec, const Matrix3& m);


    float values[9];
    
private:
    
    Matrix3 inverse(float) const;
};

#endif