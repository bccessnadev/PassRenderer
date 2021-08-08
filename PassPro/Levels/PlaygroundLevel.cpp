#include "PlaygroundLevel.h"

#include "../ObjectManager/ObjectManager.h"
#include "../Components/RenderingComponent.h"
#include "../Components/MovementComponent2D.h"
#include "../Components/PhysicsComponent.h"
#include "../InputManager/InputManager.h"

void PlaygroundLevel::InitializeLevel()
{
    SquareObject = new Object2D(Vector2(), 0.f, Vector2(5.f, 5.f));
    SquareObject->AddComponent(new MovementComponent2D(SquareObject));
    PhysicsComponent2D* PhysicsComponent = new PhysicsComponent2D(SquareObject, new AABBCollider(SquareObject, Vector2(1.f, 1.f)));
    PhysicsComponent->bDebugDraw = true;
    SquareObject->AddComponent(PhysicsComponent);
    Objects->AddObject(SquareObject);
}

void PlaygroundLevel::DestructLevel()
{

}

void PlaygroundLevel::UpdateLevel(double DeltaTime)
{
    ILevel::UpdateLevel(DeltaTime);
}