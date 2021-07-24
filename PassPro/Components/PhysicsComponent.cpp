#include "PhysicsComponent.h"
#include "../ObjectManager/Object.h"
#include "../RenderManager/RenderManager.h"
#include "../WorldSize.h"

AABBCollider::AABBCollider(Object2D* RootObject, Vector2 ColliderSize) : ICollider(RootObject)
{
	Extent = ColliderSize * 0.5f;

	if (Root)
	{
		Extent *= RootObject->Transform.GetScale();
	}
}

bool AABBCollider::TestScreenCollision()
{
	if (Root)
	{
		const Vector2 ScreenExtents = Vector2(HalfNumXUnits, HalfNumYUnits);
		const Vector2 Position = Root->Transform.GetPosition();
		const Vector2 PastScreen = (Vector2::GetAbs(Position) + Extent) - ScreenExtents;
		if (PastScreen.X > 0.f || PastScreen.Y > 0.f)
		{
			const Vector2 Resolution = Vector2(PastScreen.X > 0 ? PastScreen.X : 0.f, PastScreen.Y > 0 ? PastScreen.Y : 0.f);
			const Vector2 ResolutionDirection = Vector2(Position.X > 0 ? -1.f : 1.f, Position.Y > 0 ? -1.f : 1.f);
			Root->Transform.TranslateLocal(Resolution * ResolutionDirection);
		}
	}
	return false;
}

PhsicsComponent2D::PhsicsComponent2D(Object* Parent, ICollider* Collision, bool bCollidesWithScreenEdge) : IComponent(Parent), Collider(Collision), bScreenEdgeCollision(bCollidesWithScreenEdge)
{
	Parent2D = static_cast<Object2D*>(Parent);
	if (Parent2D)
	{
		PreviousPosition = Parent2D->Transform.GetPosition();
	}
}

PhsicsComponent2D::~PhsicsComponent2D()
{
	delete Collider;
}

void PhsicsComponent2D::Update(double DeltaTime)
{
	if (Parent2D)
	{
		const Vector2 ParentPosition = Parent2D->Transform.GetPosition();
		Veloctiy = (ParentPosition - PreviousPosition) / DeltaTime;
		PreviousPosition = ParentPosition;
		RenderManager::Get()->DrawDebugLine(ParentPosition, ParentPosition + Veloctiy, Vector4(0.f, 1.f, 0.f, 1.f));
	}

	if (bScreenEdgeCollision && Collider)
	{
		Collider->TestScreenCollision();
	}
}
