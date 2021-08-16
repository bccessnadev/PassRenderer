#include "PhysicsManager.h"
#include "../Components/PhysicsComponent.h"
#include "../ObjectManager/Object.h"
#include "../RenderManager/RenderManager.h"

using namespace std;

AABBCollider::AABBCollider(Object2D* RootObject, Vector2 ColliderSize) : ICollider(RootObject)
{
	Extent = ColliderSize * 0.5f;

	if (Root)
	{
		Extent *= RootObject->Transform.GetScale();
	}
}

std::vector<Vector2> ConvexCollider2D::GetWorldSpaceVerticies() const
{
	vector<Vector2> WorldSpaceVerts;
	WorldSpaceVerts.resize(Verticies.size());

	for (int v = 0; v < Verticies.size(); v++)
	{
		WorldSpaceVerts[v] = Root->Transform.GetMatrix() * Verticies[v];
	}

	return WorldSpaceVerts;
}

BoxCollider2D::BoxCollider2D(Object2D* RootObject, const Vector2& Scale, const Vector2& Offset, const float Rotation) : ConvexCollider2D(RootObject)
{
	const Vector2 Extent = Scale * 0.5f;
	Verticies.push_back(Offset + Extent.Rotate(Rotation));
	Verticies.push_back(Offset + Vector2(Extent.X, -Extent.Y).Rotate(Rotation));
	Verticies.push_back(Offset + Vector2(-Extent.X, -Extent.Y).Rotate(Rotation));
	Verticies.push_back(Offset + Vector2(-Extent.X, Extent.Y).Rotate(Rotation));
}

PhysicsManager* PhysicsManager::Instance = nullptr;

PhysicsManager* PhysicsManager::Get()
{
	if (!Instance)
	{
		Instance = new PhysicsManager();
	}

	return Instance;
}

void PhysicsManager::RegisterPhysicsObject(PhysicsComponent2D* PhysicsObject)
{
	// TODO: Add only unique
	PhysicsObjects.push_back(PhysicsObject);
}

void PhysicsManager::Update(double DeltaTime)
{
	for (int ObjectAIndex = 0; ObjectAIndex < PhysicsObjects.size(); ObjectAIndex++)
	{
		for (int ObjectBIndex = ObjectAIndex + 1; ObjectBIndex < PhysicsObjects.size(); ObjectBIndex++)
		{
			TestConvexColliders_SAT(PhysicsObjects[ObjectAIndex], PhysicsObjects[ObjectBIndex]);
		}
	}
}

void PhysicsManager::TestConvexColliders_SAT(PhysicsComponent2D* ObjectA, PhysicsComponent2D* ObjectB)
{
	if (!ObjectA || !ObjectB)
	{
		return;
	}

	ConvexCollider2D* ColliderA = static_cast<ConvexCollider2D*>(ObjectA->Collider);
	ConvexCollider2D* ColliderB = static_cast<ConvexCollider2D*>(ObjectB->Collider);

	if (ColliderA && ColliderB)
	{
		const vector<Vector2> AVerts = ColliderA->GetWorldSpaceVerticies();
		const vector<Vector2> BVerts = ColliderB->GetWorldSpaceVerticies();

		// Test all A edges and all B edges
		Vector2 AResolution = Vector2(INFINITY, INFINITY);
		Vector2 BResolution = Vector2(INFINITY, INFINITY);
		bool bOverlapping = SAT_CollisionTestHelper(AVerts, BVerts, AResolution) && SAT_CollisionTestHelper(BVerts, AVerts, BResolution);	

		// Has overlap occurred
		if (bOverlapping)
		{
			if (!ObjectA->IsOverlapping())
			{
				ObjectA->OnOverlapStart();
			}
			if (!ObjectB->IsOverlapping())
			{
				ObjectB->OnOverlapStart();
			}

			// The ratio of the resolution that should be applied to ObjectA
			float ResolutionAlpha = 1.f;
			
			const float AMass = ObjectA->Mass;
			const float BMass = ObjectB->Mass;

			// If both objects have the same mass, apply half of the resolve vector to each
			if (AMass == BMass)
			{
				ResolutionAlpha = 0.5;
			}
			// If one of the objects has no mass, apply all of the resolution to that object
			else if (AMass == 0.f || BMass == 0.f)
			{
				ResolutionAlpha = AMass == 0.f ? 1.f : 0.f;
			}
			// If each object has a unique non-zero mass, apply the resolution based on the ratio between the two masses
			else
			{
				ResolutionAlpha = BMass / (AMass + BMass);
			}

			AResolution *= ResolutionAlpha;
			BResolution *= (1 - ResolutionAlpha);

			ApplyResolution(ObjectA, AResolution);
			ApplyResolution(ObjectB, BResolution);

			const Vector2 APos = ColliderA->Root->Transform.GetPosition();
			const Vector2 BPos = ColliderB->Root->Transform.GetPosition();
			RenderManager::Get()->DrawDebugLine(APos, APos + AResolution, Colors::Blue);
			RenderManager::Get()->DrawDebugLine(BPos, BPos + BResolution, Colors::Blue);
		}
		else
		{
			if (ObjectA->IsOverlapping())
			{
				ObjectA->OnOverlapEnd();
			}
			if (ObjectB->IsOverlapping())
			{
				ObjectB->OnOverlapEnd();
			}
		}
	}
}

