#include "Object.h"

Object::Object(Material * material, Shape * shape)
{
	this->material = material;
	this->shape = shape;
}

Object::~Object()
{
	delete material;
	delete shape;
}

Intersection * Object::intersect(Ray ray)
{
	Intersection *intersection = this->shape->intersect(ray);
	if (intersection != nullptr) {
		intersection->object = this;
	}
	return intersection;
}
