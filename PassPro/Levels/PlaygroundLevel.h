#pragma once

#include "../ObjectManager/Level.h"

class Object2D;
template<typename CallbackObjectType> 
class DelegateCallback;

class PlaygroundLevel : public ILevel
{
public:
	PlaygroundLevel();
	~PlaygroundLevel();

	virtual void InitializeLevel() override;
	virtual void UpdateLevel(double DeltaTime) override;

protected:

	void ForwardInput();

	Object2D* TriangleObject = nullptr;

	DelegateCallback<PlaygroundLevel>* ForwardInputBind;

	float Rotation = 0.f;
	float PositionVal = 0.f;
	float ScaleVal = 0.f;
};
