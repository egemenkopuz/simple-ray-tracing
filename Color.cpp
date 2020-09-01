#include "Color.h"

Color::Color() : r(0.0f), g(0.0f), b(0.0f)
{
}

Color::Color(float f) : r(f), g(f), b(f)
{
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b)
{
}

void Color::clamp(float min, float max)
{
	r = std::max(min, std::min(max, r));
	g = std::max(min, std::min(max, g));
	b = std::max(min, std::min(max, b));
}

void Color::applyGammaCorrection(float exposure, float gamma)
{
	r = std::pow(r * exposure, gamma);
	g = std::pow(g * exposure, gamma);
	b = std::pow(b * exposure, gamma);
}

Color & Color::operator=(const Color & rhs)
{
	r = rhs.r;
	g = rhs.g;
	b = rhs.b;
	return *this;
}

Color & Color::operator+=(const Color & rhs)
{
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
	return *this;
}

Color & Color::operator*=(const Color & rhs)
{
	r *= rhs.r;
	g *= rhs.g;
	b *= rhs.b;
	return *this;
}

Color & Color::operator*=(float f)
{
	r *= f;
	g *= f;
	b *= f;
	return *this;
}
