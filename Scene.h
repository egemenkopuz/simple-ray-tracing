#ifndef SCENE_H_EK
#define SCENE_H_EK

#include <vector>
#include "Object.h"
#include "Image.h"
#include "Light.h"
#include "Ray.h"
#include "Color.h"
#include "Camera.h"

struct Settings {
public:
	unsigned int resW;		// resolution width
	unsigned int resH;		// resolution height
	float resRatio;			// resolution ratio
	float fov;				// field of view
	Color backColor;		// background color
	unsigned int bounce;	// bounce count

	Settings() = default;
	Settings(unsigned int resW, unsigned int resH, const Color & backColor, unsigned int bounce, float fov = 25.0f * PI / 180.0f)
		: resW(resW), resH(resH), fov(fov), resRatio((float)resW/(float)resH), backColor(backColor), bounce(bounce) {}
};

class Scene {
private:
	std::vector<Object*> objects;	
	std::vector<PointLight*> lights;
	std::vector<AmbientLight*> ambientLights;
	Settings settings;
	Camera camera;
public:
	Scene();
	virtual ~Scene();

	Image * capture();
	Color getColor(const Ray & ray, int bounce);
	Color getDiffuseColor(const Point3D & iPoint, const Vector3D & iNormal);
	Color getSpecularColor(const Vector3D &view_direction, const Intersection &intersection, float k);
	Color getAmbientColor();

	void setCamera(const Camera& camera);
	void setSettings(const Settings& settings);
	void addObject(Object* shape);
	void addLight(PointLight* light);
	void addAmbientLight(AmbientLight* light);
	
	unsigned int getNumObjects();
	unsigned int getNumLights();
	unsigned int getNumAmbientLights();

	Intersection * closestIntersection(const Ray & ray);
	bool isOccluded(const Vector3D &a, const Vector3D &b);

	float getResRatio() { return this->settings.resRatio; }
	float getFov() { return this->settings.fov; }
};

#endif 