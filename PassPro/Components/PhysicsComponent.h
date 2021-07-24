#pragma once

#include "Component.h"
#include "../Math/VectorLibrary.h"

class Object2D;

class ICollider
{
public:
	ICollider(Object2D* RootObject) : Root(RootObject) {}
	virtual bool TestScreenCollision() = 0;	

	Object2D* Root;
};

class AABBCollider : public ICollider
{
public:
	AABBCollider(Object2D* RootObject, Vector2 ColliderSize);
	virtual bool TestScreenCollision();
	Vector2 Extent;
};

class PhsicsComponent2D : public IComponent
{
public:
	PhsicsComponent2D(Object* Parent, ICollider* Collision = nullptr, bool bCollidesWithScreenEdge = true);
	~PhsicsComponent2D();

	virtual void Update(double DeltaTime);

	ICollider* Collider;

protected:
	Vector2 Veloctiy;
	Vector2 PreviousPosition;

	Object2D* Parent2D;

	bool bScreenEdgeCollision = true;

private:
	const float VelocityUpdateRate = 1.f;
	float VelocityUpdateTimer = 1.f;

};