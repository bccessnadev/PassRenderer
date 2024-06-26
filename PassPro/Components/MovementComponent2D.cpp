#include "MovementComponent2D.h"
#include "../ObjectManager/Object.h"
#include "../InputManager/InputManager.h"
#include "PhysicsComponent.h"
#include "../RenderManager/RenderManager.h"

MovementComponent2D::MovementComponent2D(Object* InParent, const int Player) : IComponent(InParent)
{
	if (InputManager* IM = InputManager::Get())
	{
		if (Player == 0)
		{
			IM->BindToKeyPressed<MovementComponent2D>('W', this, &MovementComponent2D::MoveForward);
			IM->BindToKeyReleased<MovementComponent2D>('W', this, &MovementComponent2D::StopMoveForward);
			IM->BindToKeyPressed<MovementComponent2D>('S', this, &MovementComponent2D::MoveBack);
			IM->BindToKeyReleased<MovementComponent2D>('S', this, &MovementComponent2D::StopMoveBack);
			IM->BindToKeyPressed<MovementComponent2D>('A', this, &MovementComponent2D::MoveLeft);
			IM->BindToKeyReleased<MovementComponent2D>('A', this, &MovementComponent2D::StopMoveLeft);
			IM->BindToKeyPressed<MovementComponent2D>('D', this, &MovementComponent2D::MoveRight);
			IM->BindToKeyReleased<MovementComponent2D>('D', this, &MovementComponent2D::StopMoveRight);
			IM->BindToKeyPressed<MovementComponent2D>('E', this, &MovementComponent2D::RotateClockwise);
			IM->BindToKeyReleased<MovementComponent2D>('E', this, &MovementComponent2D::StopRotateClockwise);
			IM->BindToKeyPressed<MovementComponent2D>('Q', this, &MovementComponent2D::RotateCounterClockwise);
			IM->BindToKeyReleased<MovementComponent2D>('Q', this, &MovementComponent2D::StopRotateCounterClockwise);
		}
		else if (Player == 1)
		{
			IM->BindToKeyPressed<MovementComponent2D>(0x26, this, &MovementComponent2D::MoveForward);
			IM->BindToKeyReleased<MovementComponent2D>(0x26, this, &MovementComponent2D::StopMoveForward);
			IM->BindToKeyPressed<MovementComponent2D>(0x28, this, &MovementComponent2D::MoveBack);
			IM->BindToKeyReleased<MovementComponent2D>(0x28, this, &MovementComponent2D::StopMoveBack);
			IM->BindToKeyPressed<MovementComponent2D>(0x25, this, &MovementComponent2D::MoveLeft);
			IM->BindToKeyReleased<MovementComponent2D>(0x25, this, &MovementComponent2D::StopMoveLeft);
			IM->BindToKeyPressed<MovementComponent2D>(0x27, this, &MovementComponent2D::MoveRight);
			IM->BindToKeyReleased<MovementComponent2D>(0x27, this, &MovementComponent2D::StopMoveRight);
			IM->BindToKeyPressed<MovementComponent2D>(0x63, this, &MovementComponent2D::RotateClockwise);
			IM->BindToKeyReleased<MovementComponent2D>(0x63, this, &MovementComponent2D::StopRotateClockwise);
			IM->BindToKeyPressed<MovementComponent2D>(0x63, this, &MovementComponent2D::RotateCounterClockwise);
			IM->BindToKeyReleased<MovementComponent2D>(0x63, this, &MovementComponent2D::StopRotateCounterClockwise);
		}
	}

	Owner = static_cast<Object2D*>(Parent);
	PhysicsComponent = Parent->FindComponent<PhysicsComponent2D*>();
}

void MovementComponent2D::Update(double DeltaTime)
{
	if (!Owner)
	{
		return;
	}

	if (PhysicsComponent)
	{
		if (ForwardInput != 0.f || RightInput != 0.f)
		{
			Vector2 DeltaVelocity = Vector2(
				RightInput * MovementSpeed * static_cast<float>(DeltaTime),
				ForwardInput * MovementSpeed * static_cast<float>(DeltaTime));
			
			if (Vector2::Length(PhysicsComponent->GetVelocity() + DeltaVelocity) > MaxSpeed)
			{
				const float CurrentSpeed = PhysicsComponent->GetSpeed();
				const Vector2 TargetDir = Vector2::Normalize(PhysicsComponent->GetVelocity() + DeltaVelocity);
				const Vector2 TargetVelocity = TargetDir * MaxSpeed;
				DeltaVelocity = TargetVelocity - PhysicsComponent->GetVelocity();
			}

			PhysicsComponent->AddVelocity(DeltaVelocity);
			RenderManager::Get()->DrawDebugLine(Owner->Transform.GetPosition(), Owner->Transform.GetPosition() + (DeltaVelocity * 10.f), Colors::Yellow);
		}

		Owner->Transform.RotateLocal(RotationInput * RotationSpeed * static_cast<float>(DeltaTime) * (3.14159265359f / 180.f));

		if (PhysicsComponent->GetSpeed() > DBL_EPSILON)
		{
			const Vector2 FrictionAlpha = Vector2(RightInput == 0.f ? 1.f : 0.f, ForwardInput == 0.f ? 1.f : 0.f);

			const Vector2 FrictionDirection = -Vector2::Normalize(PhysicsComponent->GetVelocity());
			const Vector2 FrictionForce = FrictionAlpha * FrictionDirection * Friction;

			// Make sure we don't add enough friction to switch it's direction
			if (PhysicsComponent->GetSpeed() - Vector2::Length(FrictionForce * static_cast<float>(DeltaTime)) > 0.f)
			{
				PhysicsComponent->AddForce(FrictionForce);
			}
			else
			{
				PhysicsComponent->SetVelocity(Vector2(0.f, 0.f));
			}

			RenderManager::Get()->DrawDebugLine(Owner->Transform.GetPosition(), Owner->Transform.GetPosition() + (FrictionForce * 0.1f), Colors::Red);
		}
	}
	else
	{
		Owner->Transform.TranslateGlobal(Vector2(0.f, 1.f) * ForwardInput * MovementSpeed * static_cast<float>(DeltaTime));
		Owner->Transform.TranslateGlobal(Vector2(1.f, 0.f) * RightInput * MovementSpeed * static_cast<float>(DeltaTime));
		Owner->Transform.RotateLocal(-RotationInput * RotationSpeed * static_cast<float>(DeltaTime) * (3.14159265359f / 180.f));
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
	RotationInput = -1.f;
}

void MovementComponent2D::StopRotateClockwise()
{
	RotationInput = RotationInput >= 0.f ? 0.f : 1.f;
}

void MovementComponent2D::RotateCounterClockwise()
{
	RotationInput = 1.f;
}

void MovementComponent2D::StopRotateCounterClockwise()
{
	RotationInput = RotationInput >= 0.f ? 0.f : -1.f;
}
