#include "Level.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "../RenderManager/RenderManager.h"

ILevel::ILevel()
{
	Objects = new ObjectManager();
	Renderer = RenderManager::Get();
}

ILevel::~ILevel()
{
	delete Objects;
}

void ILevel::UpdateLevel(double DeltaTime)
{
	Objects->Update(DeltaTime);	
}

void ILevel::RenderLevel()
{
	Renderer->PreRender();
	Objects->Render();
	Renderer->PresentRender();
}
