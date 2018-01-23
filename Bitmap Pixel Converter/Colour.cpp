#include "Colour.h"

Colour::Colour(const unsigned int value)
	:
	value(value)
{
}

Colour::Colour(const unsigned char alpha, const unsigned char red, const unsigned char green, const unsigned char blue)
	:
	Colour(alpha << 24 | red << 16 | green << 8 | blue)
{
}

Colour::Colour(const unsigned char red, const unsigned char green, const unsigned char blue)
	:
	Colour(0xFF, red, green, blue)
{
}

bool Colour::operator ==(const Colour& source) const
{
	return value == source.value;
}

bool Colour::CompareIgnoreAlpha(const Colour& source) const
{
	return (value & 0xFFFFFF) == (source.value & 0xFFFFFF);
}

unsigned int Colour::GetAlpha() const
{
	return value >> 24;
}

unsigned int Colour::GetRed() const
{
	return value >> 16 & 0xFF;
}

unsigned int Colour::GetGreen() const
{
	return value >> 8 & 0xFF;
}

unsigned int Colour::GetBlue() const
{
	return value & 0xFF;
}