#pragma once

class Object;

class IComponent
{
public:

	int Priority = 0;

	IComponent(Object* InParent) { Parent = InParent; }

	virtual ~IComponent() {}

	/*****************************************************************
								 GETTERS
	*****************************************************************/

	inline Object* GetOwner() { return Parent; }
	inline bool GetIsEnabled() { return IsEnabled; }

	/*****************************************************************
								 SETTERS
	*****************************************************************/

	virtual inline void SetIsEnabled(bool NewIsEnabled) { IsEnabled = NewIsEnabled; }

	virtual void Update(double deltaTime = 0) {};

	virtual void Render() {};

protected:

	Object* Parent;

	bool IsEnabled = true;
};
