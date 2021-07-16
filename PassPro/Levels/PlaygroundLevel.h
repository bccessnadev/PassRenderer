#pragma once

#include "../ObjectManager/Level.h"

class Object2D;
template<typename CallbackObjectType> 
class DelegateCallback;

class PlaygroundLevel : public ILevel
{
public:
	virtual void InitializeLevel() override;
	virtual void DestructLevel() override;
	virtual void UpdateLevel(double DeltaTime) override;

protected:

	void ForwardInputPressed();
	void ForwardInputReleased();

	Object2D* TriangleObject = nullptr;

	DelegateCallback<PlaygroundLevel>* ForwardInputPressedBind;
	DelegateCallback<PlaygroundLevel>* ForwardInputReleasedBind;

	float Rotation = 0.f;
	float PositionVal = 0.f;
	float ScaleVal = 0.f;

	bool Move = false;
};
