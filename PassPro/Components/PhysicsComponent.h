#pragma once

#include "Component.h"
#include "../Math/PhysicsManager.h"
#include <vector>

class Object2D;

class PhysicsComponent2D : public IComponent
{
public:
	PhysicsComponent2D(Object* Parent, ICollider* Collision = nullptr);
	~PhysicsComponent2D();

	virtual void Update(double DeltaTime);

	inline float GetSpeed() const { return Velocity.Length(); }

	/* Adds Impulse * (1.f / Mass) to the velocity. 
	* An impulse is added in its entirety in one frame, 
	* whereas a force is only partially added in one frame based on the delta time */
	void AddImpulse(const Vector2 Impulse);

	/* Adds Force * (1.f / Mass) to the velocity. 
	* A force is only partially added in one frame based on the delta time, 
	* whereas a impulse is added in its entirety in one frame */
	void AddForce(const Vector2 Force);

	void OnOverlapStart();
	void OnOverlapEnd();

	inline bool IsOverlapping() const { return bOverlapping; }

	ICollider* Collider;
	bool bDebugDraw = false;

	Vector2 Velocity;
	float Mass = 0.f;

protected:

	Object2D* Parent2D = nullptr;

	bool bOverlapping = false;

	std::vector<Vector2> ForcesToApply;

private:
	const float VelocityUpdateRate = 1.f;
	float VelocityUpdateTimer = 1.f;

};