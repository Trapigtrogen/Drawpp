#ifndef DPP_VECTOR4_H
#define DPP_VECTOR4_H

struct Vector4
{
    Vector4();
    Vector4(float v);
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector4& other);


    static Vector4 random();
    static Vector4 random(class Random& gen);


    float mag() const;
    float magSq() const;


    Vector4 operator+(const Vector4& vec) const;


    Vector4 operator-(const Vector4& vec) const;


    Vector4 operator-()                   const;


    Vector4 operator*(float n)            const;


    Vector4 operator*(const Vector4& vec) const;
    

    Vector4 operator/(float n)            const;

    
    Vector4 operator/(const Vector4& vec) const;


    Vector4& operator=(const Vector4& vec);


    Vector4& operator+=(const Vector4& vec);


    Vector4& operator-=(const Vector4& vec);


    Vector4& operator*=(float n);


    Vector4& operator*=(const Vector4& vec);


    Vector4& operator/=(float n);


    Vector4& operator/=(const Vector4& vec);

    bool operator==(const Vector4& vec) const;
    bool operator!=(const Vector4& vec) const;
    bool operator<(const Vector4& vec)  const;
    bool operator>(const Vector4& vec)  const;
    bool operator<=(const Vector4& vec) const;
    bool operator>=(const Vector4& vec) const;
    
    float& operator[](unsigned int index);

    float operator[](unsigned int index) const;

    friend Vector4 operator*(float n, const Vector4& vec);

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};

#endif