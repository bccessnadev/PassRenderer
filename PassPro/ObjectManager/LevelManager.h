#pragma once

class ILevel;

class LevelManager
{
public:
	
	LevelManager(ILevel* LevelToManage);
	~LevelManager();

	void Update(double DeltaTime = 0);
	void Render();

protected:
	ILevel* LoadedLevel = nullptr;
};