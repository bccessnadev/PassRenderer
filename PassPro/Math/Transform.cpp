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
	Matrix._11 =  cosf(RotationInRads);
	Matrix._12 = -sinf(RotationInRads);
	Matrix._21 =  sinf(RotationInRads);
	Matrix._22 =  cosf(RotationInRads);
}

void Transform2D::SetScale(const Vector2 Scale)
{
	// TODO
}
