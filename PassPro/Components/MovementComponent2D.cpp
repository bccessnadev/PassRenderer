#include "MovementComponent2D.h"
#include "../ObjectManager/Object.h"
#include "../InputManager/InputManager.h"

MovementComponent2D::MovementComponent2D(Object* InParent) : IComponent(InParent)
{
	if (InputManager* IM = InputManager::Get())
	{
		IM->BindToKeyPressed<MovementComponent2D>('W', this, &MovementComponent2D::MoveForward);
		IM->BindToKeyReleased<MovementComponent2D>('W', this, &MovementComponent2D::StopMoveForward);
		IM->BindToKeyPressed<MovementComponent2D>('S', this, &MovementComponent2D::MoveBack);
		IM->BindToKeyReleased<MovementComponent2D>('S', this, &MovementComponent2D::StopMoveBack);
		IM->BindToKeyPressed<MovementComponent2D>('A', this, &MovementComponent2D::MoveLeft);
		IM->BindToKeyReleased<MovementComponent2D>('A', this, &MovementComponent2D::StopMoveLeft);
		IM->BindToKeyPressed<MovementComponent2D>('D', this, &MovementComponent2D::MoveRight);
		IM->BindToKeyReleased<MovementComponent2D>('D', this, &MovementComponent2D::StopMoveRight);
		IM->BindToKeyPressed<MovementComponent2D>(0x27, this, &MovementComponent2D::RotateClockwise);
		IM->BindToKeyReleased<MovementComponent2D>(0x27, this, &MovementComponent2D::StopRotateClockwise);
		IM->BindToKeyPressed<MovementComponent2D>(0x25, this, &MovementComponent2D::RotateCounterClockwise);
		IM->BindToKeyReleased<MovementComponent2D>(0x25, this, &MovementComponent2D::StopRotateCounterClockwise);
	}
}

void MovementComponent2D::Update(double DeltaTime)
{
	if (Object2D* Owner = static_cast<Object2D*>(GetOwner()))
	{
		Owner->Transform.TranslateLocal(Vector2(0.f, 1.f) * ForwardInput * MovementSpeed * DeltaTime);
		Owner->Transform.TranslateLocal(Vector2(1.f, 0.f) * RightInput * MovementSpeed * DeltaTime);
		Owner->Transform.RotateLocal(CounterClockwiseInput * RoationSpeed * DeltaTime * (3.14159265359 / 180.f));
	}
}

void MovementComponent2D::MoveForward()
{
	ForwardInput = 1.f;
}

void MovementComponent2D::StopMoveForward()
{
	ForwardInput = ForwardInput >= 0.f ? 0.f : -1.f;
}

void MovementComponent2D::MoveBack()
{
	ForwardInput = -1.f;
}

void MovementComponent2D::StopMoveBack()
{
	ForwardInput = ForwardInput <= 0.f ? 0.f : 1.f;
}

void MovementComponent2D::MoveLeft()
{
	RightInput = -1.f;
}

void MovementComponent2D::StopMoveLeft()
{
	RightInput = RightInput <= 0.f ? 0.f : 1.f;
}

void MovementComponent2D::MoveRight()
{
	RightInput = 1.f;
}

void MovementComponent2D::StopMoveRight()
{
	RightInput = RightInput >= 0.f ? 0.f : -1.f;
}

void MovementComponent2D::RotateClockwise()
{
	CounterClockwiseInput = -1.f;
}

void MovementComponent2D::StopRotateClockwise()
{
	CounterClockwiseInput = CounterClockwiseInput >= 0.f ? 0.f : 1.f;
}

void MovementComponent2D::RotateCounterClockwise()
{
	CounterClockwiseInput = 1.f;
}

void MovementComponent2D::StopRotateCounterClockwise()
{
	CounterClockwiseInput = CounterClockwiseInput >= 0.f ? 0.f : -1.f;
}
