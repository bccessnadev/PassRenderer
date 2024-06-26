#pragma once

#include "Component.h"
#include "../Math/PhysicsManager.h"
#include <vector>

class Object2D;

/** 
* Component that acts as an interface between an object and the physics manager 
*
* Allows forces to be applied to an object, and allows handling overlap events.
*/
class PhysicsComponent2D : public IComponent
{
public:
	/**
	* Constructs physics component, and registers it with the Physics Manager
	*
	* @param Parent Object component is attached to
	* @param Collision Definition of component's physics collider
	*/
	PhysicsComponent2D(Object* Parent, ICollider2D* Collision = nullptr);
	~PhysicsComponent2D();

	/** Translates object based on pending forces from this frame */
	virtual void Update(double DeltaTime) override;

	/** Handles debug drawing */
	virtual void Render() override;

	/** Returns how fast object is currently moving */
	inline float GetSpeed() const { return Velocity.Length(); }

	/** Returns the owner of this component as an Object2D */
	inline Object2D* GetOwner2D() const { return Parent2D; }

	/**
	* Adds Impulse * (1.f / Mass) to the velocity.
	*
	* An impulse is added in its entirety in one frame,
	* whereas a force is only partially added in one frame based on the delta time
	*/
	void AddImpulse(const Vector2 Impulse);

	/**
	* Adds Force * (1.f / Mass) to the velocity.
	*
	* A force is only partially added in one frame based on the delta time,
	* whereas a impulse is added in its entirety in one frame
	*/
	void AddForce(const Vector2 Force);

	/** Called when overlap with other component starts */
	void OnOverlapStart();

	/** Called whe overlap with other object ends */
	void OnOverlapEnd();

	/** Returns whether component is currently overlapping other component */
	inline bool IsOverlapping() const { return bOverlapping; }

	/** Returns the collider used to determine if component is overlapping other component */
	inline ICollider2D* GetCollider() const { return Collider; }

	/** Get current velocity of the object */
	inline Vector2 GetVelocity() const { return Velocity; }

	/** Directly set the velocity of the object */
	inline void SetVelocity(const Vector2& NewVelocity) { Velocity = NewVelocity; }

	/** Directly adds to the objects current velocity. Ignores mass */
	inline void AddVelocity(const Vector2& VelocityToAdd) { Velocity += VelocityToAdd; }

	/** Set whether collider and forces should be displayed */
	inline void SetDebugDraw(const bool bNewDebugDraw) { bDebugDraw = bNewDebugDraw; }

	/** Get the mass of the object */
	inline float GetMass() const { return Mass; }

	/** Set how much mass the object has. Determines how much affect forces have on the object */
	inline void SetMass(const float NewMass) { Mass = NewMass; }

protected:
	/** Collider used to determine if component is overlapping other component */
	ICollider2D* Collider;

	/**
	 * Whether to draw debug lines for collider shape, forces, velocity, etc.
	 */
	bool bDebugDraw = false;

	/** Current velocity of object */
	Vector2 Velocity;

	/** How much mass the object has. Determines how much affect forces have on the object */
	float Mass = 0.f;

	/** Reference to parent as a 2D object */
	Object2D* Parent2D = nullptr;

	/** Whether component is currently overlapping other component */
	bool bOverlapping = false;

	/** 
	* List of forces that have been requested to be applied this frame.
	* 
	* These forces are applied every update then the list is cleared.
	*/
	std::vector<Vector2> ForcesToApply;
};