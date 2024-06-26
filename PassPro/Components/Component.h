#pragma once

class Object;

/**
* @class Component
* @brief class for a component that is attached to an Object
* to give the object special functionality defined by the component.
* 
* Component can have unique logic that can be updated and rendered.
* This can be used to add functionality and store data for an object
*/
class IComponent
{
public:
	/** 
	* Determines order in which this component is updated and rendered on the object
	* relative to other components
	* 
	* The higher the priority, the earlier the component will be updated.
	*/
	int Priority = 0;

	/** Component base constructor. Parent object is required to create component */
	IComponent(Object* InParent) { Parent = InParent; }

	virtual ~IComponent() {}

	/** Returns the object the component is attached to */
	inline Object* GetOwner() { return Parent; }

	/** Returns whether the component should be updated, rendered, and considered active */
	inline bool GetIsEnabled() { return IsEnabled; }

	/** Set whether the component should be updated, rendered, and considered active */
	virtual inline void SetIsEnabled(bool NewIsEnabled) { IsEnabled = NewIsEnabled; }

	/** Override to add logic that should be updated every frame */
	virtual void Update(double deltaTime = 0) {};

	/** Override to add rendering logic to the component */
	virtual void Render() {};

protected:
	/** Object this component is attached to and updated by */
	Object* Parent;

	/** Should this component be updated, rendered, and considered active */
	bool IsEnabled = true;
};
