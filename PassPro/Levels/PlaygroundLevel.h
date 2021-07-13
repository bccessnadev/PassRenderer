#pragma once

#include "../ObjectManager/Level.h"

class Object2D;

class PlaygroundLevel : public ILevel
{
public:
	PlaygroundLevel();

	virtual void InitializeLevel() override;
	virtual void UpdateLevel(double DeltaTime) override;

protected:

	Object2D* TriangleObject = nullptr;

	float Rotation = 0.f;
	float PositionVal = 0.f;
	float ScaleVal = 0.f;
};
