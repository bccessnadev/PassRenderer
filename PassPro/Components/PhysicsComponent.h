#pragma once

#include "Component.h"
#include "../Math/VectorLibrary.h"

class Object2D;

class ICollider
{
public:
	ICollider(Object2D* RootObject) : Root(RootObject) {}

	Object2D* Root;
};

class AABBCollider : public ICollider
{
public:
	AABBCollider(Object2D* RootObject, Vector2 ColliderSize);
	Vector2 Extent;
};

class ConvexCollider : public ICollider
{
public:
	ConvexCollider(Object2D* RootObject, Vector2 ColliderSize);
	Vector2 Extent;
};

class PhysicsComponent2D : public IComponent
{
public:
	PhysicsComponent2D(Object* Parent, ICollider* Collision = nullptr);
	~PhysicsComponent2D();

	virtual void Update(double DeltaTime);

	ICollider* Collider;
	bool bDebugDraw = false;

protected:
	Vector2 Veloctiy;
	Vector2 PreviousPosition;

	Object2D* Parent2D;

private:
	const float VelocityUpdateRate = 1.f;
	float VelocityUpdateTimer = 1.f;

};