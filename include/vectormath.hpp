#ifndef DPP_VECTORMATH_H
#define DPP_VECTORMATH_H

#include <vector2.hpp>
#include <vector3.hpp>
#include <vector4.hpp>


///\file

///\addtogroup drawpp_function_api
///@{


///\defgroup drawpp_vectormath_api Vector Math
///\addtogroup drawpp_vectormath_api
///@{

///\brief Get dot product between \p a and \p b
float dot(const Vector2& a, const Vector2& b);


///\copydoc dot(const Vector2&,const Vector2&)
float dot(const Vector3& a, const Vector3& b);


///\copydoc dot(const Vector2&,const Vector2&)
float dot(const Vector4& a, const Vector4& b);



///\brief Get 2D cross product between \p a and \p b
///
///Implemented as \code a.x * b.y - a.y * b.x \endcode
float cross(const Vector2& a, const Vector2& b);


///\brief Get cross product between \p a and \p b
Vector3 cross(const Vector3& a, const Vector3& b);



///\brief Get the angle between \p a and \p vb in radians
float angleBetween(const Vector2& a, const Vector2& b);


///\copydoc angleBetween(const Vector2&,const Vector2&)
float angleBetween(const Vector3& a, const Vector3& b);


///\copydoc angleBetween(const Vector2&,const Vector2&)
float angleBetween(const Vector4& a, const Vector4& b);



///\brief Linearly interpolate between \p a and \p b by \p t
Vector2 lerp(const Vector2& a, const Vector2& b, float t);


///\copydoc lerp(const Vector2&,const Vector2&,float)
Vector3 lerp(const Vector3& a, const Vector3& b, float t);


///\copydoc lerp(const Vector2&,const Vector2&,float)
Vector4 lerp(const Vector4& a, const Vector4& b, float t);



///\brief Normalize \p vec
Vector2 normalize(const Vector2& vec);


///\copydoc normalize(const Vector2&)
Vector3 normalize(const Vector3& vec);


///\copydoc normalize(const Vector2&)
Vector4 normalize(const Vector4& vec);



///\brief Set the magnitude of \p vec to \p len
Vector2 setMag(const Vector2& vec, float m);


///\copydoc setMag(const Vector2&,float)
Vector3 setMag(const Vector3& vec, float m);


///\copydoc setMag(const Vector2&,float)
Vector4 setMag(const Vector4& vec, float m);



///\brief Limit the magnitude of \p vec to \p m
Vector2 limit(const Vector2& vec, float m);


///\copydoc limit(const Vector2&,float)
Vector3 limit(const Vector3& vec, float m);


///\copydoc limit(const Vector2&,float)
Vector4 limit(const Vector4& vec, float m);



///\brief Apply std::abs to each member
Vector2 abs(const Vector2& vec);


///\copydoc abs(const Vector2&)
Vector3 abs(const Vector3& vec);


///\copydoc abs(const Vector2&)
Vector4 abs(const Vector4& vec);


// End group drawpp_vectormath_api
///@}


// End group drawpp_function_api
///@}

#endif