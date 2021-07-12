#include "VectorLibrary.h"

Vector2 Vector2::operator*=(const float& Rhs)
{
	X = X * Rhs;
	Y = Y * Rhs;
	return *this;
}

void Vector2::Normalize()
{
	const float VectorLength = Length();
	X /= VectorLength;
	Y /= VectorLength;
}

Vector2 Vector2::Normalize(Vector2 Vector)
{
	Vector.Normalize();
	return Vector;
}
