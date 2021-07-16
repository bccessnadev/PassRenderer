#pragma once

class LevelManager;
class ObjectManager;
class RenderManager;

class ILevel
{
public: 
	ILevel();
	~ILevel();

	virtual void InitializeLevel() = 0;
	virtual void DestructLevel() {}
	virtual void UpdateLevel(double DeltaTime);
	virtual void RenderLevel();

protected:
	ObjectManager* Objects = nullptr;
	RenderManager* Renderer = nullptr;
};