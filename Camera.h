#ifndef CAMERA_H_EK
#define CAMERA_H_EK

#include "Ray.h"

class Camera {
public:
	Vector3D position, direction,
		horizontalDirection, verticalDirection;
	double viewWidth, viewHeight;

	Camera() = default;

	Camera(const Point3D &position, const Vector3D &target, const Vector3D &verticalDirection,float fov, float aspecRatio);
	virtual Ray makeRay(Vector2D point) const;
	virtual Vector3D dir(Vector2D point) const;
};

#endif