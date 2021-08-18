#include "PlaygroundLevel.h"

#include "../ObjectManager/ObjectManager.h"
#include "../Components/RenderingComponent.h"
#include "../Components/MovementComponent2D.h"
#include "../Components/PhysicsComponent.h"
#include "../InputManager/InputManager.h"

void PlaygroundLevel::InitializeLevel()
{
    SquareObject = new Object2D(Vector2(), 0.f, Vector2(5.f, 5.f), "Player");
    PhysicsComponent2D* PhysicsComponent = new PhysicsComponent2D(SquareObject, new BoxCollider2D(SquareObject));
    PhysicsComponent->bDebugDraw = true;
    PhysicsComponent->Mass = 0.f;
    SquareObject->AddComponent(PhysicsComponent);
    MovementComponent2D* MovementComponent = new MovementComponent2D(SquareObject);
    MovementComponent->Friction = 3.f;
    SquareObject->AddComponent(MovementComponent);
    Objects->AddObject(SquareObject);

    PhysicsDummy = new Object2D(Vector2(0.f,-10.f), 0.f, Vector2(5.f, 5.f), "Dummy");
    PhysicsComponent2D* PhysicsComponentB = new PhysicsComponent2D(PhysicsDummy, new BoxCollider2D(PhysicsDummy));
    PhysicsComponentB->bDebugDraw = true;
    PhysicsComponentB->Mass = 2.f;
    PhysicsDummy->AddComponent(PhysicsComponentB);
    PhysicsDummy->AddComponent(new MovementComponent2D(PhysicsDummy, 1));
    Objects->AddObject(PhysicsDummy);
}

void PlaygroundLevel::DestructLevel()
{

}

void PlaygroundLevel::UpdateLevel(double DeltaTime)
{
    ILevel::UpdateLevel(DeltaTime);
}