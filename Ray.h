#ifndef RAY_H_EK
#define RAY_H_EK

// In order to prevent bouncing rays self-intersecting
#define RAY_T_MIN 0.0001f

// 'Infinite' distance, used as a default value
#define RAY_T_MAX 1.0e30f

#include "VectorMath.h"

class Ray {
public:
	Point3D origin;
	Vector3D direction;
	float tMax;

	Ray();
	Ray(const Ray& r);
	Ray(const Point3D& origin, const Vector3D& direcion, float tMax = RAY_T_MAX);

	virtual ~Ray() = default;

	Ray& operator=(const Ray& rhs);

	Point3D calculate(float t) const;
};

#endif 