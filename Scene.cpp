#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto Object : this->objects)
		delete Object;
	for (auto Light : this->lights)
		delete Light;
	for (auto ALight : this->ambientLights)
		delete ALight;
}

void Scene::setCamera(const Camera & camera)
{
	this->camera = camera;
}
void Scene::setSettings(const Settings & settings)
{
	this->settings = settings;
}

Image * Scene::capture()
{
	unsigned int resWidth = this->settings.resW, resHeight = this->settings.resH;
	Image * img = new Image(resWidth, resHeight);

	for (int w = 0; w < resWidth; w++) {
		for (int h = 0; h < resHeight; h++) {
			Color currentPixel = Color(0.0f);
			Vector2D screenCoord((2.0f * w) / resWidth - 1.0f, (-2.0f * h) / resHeight + 1.0f);
			Ray ray(this->camera.position, this->camera.dir(screenCoord));
			currentPixel = this->getColor(ray, this->settings.bounce);
			img->setColor(w, h, currentPixel);
		}
	}
	return img;
}

Color Scene::getColor(const Ray & ray, int bounce)
{
	Intersection * closeInt = closestIntersection(ray);
	Color color;

	if (closeInt == nullptr) color = this->settings.backColor;
	else
	{
		Material *material = closeInt->object->material;
		
		color = material->color * (getAmbientColor() + (getDiffuseColor(closeInt->point, closeInt->normal) * material->diffuse));

		if (material->specular != 0.0f) 
		{
			color += (getSpecularColor(ray.direction, *closeInt, material->specular) * (material->specular * 3.0f));
		}

		if (material->mirror != 0.0f && bounce > 0) 
		{
			color += (getColor(Ray(closeInt->point, closeInt->reflection), bounce - 1) * material->mirror);
		}
		color.clamp();
	}
	delete closeInt;
	return color;
}


void Scene::addObject(Object * object)
{
	objects.push_back(object);
}

void Scene::addLight(PointLight * light)
{
	lights.push_back(light);
}

void Scene::addAmbientLight(AmbientLight * light)
{
	ambientLights.push_back(light);
}

unsigned int Scene::getNumObjects()
{
	return objects.size();
}

unsigned int Scene::getNumLights()
{
	return lights.size();
}

unsigned int Scene::getNumAmbientLights()
{
	return ambientLights.size();
}

Intersection *Scene::closestIntersection(const Ray &ray) 
{
	Intersection *closestIntersection = nullptr;
	Intersection *intersection;
	for (auto &Object : this->objects)
	{
		intersection = Object->intersect(ray);

		if (intersection != nullptr && (closestIntersection == nullptr || intersection->distance < closestIntersection->distance)) 
		{
			delete closestIntersection;
			closestIntersection = intersection;
		}
		else 
		{
			delete intersection;
		}
	}

	return closestIntersection;
}

Color Scene::getDiffuseColor(const Point3D & iPoint, const Vector3D & iNormal) 
{
	Color color(0.0f);
	for (PointLight *light : this->lights) 
	{
		if (!isOccluded(iPoint, light->position)) {
			Vector3D lightToIntersection = (light->position - iPoint).normalized();
			float t = dot(iNormal, lightToIntersection);
			color += ((light->color * light->intensity) * fmax(0.0f, dot(iNormal,lightToIntersection)));
		}
	}
	return color;
}

Color Scene::getSpecularColor(const Vector3D &view_direction, const Intersection &intersection, float k) 
{
	Color color(0.0f);

	for (PointLight *light : this->lights) 
	{
		if (!isOccluded(intersection.point, light->position)) 
		{
			float specular_intensity = dot(intersection.reflection,(light->position - intersection.point).normalized());
			color += (light->color * light->intensity * pow(fmax(0.0f, specular_intensity), floor(pow(k + 1.0f, 10.0f))));
		}
	}

	return color;
}

Color Scene::getAmbientColor()
{
	Color color(0.0f);
	for (AmbientLight *light : this->ambientLights)
	{
		color += (light->color * light->intensity);
	}
	return color;
}

bool Scene::isOccluded(const Vector3D &a, const Vector3D &b) 
{

	Ray ray(a, b - a);
	for (Object *object : this->objects)
	{
		Intersection * intersection = object->intersect(ray);
		if (intersection) {
			delete intersection;
			return true;
		}
	}
	return false;
}