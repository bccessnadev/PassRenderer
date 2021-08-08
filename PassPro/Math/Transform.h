#pragma once
#include "VectorLibrary.h"

class Transform2D
{
public:
	Transform2D() {}
	Transform2D(const Vector2& Position, const float RotationInRads, const Vector2& Scale);

	const Matrix2D& GetMatrix() const { return Matrix; }
	
	void SetPosition(const Vector2& Position);
	Vector2 GetPosition() const;
	void SetRotation(const float RotationInRads);
	Vector2 GetScale() const;
	void SetScale(const Vector2& Scale);

	void TranslateLocal(const Vector2& Translation);
	void TranslateGlobal(const Vector2& Translation);
	void RotateLocal(const float Rotation);

	Matrix2D GetRotationMatrix() const;
	float GetRotationAngle() const;

protected:
	Matrix2D Matrix;
};