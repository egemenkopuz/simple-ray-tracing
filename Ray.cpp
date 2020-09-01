#include "Ray.h"

Ray::Ray() : origin(0.0f,0.0f,0.0f), direction(), tMax(RAY_T_MAX)
{
}

Ray::Ray(const Ray & ray) : origin(ray.origin), direction(ray.direction), tMax(RAY_T_MAX) 
{
}

Ray::Ray(const Point3D& origin, const Vector3D& direction, float tMax) : origin(origin), direction(direction), tMax(tMax) 
{
}

Ray & Ray::operator=(const Ray & ray)
{
	origin = ray.origin;
	direction = ray.direction;
	tMax = ray.tMax;
	return *this;
}

Point3D Ray::calculate(float t) const
{
	return origin + direction * t;	// p + dt
}