bool PhysicsManager::SAT_CollisionTestHelper(const vector<Vector2> AVerts, const vector<Vector2> BVerts, Vector2& OutResolution)
{
	bool bOverlapping = true;
	OutResolution = Vector2(INFINITY, INFINITY);

	// For each edge in ColliderA
	for (int ae = 0; ae < AVerts.size(); ae++)
	{
		// Use the ae index as one point of the edge, and the next index as the other. If ae is the last vertex, circle back to the first vertex
		const Vector2 Edge = AVerts[ae < AVerts.size() - 1 ? ae + 1 : 0] - AVerts[ae];
		const Vector2 EdgeNormal = Edge.GetNormal();

		const Vector2 DebugEdgeCenter = (Edge * 0.5) + AVerts[ae];
		RenderManager::Get()->DrawDebugLine(DebugEdgeCenter, DebugEdgeCenter + EdgeNormal, Colors::Red);

		// The min and max value for each object after being projected to the edges normal
		Vector2 AMinMax;
		Vector2 BMinMax;

		// Get min and max values for each shape after being projected to the normal
		SAT_ProjectionHelper(AVerts, EdgeNormal, AMinMax);
		SAT_ProjectionHelper(BVerts, EdgeNormal, BMinMax);

		// The direction A is compared to B
		const int ADirection = AMinMax.Y > BMinMax.Y ? 1 : -1;
		const float OverlapAmount = ADirection > 0 ? -(AMinMax.X - BMinMax.Y) : AMinMax.Y - BMinMax.X;

		// If there is no overlap on an edge, the shapes are no overlapping
		if (OverlapAmount <= 0)
		{
			bOverlapping = false;
			break;
		}
		// If we are overlapping, cache the resolution if it is smaller than the current
		else if (OverlapAmount < fabs(OutResolution.Length()))
		{
			OutResolution = EdgeNormal * (OverlapAmount * ADirection);
		}
	}

	return bOverlapping;
}

void PhysicsManager::SAT_ProjectionHelper(const std::vector<Vector2> Verts, const Vector2 Normal, Vector2& OutMinMax)
{
	OutMinMax = Vector2(INFINITY, -INFINITY);

	for (int v = 0; v < Verts.size(); v++)
	{
		const float ProjectedPos = Vector2::Dot(Normal, Verts[v]);

		if (ProjectedPos > OutMinMax.Y)
		{
			OutMinMax.Y = ProjectedPos;
		}

		if (ProjectedPos < OutMinMax.X)
		{
			OutMinMax.X = ProjectedPos;
		}
	}
}

void PhysicsManager::ApplyResolution(PhysicsComponent2D* Object, Vector2 Resolution)
{
	if (Object2D* Parent = Object->GetOwner2D())
	{
		Parent->Transform.TranslateGlobal(Resolution);

		// If the resolution opposes the velocity, just set the velocity to 0.0 for now
		const float ResolutionDotVelocity = Vector2::Dot(Resolution, Object->Velocity);
		if (ResolutionDotVelocity < 0.f)
		{
			Vector2 DeltaVelocity = Vector2::Normalize(Resolution) * fabs(ResolutionDotVelocity);
			Object->Velocity += DeltaVelocity;
		}
	}
}
