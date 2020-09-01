#ifndef LIGHT_H_EK
#define LIGHT_H_EK

#include "VectorMath.h"
#include "Color.h"

class Light {
public:
	Color color;
	float intensity;

	Light(const Color &color, float intensity) 
		: color(color), intensity(fmin(fmax(0.0f, intensity), 1.0f)) {}
};

class AmbientLight : public Light {
public:
	AmbientLight(const Color &color, float intensity)
		: Light(color, intensity) {}
};

class PointLight : public Light {
public:
	Vector3D position;
	PointLight(const Color &color, float intensity, const Vector3D &position)
		: Light(color, intensity), position(position) {}
};

#endif 