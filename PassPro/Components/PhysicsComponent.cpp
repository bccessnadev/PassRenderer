#include "PhysicsComponent.h"
#include "../Math/PhysicsManager.h"
#include "../ObjectManager/Object.h"
#include "../RenderManager/RenderManager.h"
#include "../WorldSize.h"
#include <vector>
#include <debugapi.h>
#include <string>
#include <sstream>

using namespace std;

PhysicsComponent2D::PhysicsComponent2D(Object* Parent, ICollider* Collision) : IComponent(Parent), Collider(Collision)
{
	Parent2D = static_cast<Object2D*>(Parent);

	if (Collider)
	{
		PhysicsManager::Get()->RegisterPhysicsObject(this);
	}

	ForcesToApply.reserve(10);
}

PhysicsComponent2D::~PhysicsComponent2D()
{
	delete Collider;
}

void PhysicsComponent2D::Update(double DeltaTime)
{
	if (Parent2D)
	{
		// Apply any pending forces
		if (ForcesToApply.size() > 0)
		{
			for (int f = 0; f < ForcesToApply.size(); f++)
			{
				Velocity += ForcesToApply[f] * (Mass > 0.f ? (1.f / Mass) : 1.f) * DeltaTime;
			}

			ForcesToApply.clear();
		}

		// Move the parent's transform based on the velocity
		Parent2D->Transform.TranslateGlobal(Velocity * DeltaTime);
	}
}

void PhysicsComponent2D::Render()
{
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

		ostringstream VelocityDebugStream;
		VelocityDebugStream << "Velocity: [" << Velocity.X << ", " << Velocity.Y << "] \n";
		OutputDebugStringA(VelocityDebugStream.str().c_str());
	}
}

void PhysicsComponent2D::AddImpulse(const Vector2 Impulse)
{
	Velocity += Impulse * (Mass > 0.f ? (1.f / Mass) : 1.f);
}

void PhysicsComponent2D::AddForce(const Vector2 Force)
{
	ForcesToApply.push_back(Force);
}

void PhysicsComponent2D::OnOverlapStart()
{
	bOverlapping = true;
}

void PhysicsComponent2D::OnOverlapEnd()
{
	bOverlapping = false;
}
