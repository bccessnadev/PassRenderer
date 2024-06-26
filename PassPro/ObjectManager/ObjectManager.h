#pragma once
#include "Object.h"
#include <unordered_map>
#include <queue>

/**
 * The ObjectManager class manages a collection of game objects within the engine.
 *
 * It is responsible for adding, removing, and accessing objects, as well as
 * updating and rendering all objects in the collection. The ObjectManager ensures
 * that all objects are properly managed and interact with each other as needed.
 */
class ObjectManager
{
public:

	~ObjectManager();

	/**
	* Returns a Object with the name passed in if it is in the
	*	collection. Otherwise, will return nullptr.
	* 
	* @param InName The name of the Object
	* @return An Object with the given name
	*/
	Object* FindObjectByName(const char* InName);

	/**
	* Adds an object to the ObjectManager to be updated and rendered.
	* 
	* It's name in the map will be whatever the Objects
	* current name is.
	*
	* @param Object The Object to add
	*/
	void AddObject(Object* Object);

	/**
	* Adds an object to the ObjectManager to be updated and rendered.
	* 
	* The name in the map will be what is passed in, and the
	* Objects will have it's name changed to it.
	*
	* @param Object The Object to add
	* @param Name The name of the Object
	*/
	void AddObject(Object* Object, const char* Name);

	/**
	* Removes an Object from the Entity Manager by name. 
	*
	* This is faster than removing by Object pointer.
	* 
	* @param Name The name of the Object to remove
	*/
	void DestroyObject(const char* Name);

	/**
	 * Destroys an Object.
	 *
	 * Removes an Object from the Entity Manager by name. This is slower than
	 * removing by name. This should only be used if the name in the Object
	 * does not match its name in the Entity Manager.
	 *
	 * @param Object The Object to remove.
	 */
	void DestroyObject(Object* Object);

	/**
	 * Updates all active Objects in the Entity Manager along with all Components on the Objects.
	 *
	 * @param DeltaTime The time elapsed since the last update (optional, default is 0).
	 */
	void Update(double DeltaTime = 0);

	/** Renders all active Objects in the Entity Manager along with all Components on the Objects. */
	void Render();

private:
	/** All objects, search-able by their unique name */
	std::unordered_map<std::string, Object*> Objects;

	/** All objects, in order of their priority to be updated */
	std::vector<Object*> PriorityObjects;
};