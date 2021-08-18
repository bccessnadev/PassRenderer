#pragma once
#include <vector>
#include "Transform.h"

class PhysicsComponent2D;
class Object2D;

class ICollider
{
public:
	ICollider(Object2D* RootObject) : Root(RootObject) {}

	Object2D* Root;
};

class AABBCollider : public ICollider
{
public:
	AABBCollider(Object2D* RootObject, Vector2 ColliderSize);
	Vector2 Extent;
};

class ConvexCollider2D : public ICollider
{
public:
	ConvexCollider2D(Object2D* RootObject) : ICollider(RootObject) {}
	std::vector<Vector2> GetWorldSpaceVerticies() const;

protected:
	std::vector<Vector2> Verticies;
};

class BoxCollider2D : public ConvexCollider2D
{
public:
	BoxCollider2D(Object2D* RootObject, const Vector2& Scale = Vector2(1.f, 1.f), const Vector2& Offset = Vector2(0.f, 0.f), const float Rotation = 0.f);
};

class PhysicsManager
{
public:
	/* Getter for singleton instance */
	static PhysicsManager* Get();

	void RegisterPhysicsObject(PhysicsComponent2D* PhysicsObject);

	void Update(double DeltaTime = 0.f);

private:
	PhysicsManager() {}

	/* Singleton instance of this class */
	static PhysicsManager* Instance;

	/* Uses Separated Axis Theorem to test two convex shapes against each other */
	void TestConvexColliders_SAT(PhysicsComponent2D* ObjectA, PhysicsComponent2D* ObjectB);
	bool SAT_CollisionTestHelper(const std::vector<Vector2> AVerts, const std::vector<Vector2> BVerts, Vector2& OutResolution, bool& bUseOtherResolve);
	void SAT_ProjectionHelper(const std::vector<Vector2> Verts, const Vector2 Normal, Vector2& OutMinMax);

	void ApplyResolution(PhysicsComponent2D* Object, Vector2 Resolution);

	std::vector<PhysicsComponent2D*> PhysicsObjects;

};