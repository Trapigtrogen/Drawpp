#ifndef DPP_VECTOR3_H
#define DPP_VECTOR3_H

#include <cstdint>
#include <vector>

class Random;

///\brief A basic vector3 class
struct DVector
{
    ///\brief All values are initialized to zero
    DVector();


    ///\brief All values are initialized to \p n
    DVector(float n);


    ///\brief Initialize x and y, and set z to zero
    DVector(float x, float y);


    ///\brief Initialize x, y and z
    DVector(float x, float y, float z);


    DVector(const DVector&) = default;
    DVector(DVector&&) = default;
    ~DVector() = default;


    ///\brief Set x, y and z
    ///\return Reference to self
    DVector& set(float x, float y, float z);


    ///\brief Set x and y, z is left untouched
    ///\return Reference to self
    DVector& set(float x, float y);


    ///\brief Copy values from another vector
    ///\return Reference to self
    DVector& set(const DVector& v);


    ///\brief Generate a random direction vector in xy plane
    ///\return DVector
    static DVector random2D();


    ///\brief Generate a random direction vector in xy plane using \p gen
    ///\return DVector
    static DVector random2D(Random& gen);


    ///\brief Generate a random direction vector in xy plane, and assing result to target
    ///\return Reference to target
    static DVector& random2D(DVector& target);


    ///\brief Generate a random direction vector in xy plane using \p gen, and assing result to target
    ///\return Reference to target
    static DVector& random2D(DVector& target, Random& gen);


    ///\brief Generate a random direction vector
    ///\return DVector
    static DVector random3D();


    ///\brief Generate a random direction vector using \p gen
    ///\return DVector
    static DVector random3D(Random& gen);


    ///\brief Generate a random direction vector, and assing result to target
    ///\return Reference to target
    static DVector& random3D(DVector& target);


    ///\brief Generate a random direction vector using \p gen, and assing result to target
    ///\return Reference to target
    static DVector& random3D(DVector& target, Random& gen);


    ///\brief Get a direction vector from radians
    ///\return DVector
    static DVector fromAngle(float angle);
 

    ///\brief Get a direction vector from radians, and assign it to \p target 
    ///\return Reference to \p target
    static DVector& fromAngle(float angle, DVector& target);


    ///\brief Copy the vector
    ///
    ///Prefer the '=' operator instead of copy().
    ///\return DVector
    DVector copy() const;


    ///\brief Get the vector magnitude
    ///\return Magnitude
    float mag() const;


    ///\brief Get the vector magnitude squared
    ///\return Magnitude squred
    float magSq() const;


    ///\brief Add \p v1 to this vector
    ///\return Reference to self
    DVector& add(const DVector& v1);


    ///\brief Add another vector to this vector
    ///
    ///z is left untouched.
    ///\return Reference to self
    DVector& add(float x, float y);


    ///\brief Add another vector to this vector
    ///\return Reference to self
    DVector& add(float x, float y, float z);


    ///\brief Add \p v1 to \p v2
    ///\return DVector
    static DVector add(const DVector& v1, const DVector& v2);


    ///\brief Add \p v1 to \p v2, and assign result to \p target
    ///\return Reference to \p target
    static DVector& add(const DVector& v1, const DVector& v2, DVector& target);


    ///\brief Substract \p v1 from this vector
    ///\return Reference to self
    DVector& sub(const DVector& v1);


    ///\brief Substract another vector from this vector
    ///
    ///z is left untouched.
    ///\return Reference to self
    DVector& sub(float x, float y);


    ///\brief Substract another vector from this vector
    ///\return Reference to self
    DVector& sub(float x, float y, float z);


    ///\brief Substract \p v2 from \p v1
    ///\return DVector
    static DVector sub(const DVector& v1, const DVector& v2);


    ///\brief Substract \p v2 from \p v1, and assign result to \p target
    ///\return Reference to \p target
    static DVector& sub(const DVector& v1, const DVector& v2, DVector& target);


    ///\brief Multiply x, y and z by \p n
    ///\return Reference to self
    DVector& mult(float n);


    ///\brief Multiply \p v1 by \p n
    ///\return DVector
    static DVector mult(const DVector& v1, float n);


    ///\brief Multiply \p v1 by \p n, and assign result to \p target
    ///\return Reference to \p target
    static DVector& mult(const DVector& v1, float n, DVector& target);


    ///\brief Divide x, y and z by \p n
    ///\return Reference to self
    DVector& div(float n);


    ///\brief Divide \p v1 by \p n
    ///\return DVector
    static DVector div(const DVector& v1, float n);


    ///\brief Divide \p v1 by \p n, and assign result to \p target
    ///\return Reference to \p target
    static DVector& div(const DVector& v1, float n, DVector& target);


    ///\brief Get distance between this vector and \p v1
    ///\return Distance
    float dist(const DVector& v1) const;


    ///\brief Get distance between \p v1 and \p v2
    ///\return Distance
    static float dist(const DVector& v1, const DVector& v2);


