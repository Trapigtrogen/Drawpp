#ifndef DPP_VECTOR2_H
#define DPP_VECTOR2_H

///\brief Vector2 class
struct Vector2
{
    ///\brief All values are initialized to zero
    Vector2();


    ///\brief All values are initialized to \p v
    Vector2(float v);

    ///\brief Initialize x and y
    Vector2(float x, float y);


    Vector2(const Vector2&) = default;


    ///\brief Generate a random direction vector
    ///
    ///Uses the default random generator.
    static Vector2 random();


    ///\brief Generate a random direction vector using \p gen
    static Vector2 random(class Random& gen);


    ///\brief Get a direction vector from radians
    static Vector2 fromAngle(float angle);


    ///\brief Get the vector magnitude
    float mag() const;


    ///\brief Get the vector magnitude squared
    float magSq() const;


    ///\brief Get the heading of this vector as radians
    float heading() const;


    ///\brief Rotate this vector by \p theta radians
    Vector2 rotate(float angle) const;

    
    ///\brief Add \p vec to this vector
    Vector2 operator+(const Vector2& vec) const;


    ///\brief Substract \p vec from this vector
    Vector2 operator-(const Vector2& vec) const;


    ///\brief Invert this vector
    Vector2 operator-()                   const;


    ///\brief Multiply this vector by \p n
    Vector2 operator*(float n)            const;


    ///\brief Multiply elements of this vector by elements of \p vec
    Vector2 operator*(const Vector2& vec) const;
    

    ///\brief Divide this vector by \p n
    Vector2 operator/(float n)            const;

    
    ///\brief Divide elements of this vector by elements of \p vec
    Vector2 operator/(const Vector2& vec) const;


    ///\brief Assign \p vec to this vector
    Vector2& operator=(const Vector2& vec);


    ///\brief Add \p vec to this vector, and assing result to this vector
    Vector2& operator+=(const Vector2& vec);


    ///\brief Substract \p vec from this vector, and assing result to this vector
    Vector2& operator-=(const Vector2& vec);


    ///\brief Multiply this vector by \p n, and assing result to this vector
    Vector2& operator*=(float n);


    ///\brief Multiply this vector by \p vec, and assing result to this vector
    Vector2& operator*=(const Vector2& vec);


    ///\brief Divide this vector by \p n, and assing result to this vector
    Vector2& operator/=(float n);


    ///\brief Divide this vector by \p vec, and assing result to this vector
    Vector2& operator/=(const Vector2& vec);


    ///\brief Test if this vector and \p vec are the same
    bool operator==(const Vector2& vec) const;


    ///\brief Test if this vector and \p vec are not the same
    bool operator!=(const Vector2& vec) const;


    ///\brief Test if this vector is shorter than \p vec
    bool operator<(const Vector2& vec)  const;


    ///\brief Test if this vector is longer than \p vec
    bool operator>(const Vector2& vec)  const;


    ///\brief Test if this vector is shorter than or equal to \p vec
    bool operator<=(const Vector2& vec) const;

    
    ///\brief Test if this vector is longer than or equal to \p vec
    bool operator>=(const Vector2& vec) const;
    

    ///\brief Access members by index
    float& operator[](unsigned int index);


    ///\copydoc Vector2::operator[](unsigned int)
    float operator[](unsigned int index) const;


    ///\copydoc operator*(float n) const
    friend Vector2 operator*(float n, const Vector2& vec);

    float x = 0.0f;
    float y = 0.0f;
};

#endif