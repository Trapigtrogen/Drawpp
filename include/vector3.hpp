#ifndef DPP_VECTOR3_H
#define DPP_VECTOR3_H

///\brief Vector3 class
struct Vector3
{
    ///\brief All values are initialized to zero
    Vector3();


    ///\brief All values are initialized to \p v
    Vector3(float v);


    ///\brief Initialize x, y and z
    Vector3(float x, float y, float z);


    Vector3(const Vector3&) = default;


    ///\brief Generate a random direction vector
    ///
    ///Uses the default random generator.
    static Vector3 random();

    
    ///\brief Generate a random direction vector using \p gen
    static Vector3 random(class Random& gen);


    ///\brief Get the vector magnitude
    float mag() const;
    

    ///\brief Get the vector magnitude squared
    float magSq() const;


    ///\brief Add \p vec to this vector
    Vector3 operator+(const Vector3& vec) const;


    ///\brief Substract \p vec from this vector
    Vector3 operator-(const Vector3& vec) const;


    ///\brief Invert this vector
    Vector3 operator-()                   const;


    ///\brief Multiply this vector by \p n
    Vector3 operator*(float n)            const;


    ///\brief Multiply elements of this vector by elements of \p vec
    Vector3 operator*(const Vector3& vec) const;
    

    ///\brief Divide this vector by \p n
    Vector3 operator/(float n)            const;

    
    ///\brief Divide elements of this vector by elements of \p vec
    Vector3 operator/(const Vector3& vec) const;


    ///\brief Assign \p vec to this vector
    Vector3& operator=(const Vector3& vec);


    ///\brief Add \p vec to this vector, and assing result to this vector
    Vector3& operator+=(const Vector3& vec);


    ///\brief Substract \p vec from this vector, and assing result to this vector
    Vector3& operator-=(const Vector3& vec);


    ///\brief Multiply this vector by \p n, and assing result to this vector
    Vector3& operator*=(float n);


    ///\brief Multiply this vector by \p vec, and assing result to this vector
    Vector3& operator*=(const Vector3& vec);


    ///\brief Divide this vector by \p n, and assing result to this vector
    Vector3& operator/=(float n);


    ///\brief Divide this vector by \p vec, and assing result to this vector
    Vector3& operator/=(const Vector3& vec);


    ///\brief Test if this vector and \p vec are the same
    bool operator==(const Vector3& vec) const;


    ///\brief Test if this vector and \p vec are not the same
    bool operator!=(const Vector3& vec) const;


    ///\brief Test if this vector is shorter than \p vec
    bool operator<(const Vector3& vec)  const;


    ///\brief Test if this vector is longer than \p vec
    bool operator>(const Vector3& vec)  const;


    ///\brief Test if this vector is shorter than or equal to \p vec
    bool operator<=(const Vector3& vec) const;

    
    ///\brief Test if this vector is longer than or equal to \p vec
    bool operator>=(const Vector3& vec) const;
    

    ///\brief Access members by index
    float& operator[](unsigned int index);


    ///\copydoc Vector3::operator[](unsigned int)
    float operator[](unsigned int index) const;


    ///\copydoc operator*(float n) const
    friend Vector3 operator*(float n, const Vector3& vec);

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

#endif