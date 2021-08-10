#pragma once

#include "Component.h"
#include "../Math/PhysicsManager.h"

class Object2D;

class PhysicsComponent2D : public IComponent
{
public:
	PhysicsComponent2D(Object* Parent, ICollider* Collision = nullptr);
	~PhysicsComponent2D();

	virtual void Update(double DeltaTime);

	void OnOverlapStart();
	void OnOverlapEnd();

	inline bool IsOverlapping() const { return bOverlapping; }

	ICollider* Collider;
	bool bDebugDraw = false;

protected:
	Vector2 Veloctiy;
	Vector2 PreviousPosition;

	Object2D* Parent2D = nullptr;

	bool bOverlapping = false;

private:
	const float VelocityUpdateRate = 1.f;
	float VelocityUpdateTimer = 1.f;

};