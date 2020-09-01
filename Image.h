#ifndef IMAGE_H_EK
#define IMAGE_H_EK

#include "VectorMath.h"
#include "Color.h"

class Image {
protected:
	Color* pixels;
	int width, height;
public:
	Image(int width, int height);
	~Image();

	void setColor(int w, int h, const Color color);
	Color* getColor(int w, int h);

	Color* getPixels() const;

	int getWidth() { return width; }
	int getHeight() { return height; }
};

#endif 