#pragma once
#include <vector>
#include <string>

#include "../Components/Component.h"
#include "../Math/Transform.h"

class ObjectManager;

class Object
{
public:
	/* Incremented each time a new object it constructed. Used to give each object a unique identifier */
	static int CurrentInstanceID;

	/* Unique name of this Object. Can be used to find this object in the Entity Manager. Useful for debugging*/
	std::string Name = "Object";

	/* Unique number identifier of this object */
	int InstanceID = 0;
	int Priority = 0;
	//Transform Transform;
	ObjectManager* ObjectManager = nullptr;

	Object();
	Object(const std::string ObjectName);
	~Object();

	inline bool IsActive() { return bIsActive; }

	/*****************************************************************
								 SETTERS
	*****************************************************************/

	inline void SetIsActive(bool NewIsActive) { bIsActive = NewIsActive; }

	/******************************************************************
		AddComponent()
		Adds the component passed in to the GameObjects component
			collection

		IN:
					Component -		The Component to add to the
										collection

	******************************************************************/
	void AddComponent(IComponent* component);

	/******************************************************************
		FindComponent()
		Returns the first component of that type in the GameObjects
			collection. Returns a nullptr if there is no component
			of that type

		IN:
					ComponentType -		The type of component to look
											for

	******************************************************************/
	//IComponent* FindComponent(ComponentType::Type type);


	/******************************************************************
		GetComponentsOfType()
		Returns all components of that type in the GameObjects
			collection. Returns a empty vector if there are no
			components of that type.

		IN:
					ComponentType -		The type of component to look
											for

	******************************************************************/
	//std::vector<IComponent*> GetComponentsOfType(ComponentType::Type type);


	/******************************************************************
		GetAllComponents()
		Returns the collection of components the GameObject has
	******************************************************************/
	std::vector<IComponent*> GetAllComponents();


	/******************************************************************
		Update()
		Updates all of the components in the GameObject
	******************************************************************/
	void Update(double DeltaTime);

	/******************************************************************
		Render()
		Renders all of the components in the GameObject
	******************************************************************/
	void Render();

	/******************************************************************
		RemoveComponent()
		Removes a component from the GameObject
	******************************************************************/
	void RemoveComponent(IComponent* ComponentToRemove);

private:
	std::vector<IComponent*> Components;
	bool bIsActive = true;

};

class Object2D : public Object
{
public:
	Object2D() {}
	Object2D(const Vector2 Position, const float RotationInRads, const Vector2 Scale) : Transform(Position, RotationInRads, Scale) {}
	Object2D(const Vector2 Position, const float RotationInRads, const Vector2 Scale, const std::string ObjectName) : Object(ObjectName), Transform(Position, RotationInRads, Scale) {}
	Transform2D Transform;
};