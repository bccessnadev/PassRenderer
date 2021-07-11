#pragma once
#include "VectorLibrary.h"

class Transform2D
{
public:
	Transform2D() {}
	Transform2D(const Vector2 Position, const float RotationInRads, const Vector2 Scale);
	
	Matrix2D Matrix;

	void SetPosition(const Vector2 Position);
	void SetRotation(const float RotationInRads);
	void SetScale(const Vector2 Scale);
};