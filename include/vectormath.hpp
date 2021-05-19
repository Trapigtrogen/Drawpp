#ifndef DPP_VECTORMATH_H
#define DPP_VECTORMATH_H

#include <vector2.hpp>
#include <vector3.hpp>
#include <vector4.hpp>

float dot(const Vector2& a, const Vector2& b);
float dot(const Vector3& a, const Vector3& b);
float dot(const Vector4& a, const Vector4& b);

float cross(const Vector2& a, const Vector2& b);
Vector3 cross(const Vector3& a, const Vector3& b);

float angleBetween(const Vector2& a, const Vector2& b);
float angleBetween(const Vector3& a, const Vector3& b);
float angleBetween(const Vector4& a, const Vector4& b);

Vector2 lerp(const Vector2& a, const Vector2& b, float t);
Vector3 lerp(const Vector3& a, const Vector3& b, float t);
Vector4 lerp(const Vector4& a, const Vector4& b, float t);

Vector2 normalize(const Vector2& vec);
Vector3 normalize(const Vector3& vec);
Vector4 normalize(const Vector4& vec);

Vector2 setMag(const Vector2& vec, float m);
Vector3 setMag(const Vector3& vec, float m);
Vector4 setMag(const Vector4& vec, float m);

Vector2 limit(const Vector2& vec, float m);
Vector3 limit(const Vector3& vec, float m);
Vector4 limit(const Vector4& vec, float m);

Vector2 abs(const Vector2& vec);
Vector3 abs(const Vector3& vec);
Vector4 abs(const Vector4& vec);

#endif