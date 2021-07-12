#include "Transform.h"

Transform2D::Transform2D(const Vector2 Position, const float RotationInRads, const Vector2 Scale)
{
	SetPosition(Position);
	SetRotation(RotationInRads);
	SetScale(Scale);
}

void Transform2D::SetPosition(const Vector2 Position)
{
	Matrix._13 = Position.X;
	Matrix._23 = Position.Y;
}

void Transform2D::SetRotation(const float RotationInRads)
{
	const Vector2 CachedScale = GetScale();
	Matrix._11 =  cosf(RotationInRads);
	Matrix._12 = -sinf(RotationInRads);
	Matrix._21 =  sinf(RotationInRads);
	Matrix._22 =  cosf(RotationInRads);
	SetScale(CachedScale);
}

Vector2 Transform2D::GetScale()
{
	// Get both axis from matrix
	Vector2 XAxis(Matrix._11, Matrix._21);
	Vector2 YAxis(Matrix._12, Matrix._22);

	// Return length of both
	return Vector2(XAxis.Length(), YAxis.Length());
}

void Transform2D::SetScale(const Vector2 Scale)
{
	// Get both axis from matrix
	Vector2 XAxis(Matrix._11, Matrix._21);
	Vector2 YAxis(Matrix._12, Matrix._22);
	
	// Normalize axis to remove and previous scale
	XAxis.Normalize();
	YAxis.Normalize();

	// Scale axis
	XAxis *= Scale.X;
	YAxis *= Scale.Y;

	Matrix._11 = XAxis.X;
	Matrix._12 = YAxis.X;
	Matrix._21 = XAxis.Y;
	Matrix._22 = YAxis.Y;
}
