#pragma once

class ILevel;

/**
* The LevelManager handles loading levels as well as updating and rendering the current level
*/
class LevelManager
{
public:	
	LevelManager(ILevel* LevelToManage);
	~LevelManager();

	/** Udpates loaded level */
	void Update(double DeltaTime = 0);

	/** Renders loaded level */
	void Render();

protected:
	/** Active level to be updared and rendered */
	ILevel* LoadedLevel = nullptr;
};