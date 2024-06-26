#pragma once

#include "Component.h"

class PhysicsComponent2D;
class Object2D;

/** 
* Component for moving owning object based on input using physics 
*
* This component is currently used for specific testing, and isn't
* the best setup for a base class movement component.
*/
class MovementComponent2D : public IComponent
{
public:
	/** Binds movement functions to specific keys */
	MovementComponent2D(Object* InParent, const int Player = 0);

	/** Updates owner location and rotation based on input
	*
	* If physics component is attached to object, forces will be applied to give movement
	* If physics component is not attached, object will be manually translated
	*/
	void Update(double DeltaTime);

	/** Strength of force applied to move object */
	float MovementSpeed = 50.0f;

	/** Max speed of object */
	float MaxSpeed = 20.0f;

	/** How much object should rotate per second */
	float RotationSpeed = 100.f;

	/** Strength of force applied against movement */
	float Friction = 100.f;

protected:
	void MoveForward();
	void StopMoveForward();
	void MoveBack();
	void StopMoveBack();
	void MoveLeft();
	void StopMoveLeft();
	void MoveRight();
	void StopMoveRight();
	void RotateClockwise();
	void StopRotateClockwise();
	void RotateCounterClockwise();
	void StopRotateCounterClockwise();

	/** Current normalized value of forward input. 1 is forwards, -1 is backwards */
	float ForwardInput = 0.f;

	/** Current normalized value of forward input. 1 is right, -1 is left */
	float RightInput = 0.f;

	/** Current normalized value of rotational input. 1 is clockwise, -1 is counter-clockwise */
	float RotationInput = 0.f;

	/** Reference to 2D object parent */
	Object2D* Owner = nullptr;

	/** Reference to physics component attached to parent */
	PhysicsComponent2D* PhysicsComponent;
};