#include "LevelManager.h"
#include "Level.h"

LevelManager::LevelManager(ILevel* LevelToManage)
{
	LoadedLevel = LevelToManage;
	LoadedLevel->InitializeLevel();
}

LevelManager::~LevelManager()
{
	LoadedLevel->DestructLevel();
	delete LoadedLevel;
}

void LevelManager::Update(double DeltaTime)
{
	LoadedLevel->UpdateLevel(DeltaTime);
}

void LevelManager::Render()
{
	LoadedLevel->RenderLevel();
}
