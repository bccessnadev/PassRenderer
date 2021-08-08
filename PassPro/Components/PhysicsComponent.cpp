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

PhysicsComponent2D::PhysicsComponent2D(Object* Parent, ICollider* Collision) : IComponent(Parent), Collider(Collision)
{
	Parent2D = static_cast<Object2D*>(Parent);
	if (Parent2D)
	{
		PreviousPosition = Parent2D->Transform.GetPosition();
	}
}

PhysicsComponent2D::~PhysicsComponent2D()
{
	delete Collider;
}

void PhysicsComponent2D::Update(double DeltaTime)
{
	if (Parent2D)
	{
		const Vector2 ParentPosition = Parent2D->Transform.GetPosition();
		Veloctiy = (ParentPosition - PreviousPosition) / DeltaTime;
		PreviousPosition = ParentPosition;

		if (bDebugDraw)
		{
			RenderManager::Get()->DrawDebugRectangle(Parent2D->Transform, Vector4(0.f, 1.f, 0.f, 1.f));
		}
	}
}
