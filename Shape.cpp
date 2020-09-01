#include "Shape.h"

Plane::Plane(const Point3D & position, const Vector3D & normal) : position(position), normal(normal)
{
	this->normal = this->normal.normalized();
}

Intersection * Plane::intersect(Ray & ray)
{
	// checking if there is an intersetion
	float dDotN = dot(ray.direction, normal);	// direction . normal

	if (dDotN == 0.0f) return nullptr;	// ray is not embedded in the plane, not intersected

	// finding the point of intersection
	float t = dot(position - ray.origin, normal) / dDotN;

	if (t <= RAY_T_MIN) return nullptr;	// outside of relevant range

	Point3D intersectionPoint = ray.origin + (ray.direction * t) + this->normal / 1.0e10f;

	return new Intersection(t, intersectionPoint, this->normal, (ray.direction - (this->normal *2.0f * dot(this->normal, ray.direction))).normalized(), nullptr);
}

Sphere::Sphere(const Point3D & center, float r) : center(center), radius(r)
{
}

Intersection * Sphere::intersect(Ray & r)
{
	// Transform ray to only consider origin-centered sphere
	Ray ray = r;
	ray.origin -= center;

	// Calculate quadratic coefficients
	float a = ray.direction.length2();
	float b = 2.0f * dot(ray.direction, ray.origin);
	float c = ray.origin.length2() - sqr(radius);

	// check whether there is an intersection
	float discriminant = sqr(b) - 4.0f * a * c;

	float distance;	// how far away from ray's origin position

	if (discriminant < 0.0f) return nullptr;	// no solution
	else if (discriminant == 0.0f) 
	{
		// one solution
		distance = fmax(0.0f, -b / (2 * a));
	}
	else 
	{
		// two solutions
		float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
		float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

		if (t1 > RAY_T_MIN && t1 < t2) distance = t1;
		else if (t2 > RAY_T_MIN && t2 < t1) distance = t2;
		else return nullptr;
	}

	Vector3D normal = ((ray.origin + (ray.direction * distance)) - this->center).normalized();
	return new Intersection(distance, ray.origin + (ray.direction * distance), normal,
		(ray.direction - (normal * 2.0f * dot(normal, ray.direction))).normalized(), nullptr);
}