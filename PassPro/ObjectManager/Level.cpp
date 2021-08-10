#include "Level.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "../RenderManager/RenderManager.h"
#include "../Math/PhysicsManager.h"

ILevel::ILevel()
{
	Objects = new ObjectManager();
	Renderer = RenderManager::Get();
	PhysicsEngine = PhysicsManager::Get();
}

ILevel::~ILevel()
{
	delete Objects;
}

void ILevel::UpdateLevel(double DeltaTime)
{
	PhysicsEngine->Update(DeltaTime);
	Objects->Update(DeltaTime);	
}

void ILevel::RenderLevel()
{
	Renderer->PreRender();
	Objects->Render();
	Renderer->PresentRender();
}
