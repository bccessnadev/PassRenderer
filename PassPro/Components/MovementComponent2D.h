#pragma once

#include "Component.h"

class PhysicsComponent2D;
class Object2D;

class MovementComponent2D : public IComponent
{
public:
	MovementComponent2D(Object* InParent);

	void Update(double DeltaTime);
	void Render() {}

	float MovementSpeed = 50.0f;
	float MaxSpeed = 20.0f;
	float RoationSpeed = 100.f;
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

	float ForwardInput = 0.f;
	float RightInput = 0.f;
	float CounterClockwiseInput = 0.f;

	Object2D* Owner = nullptr;
	PhysicsComponent2D* PhysicsComponent;
};