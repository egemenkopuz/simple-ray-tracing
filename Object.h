#ifndef OBJECT_H_EK
#define OBJECT_H_EK

#include "Shape.h"

class Object {
public:
	Material * material;
	Shape *shape;

	Object(Material * material, Shape * shape);
	~Object();

	Intersection * intersect(Ray ray);
};

#endif
