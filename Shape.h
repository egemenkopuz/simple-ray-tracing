#ifndef SHAPE_H_EK
#define SHAPE_H_EK

#include "Intersection.h"
#include "Color.h"

class Material {
public:
	Color color;
	float diffuse;
	float specular;
	float mirror;

	virtual ~Material() = default;
	Material(const Color & color, float diffuse,float specular, float mirror) : color(color), diffuse(diffuse), specular(specular), mirror(mirror) {}
};

class Shape {
public:
	virtual ~Shape() = default;
	virtual Intersection * intersect(Ray & ray) = 0;
};

class Plane : public Shape {
protected:
	Point3D position;
	Vector3D normal;
public:
	Plane(const Point3D& position, const Vector3D& normal);
	virtual ~Plane() = default;
	virtual Intersection *  intersect(Ray & ray);
};

class Sphere : public Shape {
protected:
	Point3D center;
	float radius;
public:
	Sphere(const Point3D& center, float r);
	virtual ~Sphere() = default;
	virtual Intersection *  intersect(Ray & ray);
};

#endif