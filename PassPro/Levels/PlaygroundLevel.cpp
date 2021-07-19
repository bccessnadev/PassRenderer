#include "PlaygroundLevel.h"

#include "../ObjectManager/ObjectManager.h"
#include "../Components/RenderingComponent.h"
#include "../Components/MovementComponent2D.h"
#include "../InputManager/InputManager.h"

void PlaygroundLevel::InitializeLevel()
{
    TriangleObject = new Object2D(Vector2(), 0.f, Vector2(5.f, 5.f));
    TriangleObject->AddComponent(new CRenderingComponent(TriangleObject, RMesh::Triangle({ 0.f, 0.5f }, { 0.5f, -0.5f }, { -0.5f, -0.5f }, { 1.f, 0.f, 0.f, 1.f })));
    TriangleObject->AddComponent(new MovementComponent2D(TriangleObject));
    Objects->AddObject(TriangleObject);
}

void PlaygroundLevel::DestructLevel()
{
}

void PlaygroundLevel::UpdateLevel(double DeltaTime)
{
    ILevel::UpdateLevel(DeltaTime);
}