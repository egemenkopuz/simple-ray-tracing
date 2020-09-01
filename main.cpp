#include <iostream>
#include <time.h>

#include "Object.h"
#include "Scene.h"
#include "FileIO.h"

bool raytracing(std::string inputFileName, std::string outputFileName) 
{
	clock_t begin, end;
	begin = clock();

	Scene * scene = new Scene();

	if (!ConfigToScene(scene, inputFileName)) return false;

	Image * img = scene->capture();
	
	writeToPNG(img, outputFileName);

	delete img;

	end = clock();
	float duration = ((float)end - (float)begin) / 1000;	
	std::cout << "Ray Tracing: " <<  duration << " seconds have passed!" << std::endl;
	return true;
}


int main(int argc, char *argv[])
{
	std::string inputFileName;
	std::string outputFileName;

	if (argc != 3)
	{
		std::cout << "Format is [input file] [output file]\n";
		std::cout << "Overriding default values (input.txt and output.png) to inputs...\n";
		inputFileName = "input.txt";
		outputFileName = "output.png";
	}
	else
	{
		inputFileName = argv[1];
		outputFileName = argv[2];
	}

	if (!raytracing(inputFileName, outputFileName))
		std::cout << "Program has failed, and terminated!";
	else
		std::cout << "Program has successfully rendered the scene!";
	
	return 0;
}