#ifndef DPP_VECTOR3_H
#define DPP_VECTOR3_H

struct Vector3
{
    Vector3();
    Vector3(float v);
    Vector3(float x, float y, float z);
    Vector3(const Vector3& other);


    static Vector3 random();
    static Vector3 random(class Random& gen);

    float mag() const;
    float magSq() const;


    Vector3 operator+(const Vector3& vec) const;


    Vector3 operator-(const Vector3& vec) const;


    Vector3 operator-()                   const;


    Vector3 operator*(float n)            const;


    Vector3 operator*(const Vector3& vec) const;
    

    Vector3 operator/(float n)            const;

    
    Vector3 operator/(const Vector3& vec) const;


    Vector3& operator=(const Vector3& vec);


    Vector3& operator+=(const Vector3& vec);


    Vector3& operator-=(const Vector3& vec);


    Vector3& operator*=(float n);


    Vector3& operator*=(const Vector3& vec);


    Vector3& operator/=(float n);


    Vector3& operator/=(const Vector3& vec);

    bool operator==(const Vector3& vec) const;
    bool operator!=(const Vector3& vec) const;
    bool operator<(const Vector3& vec)  const;
    bool operator>(const Vector3& vec)  const;
    bool operator<=(const Vector3& vec) const;
    bool operator>=(const Vector3& vec) const;
    
    float& operator[](unsigned int index);

    float operator[](unsigned int index) const;

    friend Vector3 operator*(float n, const Vector3& vec);

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

#endif