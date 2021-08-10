#include "PhysicsComponent.h"
#include "../Math/PhysicsManager.h"
#include "../ObjectManager/Object.h"
#include "../RenderManager/RenderManager.h"
#include "../WorldSize.h"
#include <vector>

using namespace std;

PhysicsComponent2D::PhysicsComponent2D(Object* Parent, ICollider* Collision) : IComponent(Parent), Collider(Collision)
{
	Parent2D = static_cast<Object2D*>(Parent);

	if (Collider)
	{
		PhysicsManager::Get()->RegisterPhysicsObject(this);
	}

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
			if (ConvexCollider2D* ConvexCollider = static_cast<ConvexCollider2D*>(Collider))
			{
				const vector<Vector2> ColliderVerts = ConvexCollider->GetWorldSpaceVerticies();
				RenderManager* Renderer = RenderManager::Get();

				for (int v = 0; v < ColliderVerts.size(); v++)
				{
					// Have the second vertex loop back to the beginning when on last index
					const int v2 = v < ColliderVerts.size() - 1 ? v + 1 : 0;
					Renderer->DrawDebugLine(ColliderVerts[v], ColliderVerts[v2], bOverlapping ? Colors::Red : Colors::Green);
				}
			}
		}
	}
}

void PhysicsComponent2D::OnOverlapStart()
{
	bOverlapping = true;
}

void PhysicsComponent2D::OnOverlapEnd()
{
	bOverlapping = false;
}