    ///\brief Get dot product between this vector and \p v1
    ///\return Dot product
    float dot(const DVector& v1) const;


    ///\brief Get dot product between this vector and another vector
    ///\return Dot product
    float dot(float x, float y, float z) const;


    ///\brief Get dot product between \p v1 and \p v2
    ///\return Dot product
    static float dot(const DVector& v1, const DVector& v2);


    ///\brief Get cross product between this vector and \p v1
    ///\return DVector
    DVector cross(const DVector& v1) const;


    ///\brief Get cross product between this vector and \p v1, and assign result to \p target
    ///\return Reference to \p target
    DVector& cross(const DVector& v1, DVector& target) const;


    ///\brief Get cross product between \p v1 and \p v2, and assign result to \p target
    ///\return Reference to \p target
    static DVector& cross(const DVector& v1, const DVector& v2, DVector& target);


    ///\brief Get cross product between \p v1 and \p v2
    ///\return DVector
    static DVector cross(const DVector& v1, const DVector& v2);


    ///\brief Normalize this vector
    ///\return Reference to self
    DVector& normalize();


    ///\brief Normalize this vector, and assign result to \p target
    ///\return Reference to \p target
    DVector& normalize(DVector& target) const;

    ///\brief Get this vector normalized
    ///
    ///This vector is not modified.
    ///\return DVector
    DVector normalized() const;

    
    ///\brief Limit the magnitude of this vector to \p max
    ///\return Reference to self
    DVector& limit(float max);
    

    ///\brief Set the magnitude of this vector to \p len
    ///\return Reference to self
    DVector& setMag(float len);


    ///\brief Set the magnitude of this vector to \p len, and assign result to \p target
    ///
    ///This vector is not modified.
    ///\return Reference to \p target
    DVector& setMag(DVector& target, float len) const;

    
    ///\brief Get the heading of this vector (2D only)
    ///\return Heading
    float heading() const;


    ///\brief Rotate this vector by \p theta radians (2D only)
    ///\return Reference to self
    DVector& rotate(float theta);


    ///\brief Linearly interpolate between this vector and \p v1 by \p t
    ///\return Reference to self
    DVector& lerp(const DVector& v1, float t);


    ///\brief Linearly interpolate between this vector and another vector by \p t
    ///\return Reference to self
    DVector& lerp(float x, float y, float z, float t);


    ///\brief Linearly interpolate \p v1 and \p v2 by \p t
    ///\return DVector
    static DVector lerp(const DVector& v1, const DVector& v2, float t);


    ///\brief Get the angle between \p v1 and \p v2 in radians
    ///\return Angle
    static float angleBetween(const DVector& v1, const DVector& v2);


    ///\brief Get the DVector content as a std::vector
    ///\return std::vector
    std::vector<float> array() const;




    ///\brief Add \p vec to this vector
    ///\return DVector
    DVector operator+(const DVector& vec) const;


    ///\brief Substract \p vec from this vector
    ///\return DVector
    DVector operator-(const DVector& vec) const;


    ///\brief Invert this vector
    ///\return DVector
    DVector operator-()                   const;


    ///\brief Multiply this vector by \p n
    ///\return DVector
    DVector operator*(float n)            const;


    ///\brief Multiply each elements of this vector by elements of \p vec
    ///\return DVector
    DVector operator*(const DVector& vec) const;
    

    ///\brief Divide this vector by \p n
    ///\return DVector
    DVector operator/(float n)            const;


    ///\brief Assign \p vec to this vector
    ///\return Reference to self
    DVector& operator= (const DVector& vec);


    ///\brief Add \p vec to this vector, and assing result to this vector
    ///\return Reference to self
    DVector& operator+=(const DVector& vec);


    ///\brief Substract \p vec from this vector, and assing result to this vector
    ///\return Reference to self
    DVector& operator-=(const DVector& vec);


    ///\brief Multiply this vector by \p n, and assing result to this vector
    ///\return Reference to self
    DVector& operator*=(float n);


    ///\brief Multiply this vector by \p vec, and assing result to this vector
    ///\return Reference to self
    DVector& operator*=(const DVector& vec);


    ///\brief Divide this vector by \p n, and assing result to this vector
    ///\return Reference to self
    DVector& operator/=(float n);


    ///\brief Divide this vector by \p vec, and assing result to this vector
    ///\return Reference to self
    DVector& operator/=(const DVector& vec);

    bool operator==(const DVector& vec) const;
    bool operator!=(const DVector& vec) const;
    bool operator<(const DVector& vec)  const;
    bool operator>(const DVector& vec)  const;
    bool operator<=(const DVector& vec) const;
    bool operator>=(const DVector& vec) const;
    
    ///\brief Access members by index
    ///\return Value at \p index
    float& operator[](size_t index);

    ///\copydoc operator[](size_t index)
    float operator[](size_t index) const;

    ///\copydoc operator*(float n) const
    friend DVector operator*(float n, const DVector& vec);

    float x,y,z;
};

#endif