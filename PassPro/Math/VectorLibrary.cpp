#include "VectorLibrary.h"

Vector2 Vector2::operator*=(const Vector2& Rhs)
{
	X = X * Rhs.X;
	Y = Y * Rhs.Y;
	return *this;
}

Vector2 Vector2::operator*=(const float& Rhs)
{
	X = X * Rhs;
	Y = Y * Rhs;
	return *this;
}

Vector2 Vector2::Normalize()
{
	const float VectorLength = Length();
	X /= VectorLength;
	Y /= VectorLength;
	return *this;
}

Vector2 Vector2::Normalize(Vector2 Vector)
{
	Vector.Normalize();
	return Vector;
}

Vector3 Vector3::operator*=(const float& Rhs)
{
	X = X * Rhs;
	Y = Y * Rhs;
	Z = Z * Rhs;
	return *this;
}
