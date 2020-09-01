#ifndef COLOR_H_EK
#define COLOR_H_EK

#include <cmath>
#include <algorithm>

class Color {
public:
	float r, g, b;

	Color();
	Color(float f);
	Color(float r, float g, float b);

	virtual ~Color() = default;

	void clamp(float min = 0.0f, float max = 1.0f);
	void applyGammaCorrection(float exposure, float gamma);

	Color& operator =(const Color& rhs);
	Color& operator +=(const Color& rhs);
	Color& operator *=(const Color& rhs);
	Color& operator *=(float f);
};

inline Color operator+(const Color& c1, const Color& c2)
{
	return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline Color operator-(const Color& c1, const Color& c2)
{
	return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

inline Color operator*(const Color& c1, const Color& c2)
{
	return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

inline Color operator*(const Color& c1, float f)
{
	return Color(c1.r * f, c1.g * f, c1.b * f);
}

inline Color operator*(float f, const Color& c2)
{
	return Color(f * c2.r, f * c2.g, f * c2.b);
}

#endif 