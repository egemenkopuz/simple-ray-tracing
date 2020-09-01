#ifndef FILEIO_H_EK

#include "lodepng.h"
#include "Image.h"
#include <sstream>

void writeToPNG(Image * img, std::string outputFileName)
{
	std::vector<unsigned char> image;
	image.resize(img->getWidth() * img->getHeight() * 4);
	std::vector<unsigned char>::iterator imageIterator = image.begin();
	Color *currentPixel = img->getPixels();

	while (imageIterator != image.end())
	{
		*imageIterator = (unsigned char)(currentPixel->r * 255.0f);
		imageIterator++;
		*imageIterator = (unsigned char)(currentPixel->g * 255.0f);
		imageIterator++;
		*imageIterator = (unsigned char)(currentPixel->b * 255.0f);
		imageIterator++;
		*imageIterator = 255;
		imageIterator++;
		currentPixel++;
	}
	LodePNG::encode(outputFileName, image, img->getWidth(), img->getHeight());
}

bool ConfigToScene(Scene * scene, std::string inputFileName)
{
	std::ifstream file(inputFileName);
	std::string line;

	bool flag0 = false;	// if settings are read or not
	bool flag1 = false;	// if camera settings are read or not

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string classifier;
		iss >> classifier;

		if (classifier == "settings" && !flag0)
		{
			unsigned int resW;		// resolution width
			unsigned int resH;		// resolution height
			float fov;				// field of view
			Color backColor;		// background color
			float r, g, b;
			int bounce;	// bounce count

			if (!(iss >> resW >> resH >> fov >> r >> g >> b >> bounce))
			{
				std::cout << "Invalid settings parameters, skipping!\n";
			}
			else
			{
				// currently skipping fov
				Settings settings(resW, resH, Color(r, g, b), bounce);
				scene->setSettings(settings);
				flag0 = true;
			}
		}
		else if (classifier == "camera" && !flag1)
		{
			if (flag0 == false)
			{
				std::cout << "General settings must be given before camera settings, skipping!\n";
			}
			else
			{
				float x, y, z;
				float t_x, t_y, t_z;
				float v_x, v_y, v_z;

				if (!(iss >> x >> y >> z >> t_x >> t_y >> t_z >> v_x >> v_y >> v_z))
				{
					std::cout << "Invalid camera parameters, skipping!\n";
				}
				else
				{
					float f = scene->getFov();
					float a = scene->getResRatio();
					Camera camera(Point3D(x, y, z), Vector3D(t_x, t_y, t_z), Vector3D(v_x, v_y, v_z), f, a);
					scene->setCamera(camera);
					flag1 = true;
				}
			}
		}
		else if (classifier == "sphere")
		{
			float x, y, z, rad;
			float r, g, b;
			float diffuse, specular, mirror;

			if (!(iss >> x >> y >> z >> rad >> r >> g >> b >> diffuse >> specular >> mirror))
			{
				std::cout << "Invalid sphere parameters, skipping!\n";
			}
			else
			{
				Sphere * sphere = new Sphere(Point3D(x, y, z), rad);
				Material * material = new Material(Color(r, g, b), diffuse, specular, mirror);
				scene->addObject(new Object(material, sphere));
			}
		}
		else if (classifier == "plane")
		{
			float x, y, z;
			float n_x, n_y, n_z;
			float r, g, b;
			float diffuse, specular, mirror;

			if (!(iss >> x >> y >> z >> n_x >> n_y >> n_z >> r >> g >> b >> diffuse >> specular >> mirror))
			{
				std::cout << "Invalid plane parameters, skipping!\n";
			}
			else
			{
				Plane * plane = new Plane(Point3D(x, y, z), Vector3D(n_x, n_y, n_z));
				Material * material = new Material(Color(r, g, b), diffuse, specular, mirror);
				scene->addObject(new Object(material, plane));
			}
		}
		else if (classifier == "light")
		{
			float x, y, z;
			float r, g, b;
			float intensity;

			if (!(iss >> x >> y >> z >> r >> g >> b >> intensity))
			{
				std::cout << "Invalid light parameters, skipping!\n";
			}
			else
			{
				PointLight * light = new PointLight(Color(r, g, b), intensity, Point3D(x, y, z));
				scene->addLight(light);
			}
		}
		else if (classifier == "ambient")
		{
			float r, g, b;
			float intensity;

			if (!(iss >> r >> g >> b >> intensity))
			{
				std::cout << "Invalid ambient parameters, skipping!\n";
			}
			else
			{
				AmbientLight * alight = new AmbientLight(Color(r, g, b), intensity);
				scene->addAmbientLight(alight);
			}
		}
		else
		{
			std::cout << "Invalid classifier, skipping!\n";
		}
	}
	
	if (flag0 == false || flag1 == false)
	{
		std::cout << "No general settings or camera settings are given, try again!\n";
		return false;
	}
	else return true;
}

#endif 