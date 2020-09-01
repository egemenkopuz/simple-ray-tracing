#include "Camera.h"

Camera::Camera(const Point3D & position, const Vector3D & target, const Vector3D & verticalDirection,float fov, float aspectRatio)
	: position(position), direction((target - position).normalized()), verticalDirection(verticalDirection)
{
	this->horizontalDirection = cross(this->verticalDirection, this->direction).normalized();
	this->verticalDirection = cross(this->direction, this->horizontalDirection);

	viewHeight = tan(fov);
	viewWidth = viewHeight * aspectRatio;
}

Ray Camera::makeRay(Vector2D point) const
{
	Vector3D dir = direction + point.coord_X * viewWidth * horizontalDirection + point.coord_Y * viewHeight * verticalDirection;
	return Ray(this->position, dir.normalized());
}

Vector3D Camera::dir(Vector2D point) const
{
	return (direction + point.coord_X * viewWidth * horizontalDirection + point.coord_Y * viewHeight * verticalDirection).normalized();
}
