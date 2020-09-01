#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Ray.h"
#include "VectorMath.h"

class Object;

class Intersection {
public:
	float distance;
	Point3D point;
	Vector3D normal;
	Vector3D reflection;
	Object * object;

	explicit Intersection(float distance, const Point3D & point, const Vector3D & normal, const Vector3D & reflection, Object * object)
		: distance(distance), point(point), normal(normal), reflection(reflection), object(object) {}
};

#endif