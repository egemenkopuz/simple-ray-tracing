#ifndef VECTORMATH_H_EK
#define VECTORMATH_H_EK

#define PI 3.1415926f

#include <cmath>

class Vector3D {
public:
	float coord_X, coord_Y, coord_Z;

	Vector3D();
	Vector3D(float f);
	Vector3D(float x, float y, float z);

	virtual ~Vector3D() = default;

	inline float length2();
	inline float length();

	float normalize();
	Vector3D normalized();

	Vector3D& operator=(const Vector3D& rhs);
	Vector3D& operator+=(const Vector3D& rhs);
	Vector3D& operator-=(const Vector3D& rhs);
	Vector3D& operator*=(const Vector3D& rhs);
	Vector3D& operator/=(const Vector3D& rhs);
	Vector3D& operator=(float rhs);
	Vector3D& operator+=(float rhs);
	Vector3D& operator-=(float rhs);
	Vector3D& operator*=(float rhs);
	Vector3D& operator/=(float rhs);

	Vector3D& rotateX(const float &angle);
	Vector3D& rotateY(const float &angle);
	Vector3D& rotateZ(const float &angle);
};

inline Vector3D operator+(const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.coord_X + v2.coord_X, v1.coord_Y + v2.coord_Y, v1.coord_Z + v2.coord_Z);
}

inline Vector3D operator-(const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.coord_X - v2.coord_X, v1.coord_Y - v2.coord_Y, v1.coord_Z - v2.coord_Z);
}

inline Vector3D operator*(const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.coord_X * v2.coord_X, v1.coord_Y * v2.coord_Y, v1.coord_Z * v2.coord_Z);
}

inline Vector3D operator*(const Vector3D& v, float f)
{
	return Vector3D(v.coord_X * f, v.coord_Y * f, v.coord_Z * f);
}

inline Vector3D operator*(float f, const Vector3D& v)
{
	return Vector3D(f * v.coord_X, f * v.coord_Y, f * v.coord_Z);
}

inline Vector3D operator/(const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.coord_X / v2.coord_X, v1.coord_Y / v2.coord_Y, v1.coord_Z / v2.coord_Z);
}

inline Vector3D operator/(const Vector3D& v, float f)
{
	return Vector3D(v.coord_X / f, v.coord_Y / f, v.coord_Z / f);
}

inline Vector3D operator/(float f, const Vector3D& v)
{
	return Vector3D(f / v.coord_X, f / v.coord_Y, f / v.coord_Z);
}

typedef Vector3D Point3D;

class Vector2D {
public:
	float coord_X, coord_Y;

	Vector2D();
	Vector2D(float f);
	Vector2D(float x, float y);

	virtual ~Vector2D() = default;

	Vector2D& operator=(const Vector2D& rhs);
	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);
	Vector2D& operator*=(const Vector2D& rhs);
	Vector2D& operator/=(const Vector2D& rhs);
	Vector2D& operator=(float rhs);
	Vector2D& operator+=(float rhs);
	Vector2D& operator-=(float rhs);
	Vector2D& operator*=(float rhs);
	Vector2D& operator/=(float rhs);
};

inline Vector2D operator+(const Vector2D& v1, const Vector2D& v2) 
{
	return Vector2D(v1.coord_X + v2.coord_X, v1.coord_Y + v2.coord_Y);
}

inline Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.coord_X - v2.coord_X, v1.coord_Y - v2.coord_Y);
}

inline Vector2D operator*(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.coord_X * v2.coord_X, v1.coord_Y * v2.coord_Y);
}

inline Vector2D operator*(const Vector2D& v1, float f)
{
	return Vector2D(v1.coord_X * f, v1.coord_Y * f);
}

inline Vector2D operator*(float f, const Vector2D& v2)
{
	return Vector2D(f * v2.coord_X, f * v2.coord_Y);
}

inline Vector2D operator/(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.coord_X / v2.coord_X, v1.coord_Y / v2.coord_X);
}

inline Vector2D operator/(const Vector2D& v1, float f)
{
	return Vector2D(v1.coord_X / f, v1.coord_Y / f);
}

inline Vector2D operator/(float f, const Vector2D& v2)
{
	return Vector2D(f / v2.coord_X, f / v2.coord_Y);
}

typedef Vector2D Point2D;

float dot(Vector3D v1, Vector3D v2);
float dot(Vector2D v1, Vector2D v2);
Vector3D cross(Vector3D v1, Vector3D v2);
Vector2D cross(Vector2D v1, Vector2D v2);

inline float sqr(float n);

#endif