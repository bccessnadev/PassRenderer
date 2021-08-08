#include "Transform.h"

Transform2D::Transform2D(const Vector2& Position, const float RotationInRads, const Vector2& Scale)
{
	SetPosition(Position);
	SetRotation(RotationInRads);
	SetScale(Scale);
}

void Transform2D::SetPosition(const Vector2& Position)
{
	Matrix._13 = Position.X;
	Matrix._23 = Position.Y;
}

Vector2 Transform2D::GetPosition() const
{
	return Vector2(Matrix._13, Matrix._23);
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

Vector2 Transform2D::GetScale() const
{
	// Get both axis from matrix
	Vector2 XAxis(Matrix._11, Matrix._21);
	Vector2 YAxis(Matrix._12, Matrix._22);

	// Return length of both
	return Vector2(XAxis.Length(), YAxis.Length());
}

void Transform2D::SetScale(const Vector2& Scale)
{
	// Get both axis from matrix
	Vector2 XAxis(Matrix._11, Matrix._21);
	Vector2 YAxis(Matrix._12, Matrix._22);
	
	// Normalize axis to remove previous scale
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

void Transform2D::TranslateLocal(const Vector2& Translation)
{
	Vector2 WorldTranslation = GetRotationMatrix() * Translation;
	SetPosition(GetPosition() + WorldTranslation);
}

void Transform2D::TranslateGlobal(const Vector2& Translation)
{
	SetPosition(GetPosition() + Translation);
}

void Transform2D::RotateLocal(const float Rotation)
{
	Matrix2D RotationMatrix;
	RotationMatrix._11 = cosf(Rotation);
	RotationMatrix._12 = -sinf(Rotation);
	RotationMatrix._21 = sinf(Rotation);
	RotationMatrix._22 = cosf(Rotation);
	Matrix = Matrix * RotationMatrix;
}

Matrix2D Transform2D::GetRotationMatrix() const
{
	Matrix2D RotationMatrix;

	// Get both axis from matrix
	Vector2 XAxis(Matrix._11, Matrix._21);
	Vector2 YAxis(Matrix._12, Matrix._22);
	
	// Normalize axis to remove scale
	XAxis.Normalize();
	YAxis.Normalize();

	RotationMatrix._11 = XAxis.X;
	RotationMatrix._12 = YAxis.X;
	RotationMatrix._21 = XAxis.Y;
	RotationMatrix._22 = YAxis.Y;

	return RotationMatrix;
}

float Transform2D::GetRotationAngle() const
{
	const Matrix2D RotationMatrix = GetRotationMatrix();
	return atan2f(RotationMatrix._21, RotationMatrix._11);
}
