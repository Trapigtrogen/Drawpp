#ifndef DPP_VECTOR2_H
#define DPP_VECTOR2_H

struct Vector2
{
    Vector2();
    Vector2(float v);
    Vector2(float x, float y);
    Vector2(const Vector2& other);


    static Vector2 random();
    static Vector2 random(class Random& gen);
    static Vector2 fromAngle(float angle);


    float mag() const;
    float magSq() const;
    float heading() const;


    Vector2 rotate(float angle) const;

    
    Vector2 operator+(const Vector2& vec) const;


    Vector2 operator-(const Vector2& vec) const;


    Vector2 operator-()                   const;


    Vector2 operator*(float n)            const;


    Vector2 operator*(const Vector2& vec) const;
    

    Vector2 operator/(float n)            const;

    
    Vector2 operator/(const Vector2& vec) const;


    Vector2& operator=(const Vector2& vec);


    Vector2& operator+=(const Vector2& vec);


    Vector2& operator-=(const Vector2& vec);


    Vector2& operator*=(float n);


    Vector2& operator*=(const Vector2& vec);


    Vector2& operator/=(float n);


    Vector2& operator/=(const Vector2& vec);

    bool operator==(const Vector2& vec) const;
    bool operator!=(const Vector2& vec) const;
    bool operator<(const Vector2& vec)  const;
    bool operator>(const Vector2& vec)  const;
    bool operator<=(const Vector2& vec) const;
    bool operator>=(const Vector2& vec) const;
    
    float& operator[](unsigned int index);

    float operator[](unsigned int index) const;

    friend Vector2 operator*(float n, const Vector2& vec);

    float x = 0.0f;
    float y = 0.0f;
};

#endif