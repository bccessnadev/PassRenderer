#pragma once
#include <vector>
#include <string>

#include "../Components/Component.h"
#include "../Math/Transform.h"

class ObjectManager;

/**
 * The Object class represents an entity within the game engine.
 *
 * Each Object has a unique identifier and can be managed by the Entity Manager.
 * Objects can have components added to them, which define their behavior and attributes.
 * The class provides functionality to add, remove, find, update, and render components.
 */
class Object
{
	friend ObjectManager;

public:
	Object();
	Object(const std::string ObjectName);
	~Object();

	/** Incremented each time a new object it constructed. Used to give each object a unique identifier */
	static int CurrentInstanceID;

	/** Unique name of this Object. Can be used to find this object in the Entity Manager */
	std::string Name = "Object";

	/** Unique number identifier of this object */
	int InstanceID = 0;

	/** 
	* Determines update order of the object relative to other objects.
	* 
	* Objects are udpate by heighest priorety number to lowest.
	*/
	int Priority = 0;

	/** @return Is this object active and being udpated and rendered */
	inline bool IsActive() { return bIsActive; }

	/** Stop or start updating and rendering this object */
	inline void SetIsActive(bool NewIsActive) { bIsActive = NewIsActive; }

	/**
	 * Adds the component passed in to the GameObject's component collection.
	 *
	 * @param component The Component to add to the collection.
	 */
	void AddComponent(IComponent* component);

	/**
	 * Returns the first component of the template class in the GameObject's collection.
	 * Returns a nullptr if there is no component of that type.
	 *
	 * @tparam T The type of component to find.
	 * @return The first component of the specified type, or nullptr if not found.
	 */
	template<typename T>
	T FindComponent()
	{
		for (int c = 0; c < Components.size(); c++)
		{
			if (T ComponentOfType = static_cast<T>(Components[c]))
			{
				return ComponentOfType;
			}
		}

		return nullptr;
	}

	/**
	 * Returns the collection of components the Object has.
	 *
	 * @return A vector containing all components of the Object.
	 */
	std::vector<IComponent*> GetAllComponents();

	/**
	 * Updates all of the active components in the Object.
	 *
	 * @param DeltaTime The time elapsed since the last update.
	 */
	void Update(double DeltaTime);

	/** Renders all of the components in the Object. */
	void Render();

	/**
	 * Removes a component from the Object.
	 *
	 * @param ComponentToRemove The component to remove.
	 */
	void RemoveComponent(IComponent* ComponentToRemove);

	/** @return Object manager that updates this object */
	ObjectManager* GetObjectManager() { return ObjectManager; }

protected:
	/** Reference to ObjectManager that updates this object */
	ObjectManager* ObjectManager = nullptr;

private:
	/** Components on this object to be updated and rendered */
	std::vector<IComponent*> Components;

	/** Whether this object is being udpated and rendered */
	bool bIsActive = true;
};

/**
 * The Object2D class represents a 2D object within the game engine.
 *
 * It inherits from the Object class and includes a 2D transform
 * that defines its position, rotation, and scale in 2D space.
 */
class Object2D : public Object
{
public:
	/** Default constructor. Initializes a 2D object with default values. */
	Object2D() {}

	/**
    * Constructor to initialize a 2D object with specified position, rotation, and scale.
    *
    * @param Position The position of the object in 2D space.
    * @param RotationInRads The rotation of the object in radians.
    * @param Scale The scale of the object in 2D space.
    */
	Object2D(const Vector2 Position, const float RotationInRads, const Vector2 Scale) : Transform(Position, RotationInRads, Scale) {}

	/**
	* Constructor to initialize a 2D object with specified position, rotation, scale, and name.
	*
	* @param Position The position of the object in 2D space.
	* @param RotationInRads The rotation of the object in radians.
	* @param Scale The scale of the object in 2D space.
	* @param ObjectName The name of the object.
	*/
	Object2D(const Vector2 Position, const float RotationInRads, const Vector2 Scale, const std::string ObjectName) : Object(ObjectName), Transform(Position, RotationInRads, Scale) {}

	/** The 2D transform of the object, defining its position, rotation, and scale in 2D space. */
	Transform2D Transform;
};