#pragma once
#include "Object.h"
#include <unordered_map>
#include <queue>

class ObjectManager
{
public:

	~ObjectManager();

	/******************************************************************
		FindObjectByName()
		Returns a Object with the name passed in if it is in the
			collection. Otherwise, will return nullptr.

		IN:
					const char* -	The name of the Object

		OUT:
					Object* -	A Object with the name passed in

	******************************************************************/
	Object* FindObjectByName(const char* InName);


	/******************************************************************
		FindObjectsWithComponent()
		Returns all Objects that contain a component of the type
			passed in

		IN:
					ComponentType -	The type of component that will be
										searched for

		OUT:
				std::vector<Object*> -	A collection of Objects
												that have a component
												of the type passed in


	******************************************************************/
	//std::vector<Object*> FindObjectsWithComponent(ComponentType::Type Type);

	/******************************************************************
		AddObject()
		Adds an object to the ObjectManager to be updated and rendered.
			It's name in the map will be whatever the Objects
			current name is.

		IN:
					Object* -	The Object to add

	******************************************************************/
	void AddObject(Object* Object);
	/******************************************************************
		AddObject()
		Adds an object to the ObjectManager to be updated and rendered.
			The name in the map will be what is passed in, and the
			Objects will have it's name changed to it.

		IN:
					Object* -	The Object to add

					const char* -	The name of the Object

	******************************************************************/
	void AddObject(Object* Object, const char* Name);

	/******************************************************************
		DestroyObject()
		Removes an Object from the Entity Manager by name. This is
			faster than removing by Object pointer.

		IN:
					const char* -	The name of the Object to remove

	******************************************************************/
	void DestroyObject(const char* Name);

	/******************************************************************
		DestroyObject()
		Removes an Object from the Entity Manager by name. This is
			slower than removing by name. This should only be used if
			the name in the Object does not match it's name in the
			Entity Manager

		IN:
					Object* -	The Object to remove

	******************************************************************/
	void DestroyObject(Object* Object);

	/******************************************************************
		Update()
		Updates all Objects in the Entity Manager, and therefore
			all Components in the Objects.
	******************************************************************/
	void Update(double DeltaTime = 0);

	/******************************************************************
		Render()
		Renders all Objects in the Entity Manager, and therefore
			all Components in the Objects.
	******************************************************************/
	void Render();
private:
	/* All objects, search-able by their unique name */
	std::unordered_map<std::string, Object*> Objects;

	/* All objects, in order of their priority to be updated */
	std::vector<Object*> PriorityObjects;
};