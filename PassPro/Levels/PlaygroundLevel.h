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
	Object2D* SquareObject = nullptr;

};
