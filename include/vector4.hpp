#ifndef DPP_VECTOR4_H
#define DPP_VECTOR4_H

///\brief Vector4 class
struct Vector4
{
    ///\brief All values are initialized to zero
    Vector4();


    ///\brief All values are initialized to \p v
    Vector4(float v);
    

    ///\brief Initialize x, y, z and w
    Vector4(float x, float y, float z, float w);


    Vector4(const Vector4&) = default;


    ///\brief Generate a random direction vector
    ///
    ///Uses the default random generator.
    static Vector4 random();

    
    ///\brief Generate a random direction vector using \p gen
    static Vector4 random(class Random& gen);


    ///\brief Get the vector magnitude
    float mag() const;

    
    ///\brief Get the vector magnitude squared
    float magSq() const;


    ///\brief Add \p vec to this vector
    Vector4 operator+(const Vector4& vec) const;


    ///\brief Substract \p vec from this vector
    Vector4 operator-(const Vector4& vec) const;


    ///\brief Invert this vector
    Vector4 operator-()                   const;


    ///\brief Multiply this vector by \p n
    Vector4 operator*(float n)            const;


    ///\brief Multiply elements of this vector by elements of \p vec
    Vector4 operator*(const Vector4& vec) const;
    

    ///\brief Divide this vector by \p n
    Vector4 operator/(float n)            const;

    
    ///\brief Divide elements of this vector by elements of \p vec
    Vector4 operator/(const Vector4& vec) const;


    ///\brief Assign \p vec to this vector
    Vector4& operator=(const Vector4& vec);


    ///\brief Add \p vec to this vector, and assing result to this vector
    Vector4& operator+=(const Vector4& vec);


    ///\brief Substract \p vec from this vector, and assing result to this vector
    Vector4& operator-=(const Vector4& vec);


    ///\brief Multiply this vector by \p n, and assing result to this vector
    Vector4& operator*=(float n);


    ///\brief Multiply this vector by \p vec, and assing result to this vector
    Vector4& operator*=(const Vector4& vec);


    ///\brief Divide this vector by \p n, and assing result to this vector
    Vector4& operator/=(float n);


    ///\brief Divide this vector by \p vec, and assing result to this vector
    Vector4& operator/=(const Vector4& vec);


    ///\brief Test if this vector and \p vec are the same
    bool operator==(const Vector4& vec) const;


    ///\brief Test if this vector and \p vec are not the same
    bool operator!=(const Vector4& vec) const;


    ///\brief Test if this vector is shorter than \p vec
    bool operator<(const Vector4& vec)  const;


    ///\brief Test if this vector is longer than \p vec
    bool operator>(const Vector4& vec)  const;


    ///\brief Test if this vector is shorter than or equal to \p vec
    bool operator<=(const Vector4& vec) const;

    
    ///\brief Test if this vector is longer than or equal to \p vec
    bool operator>=(const Vector4& vec) const;
    

    ///\brief Access members by index
    float& operator[](unsigned int index);


    ///\copydoc Vector4::operator[](unsigned int)
    float operator[](unsigned int index) const;


    ///\copydoc operator*(float n) const
    friend Vector4 operator*(float n, const Vector4& vec);

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};

#endif