#pragma once
#include <vector>
#include "Transform.h"

class PhysicsComponent2D;
class Object2D;
class Transform2D;

/**
* Interface for any kind of 2D collider
*/
class ICollider2D
{
public:
	ICollider2D(Object2D* RootObject) : Root(RootObject) {}

	/** Get the transform of the root object */
	Transform2D GetTransform() const;

protected:
	/** Object collider is attached to. Used to get transform */
	Object2D* Root;
};

/**
* 2D Aligned Axis Bounding Box Collider
* 
* A 2D box collider that cannot be rotated
*/
class AABBCollider2D : public ICollider2D
{
public:
	/** 
	* Constructs a 2D AABB box 
	* @param RootObject The Object this collider is attached to
	* @param ColliderSize How large the collider is relative to the RootObject
	*/
	AABBCollider2D(Object2D* RootObject, Vector2 ColliderSize);

	/** Returns the half size of the AABB */
	Vector2 GetExtent() const { return Extent; }

protected:
	/** 
	* Defines size of the collider
	*
	* The X value of the vector defines half the width
	* The Y value of the vector defines half the height
	*/
	Vector2 Extent;
};

/**
* Base class for 2D convex colliders
*/
class ConvexCollider2D : public ICollider2D
{
public:
	ConvexCollider2D(Object2D* RootObject) : ICollider2D(RootObject) {}

	/** Returns a collection of points in world space that make up this shape */
	std::vector<Vector2> GetWorldSpaceVerticies() const;

protected:
	/** Contains a location of points in local space that make up the convex shape */
	std::vector<Vector2> Verticies;
};

/**
* A 2D box collider that can be scaled, offset, and rotated
*/
class BoxCollider2D : public ConvexCollider2D
{
public:
	/** 
	* Constructs a 2D box 
	* @param RootObject The Object this collider is attached to
	* @param Scale How large the collider is relative to the RootObject
	* @param Offset Offset position from the RootObject location
	* @param Rotation Rotation relative to the RootObject
	*/
	BoxCollider2D(Object2D* RootObject, const Vector2& Scale = Vector2(1.f, 1.f), const Vector2& Offset = Vector2(0.f, 0.f), const float Rotation = 0.f);
};

/**
* Singleton Manager that updates all registered physics components
* 
* Calculates whether collision objects are overlapping.
* If there are overlapping colliders, colliders will be notified
* and the collision will be resolved if needed.
*/
class PhysicsManager
{
public:
	/** Getter for singleton instance */
	static PhysicsManager* Get();

	/** 
	* Adds a component to be updated by the physics manager 
	*
	* This is required for a physics component to function
	*/
	void RegisterPhysicsObject(PhysicsComponent2D* PhysicsObject);

	/** Tests for overlapping colliders and handles those overlaps */
	void Update(double DeltaTime = 0.f);

private:
	PhysicsManager() {}

	/** Singleton instance of this class */
	static PhysicsManager* Instance;

	/** Uses Separated Axis Theorem to test two convex shapes against each other */
	void TestConvexColliders_SAT(PhysicsComponent2D* ObjectA, PhysicsComponent2D* ObjectB) const;

	/** Separated Axis Theorem helper function to determine whether shapes defined by the given verticies are overlapping and gives the required resolution */
	bool SAT_CollisionTestHelper(const std::vector<Vector2> AVerts, const std::vector<Vector2> BVerts, Vector2& OutResolution, bool& bUseOtherResolve) const;

	/** Separated Axis Theorem helper function to determine the heights and lowest world location by projecting against a given normal vector */
	void SAT_ProjectionHelper(const std::vector<Vector2> Verts, const Vector2 Normal, Vector2& OutMinMax) const;

	/** Adjusts the location an object based on a resolution to prevent overlapping with another object */
	void ApplyResolution(PhysicsComponent2D* Object, Vector2 Resolution) const;

	/** Collection of registered physics components that will be updated */
	std::vector<PhysicsComponent2D*> PhysicsObjects;

};