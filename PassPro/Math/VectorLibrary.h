#pragma once
#include <math.h>

struct Vector2
{
	float X;
	float Y;

	Vector2() : X(0.f), Y(0.f) {};
	Vector2(float x, float y) : X(x), Y(y) {};

	Vector2 operator+(const Vector2& Rhs) { return Vector2(X + Rhs.X, Y + Rhs.Y); }
	Vector2 operator-(const Vector2& Rhs) { return Vector2(X - Rhs.X, Y - Rhs.Y); }
	Vector2 operator*(const Vector2& Rhs) { return Vector2(X * Rhs.X, Y * Rhs.Y); }
	Vector2 operator*(const float& Rhs) { return Vector2(X * Rhs, Y * Rhs); }
	Vector2 operator/(const Vector2& Rhs) { return Vector2(X / Rhs.X, Y / Rhs.Y); }
	Vector2 operator/(const float& Rhs) { return Vector2(X / Rhs, Y / Rhs); }

	float Dot(const Vector2 Rhs) { return X * Rhs.X + Y * Rhs.Y; }
};

struct Vector3
{
	float X;
	float Y;
	float Z;
};

struct Vector4
{
	Vector4() : X(0.f), Y(0.f), Z(0.f), W(0.f) {};
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {};

	float X;
	float Y;
	float Z;
	float W;
};

struct Matrix2D
{
	union
	{
		struct
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float M[3][3];
	};

	Matrix2D()
		:	_11(1.f), _12(0.f), _13(0.f),
			_21(0.f), _22(1.f), _23(0.f),
			_31(0.f), _32(0.f), _33(1.f) {}

	Matrix2D(Vector2 Position, float RotationAngle)
		:	_11(cosf(RotationAngle)), _12(-sinf(RotationAngle)), _13(Position.X),
			_21(sinf(RotationAngle)), _22( cosf(RotationAngle)), _23(Position.Y),
			_31(0.f), _32(0.f), _33(1.f) {}
};
