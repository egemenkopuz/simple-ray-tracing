#include "Image.h"

Image::Image(int w, int h) 
{
	this->width = w;
	this->height = h;
	pixels = new Color[w * h];
}

Image::~Image()
{
	delete[] pixels;
}

void Image::setColor(int w, int h, const Color color)
{
	pixels[w + h * this->width] = color;
}

Color * Image::getColor(int w, int h)
{
	return &pixels[w + h * this->width];
}

Color * Image::getPixels() const
{
	return pixels;
}