#pragma once

class LevelManager;
class ObjectManager;
class RenderManager;
class PhysicsManager;

/**
* Interface for level that contains Objects to be updated and rendered
* 
* Can be implemented to act as a place to create objects that should exsist in the
* game while the level is loaded.
* 
* Level can be loaded by level manager to have all objects updated and rendered.
*/
class ILevel
{
public: 
	ILevel();
	~ILevel();

	/** 
	* Implement to create objects that exist in the level.
	* 
	* Construct objects with components that define their functionality,
	* then add the object to the ObjectManager after all of it's properties
	* have been set to the desired values.
	*/
	virtual void InitializeLevel() = 0;

	/** Any objects that get created in this level should be deleted here */
	virtual void DestructLevel() {}

	/** 
	* Updates the physics engine and object manager.
	* 
	* Can be overriden to handle changes in the level over time
	*/
	virtual void UpdateLevel(double DeltaTime);

	/** Renders all active objects in the object manager */
	virtual void RenderLevel();

protected:
	/** Object Manager that stores and manages all of the objects */
	ObjectManager* Objects = nullptr;

	/** Render Manager used to render the level */
	RenderManager* Renderer = nullptr;

	/** Physics Engine used to handle physics in the level */
	PhysicsManager* PhysicsEngine = nullptr;
};