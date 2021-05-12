#ifndef DPP_VEC2F_H
#define DPP_VEC2F_H

///\private
struct vec2f
{
    float x = 0.0f, y = 0.0f;

    float len();
    static float dot(const vec2f& a, const vec2f& b);
    static vec2f lerp(const vec2f& a, const vec2f& b, float t);

    vec2f operator*(float n) const;
    vec2f operator/(float n) const;
    vec2f operator+(const vec2f& other) const;
    vec2f operator-(const vec2f& other) const;
    friend vec2f operator*(float n, const vec2f& other);
    friend vec2f operator/(float n, const vec2f& other);
};

#endif