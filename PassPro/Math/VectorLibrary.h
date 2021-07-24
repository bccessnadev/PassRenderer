#pragma once
#include <math.h>
#include <memory.h>

struct Vector2
{
	float X;
	float Y;

	Vector2() : X(0.f), Y(0.f) {};
	Vector2(float x, float y) : X(x), Y(y) {};

	Vector2 operator+(const Vector2& Rhs) const { return Vector2(X + Rhs.X, Y + Rhs.Y); }
	Vector2 operator+(const float& Rhs) const { return Vector2(X + Rhs, Y + Rhs); }
	Vector2 operator-(const Vector2& Rhs) const { return Vector2(X - Rhs.X, Y - Rhs.Y); }
	Vector2 operator-(const float& Rhs) const { return Vector2(X - Rhs, Y - Rhs); }
	Vector2 operator-() const { return Vector2(-X, -Y); }
	Vector2 operator*(const Vector2& Rhs) const { return Vector2(X * Rhs.X, Y * Rhs.Y); }
	Vector2 operator*(const float& Rhs) const { return Vector2(X * Rhs, Y * Rhs); }
	Vector2 operator/(const Vector2& Rhs) const { return Vector2(X / Rhs.X, Y / Rhs.Y); }
	Vector2 operator/(const float& Rhs) const { return Vector2(X / Rhs, Y / Rhs); }

	Vector2 operator*=(const Vector2& Rhs);
	Vector2 operator*=(const float& Rhs);

	bool operator>(const Vector2& Rhs) { return Length() > Rhs.Length(); }
	bool operator<(const Vector2& Rhs) { return Length() < Rhs.Length(); }


	inline float Dot(const Vector2 Rhs) { return X * Rhs.X + Y * Rhs.Y; }
	inline static float Dot(const Vector2 Lhs, const Vector2 Rhs) { return Lhs.X * Rhs.X + Lhs.Y * Rhs.Y; }

	inline float Length() const { return sqrtf((X * X) + (Y * Y)); }
	inline static float Length(const Vector2 Vector) { return sqrtf((Vector.X * Vector.X) + (Vector.Y * Vector.Y)); }

	inline static Vector2 GetAbs(const Vector2 Vector) { return Vector2(fabs(Vector.X), fabs(Vector.Y)); }

	void Normalize();
	static Vector2 Normalize(Vector2 Vector);
};

struct Vector3
{
	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;

	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {};

	Vector3 operator+(const Vector3& Rhs) const { return Vector3(X + Rhs.X, Y + Rhs.Y, Z + Rhs.Z); }
	Vector3 operator-(const Vector3& Rhs) const { return Vector3(X - Rhs.X, Y - Rhs.Y, Z - Rhs.Z); }
	Vector3 operator*(const Vector3& Rhs) const { return Vector3(X * Rhs.X, Y * Rhs.Y, Z * Rhs.Z); }
	Vector3 operator*(const float& Rhs) const { return Vector3(X * Rhs, Y * Rhs, Z * Rhs); }
	Vector3 operator/(const Vector3& Rhs) const { return Vector3(X / Rhs.X, Y / Rhs.Y, Z / Rhs.Z); }
	Vector3 operator/(const float& Rhs) const { return Vector3(X / Rhs, Y / Rhs, Z / Rhs); }

	Vector3 operator*=(const float& Rhs);

	inline float Dot(const Vector3 Rhs) { return X * Rhs.X + Y * Rhs.Y + Z * Rhs.Z; }
	inline static float Dot(const Vector3 Lhs, const Vector3 Rhs) { return Lhs.X * Rhs.X + Lhs.Y * Rhs.Y + Lhs.Z * Rhs.Z; }
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

	Matrix2D(const float In11, const float In12, const float In13, 
		const float In21, const float In22, const float In23, 
		const float In31, const float In32, const float In33 )
		: _11(In11), _12(In12), _13(In13),
		_21(In21), _22(In22), _23(In23),
		_31(In31), _32(In32), _33(In33) {}

	Matrix2D operator*(const Matrix2D& Rhs)
	{
		Matrix2D ReturnMatrix;
		ReturnMatrix._11 = Vector3::Dot(Vector3(_11, _12, _13), Vector3(Rhs._11, Rhs._21, Rhs._31));
		ReturnMatrix._12 = Vector3::Dot(Vector3(_11, _12, _13), Vector3(Rhs._12, Rhs._22, Rhs._32));
		ReturnMatrix._13 = Vector3::Dot(Vector3(_11, _12, _13), Vector3(Rhs._13, Rhs._23, Rhs._33));
		ReturnMatrix._21 = Vector3::Dot(Vector3(_21, _22, _23), Vector3(Rhs._11, Rhs._21, Rhs._31));
		ReturnMatrix._22 = Vector3::Dot(Vector3(_21, _22, _23), Vector3(Rhs._12, Rhs._22, Rhs._32));
		ReturnMatrix._23 = Vector3::Dot(Vector3(_21, _22, _23), Vector3(Rhs._13, Rhs._23, Rhs._33));
		ReturnMatrix._31 = Vector3::Dot(Vector3(_31, _32, _33), Vector3(Rhs._11, Rhs._21, Rhs._31));
		ReturnMatrix._32 = Vector3::Dot(Vector3(_31, _32, _33), Vector3(Rhs._12, Rhs._22, Rhs._32));
		ReturnMatrix._33 = Vector3::Dot(Vector3(_31, _32, _33), Vector3(Rhs._13, Rhs._23, Rhs._33));
		return ReturnMatrix;
	}

	Vector2 operator*(const Vector2& Rhs) 
	{ 
		const float X = (_11 * Rhs.X) + (_12 * Rhs.Y) +_13;
		const float Y = (_21 * Rhs.X) + (_22 * Rhs.Y) +_23;
		return Vector2(X, Y); 
	}
};
