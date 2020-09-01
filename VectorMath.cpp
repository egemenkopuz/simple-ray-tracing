#include "VectorMath.h"

Vector3D::Vector3D() : coord_X(0.0f), coord_Y(1.0f), coord_Z(0.0f)
{
}

Vector3D::Vector3D(float f) : coord_X(f), coord_Y(f), coord_Z(f)
{
}

Vector3D::Vector3D(float x, float y, float z) : coord_X(x), coord_Y(y), coord_Z(z)
{
}

inline float Vector3D::length2()
{
	return sqr(coord_X) + sqr(coord_Y) + sqr(coord_Z);
}

inline float Vector3D::length()
{
	return std::sqrt(length2());
}

float Vector3D::normalize()
{
	float len = length();
	*this /= len;
	return len;
}

Vector3D Vector3D::normalized()
{
	Vector3D vec(*this);
	vec.normalize();
	return vec;
}

Vector3D & Vector3D::operator=(const Vector3D & rhs)
{
	coord_X = rhs.coord_X;
	coord_Y = rhs.coord_Y;
	coord_Z = rhs.coord_Z;
	return *this;
}

Vector3D & Vector3D::operator+=(const Vector3D & rhs)
{
	coord_X += rhs.coord_X;
	coord_Y += rhs.coord_Y;
	coord_Z += rhs.coord_Z;
	return *this;
}

Vector3D & Vector3D::operator-=(const Vector3D & rhs)
{
	coord_X -= rhs.coord_X;
	coord_Y -= rhs.coord_Y;
	coord_Z -= rhs.coord_Z;
	return *this;
}

Vector3D & Vector3D::operator*=(const Vector3D & rhs)
{
	coord_X *= rhs.coord_X;
	coord_Y *= rhs.coord_Y;
	coord_Z *= rhs.coord_Z;
	return *this;
}

Vector3D & Vector3D::operator/=(const Vector3D & rhs)
{
	coord_X /= rhs.coord_X;
	coord_Y /= rhs.coord_Y;
	coord_Z /= rhs.coord_Z;
	return *this;
}

Vector3D & Vector3D::operator=(float rhs)
{
	coord_X = rhs;
	coord_Y = rhs;
	coord_Z = rhs;
	return *this;
}

Vector3D & Vector3D::operator+=(float rhs)
{
	coord_X += rhs;
	coord_Y += rhs;
	coord_Z += rhs;
	return *this;
}

Vector3D & Vector3D::operator-=(float rhs)
{
	coord_X -= rhs;
	coord_Y -= rhs;
	coord_Z -= rhs;
	return *this;
}

Vector3D & Vector3D::operator*=(float rhs)
{
	coord_X *= rhs;
	coord_Y *= rhs;
	coord_Z *= rhs;
	return *this;
}

Vector3D & Vector3D::operator/=(float rhs)
{
	coord_X /= rhs;
	coord_Y /= rhs;
	coord_Z /= rhs;
	return *this;
}

Vector3D & Vector3D::rotateX(const float & angle)
{
	float _y = coord_Y; float _z = coord_Z;
	coord_Y = _y * cos(angle) - _z * sin(angle);
	coord_Z = _y * sin(angle) + _z * cos(angle);
	return *this;
}

Vector3D & Vector3D::rotateY(const float & angle)
{
	float _x = coord_X; float _z = coord_Z;
	coord_X = _z * sin(angle) + _x * cos(angle);
	coord_Z = _z * cos(angle) - _x * sin(angle);
	return *this;
}

Vector3D & Vector3D::rotateZ(const float & angle)
{
	float _x = coord_X; float _y = coord_Y;
	coord_X = _x * cos(angle) - coord_Y * sin(angle);
	coord_Y = _x * sin(angle) + coord_Y * cos(angle);
	return *this;
}

Vector2D::Vector2D() : coord_X(0.0f), coord_Y(0.0f)
{
}

Vector2D::Vector2D(float f) : coord_X(f), coord_Y(f)
{
}

Vector2D::Vector2D(float x, float y) : coord_X(x), coord_Y(y)
{
}

Vector2D & Vector2D::operator=(const Vector2D & rhs)
{
	coord_X = rhs.coord_X;
	coord_Y = rhs.coord_Y;
	return *this;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs)
{
	coord_X += rhs.coord_X;
	coord_Y += rhs.coord_Y;
	return *this;
}

Vector2D & Vector2D::operator-=(const Vector2D & rhs)
{
	coord_X -= rhs.coord_X;
	coord_Y -= rhs.coord_Y;
	return *this;
}

Vector2D & Vector2D::operator*=(const Vector2D & rhs)
{
	coord_X *= rhs.coord_X;
	coord_Y *= rhs.coord_Y;
	return *this;
}

Vector2D & Vector2D::operator/=(const Vector2D & rhs)
{
	coord_X /= rhs.coord_X;
	coord_Y /= rhs.coord_Y;
	return *this;
}

Vector2D & Vector2D::operator=(float rhs)
{
	coord_X = rhs;
	coord_Y = rhs;
	return *this;
}

Vector2D & Vector2D::operator+=(float rhs)
{
	coord_X += rhs;
	coord_Y += rhs;
	return *this;
}

Vector2D & Vector2D::operator-=(float rhs)
{
	coord_X -= rhs;
	coord_Y -= rhs;
	return *this;
}

Vector2D & Vector2D::operator*=(float rhs)
{
	coord_X *= rhs;
	coord_Y *= rhs;
	return *this;
}

Vector2D & Vector2D::operator/=(float rhs)
{
	coord_X /= rhs;
	coord_Y /= rhs;
	return *this;
}

float dot(Vector3D v1, Vector3D v2)
{
	return v1.coord_X * v2.coord_X +
		v1.coord_Y * v2.coord_Y +
		v1.coord_Z * v2.coord_Z;
}

float dot(Vector2D v1, Vector2D v2)
{
	return v1.coord_X * v2.coord_Y +
		v1.coord_Y * v2.coord_Y;
}

Vector3D cross(Vector3D v1, Vector3D v2)
{
	return Vector3D(v1.coord_Y * v2.coord_Z - v1.coord_Z * v2.coord_Y,
		v1.coord_Z * v2.coord_X - v1.coord_X * v2.coord_Z,
		v1.coord_X * v2.coord_Y - v1.coord_Y * v2.coord_X);
}

Vector2D cross(Vector2D v1, Vector2D v2)
{
	return Vector2D(v1.coord_X * v2.coord_Y - v1.coord_Y * v2.coord_X);
}

inline float sqr(float n)
{
	return n * n;
}
