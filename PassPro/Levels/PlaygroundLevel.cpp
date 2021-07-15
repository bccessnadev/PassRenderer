#include "PlaygroundLevel.h"

#include "../ObjectManager/ObjectManager.h"
#include "../Components/RenderingComponent.h"
#include "../InputManager/InputManager.h"

PlaygroundLevel::PlaygroundLevel()
{
}

PlaygroundLevel::~PlaygroundLevel()
{
    // TODO: this doesn't get called
    if (InputManager* IM = InputManager::Get())
    {
        IM->UnbindFromKeyPressed(unsigned int('W'), ForwardInputBind);
    }
}

void PlaygroundLevel::InitializeLevel()
{
    TriangleObject = new Object2D(Vector2(), 0.f, Vector2(5.f, 5.f));
    CRenderingComponent* TriangleRenderComponent = new CRenderingComponent(TriangleObject, RMesh::Triangle({ 0.f, 0.5f }, { 0.5f, -0.5f }, { -0.5f, -0.5f }, { 1.f, 0.f, 0.f, 1.f }));
    TriangleObject->AddComponent(TriangleRenderComponent);
    Objects->AddObject(TriangleObject);

    if (InputManager* IM = InputManager::Get())
    {
        // TODO: Find better way to bind so we don't have to keep references like this
        ForwardInputBind = new DelegateCallback<PlaygroundLevel>(this, &PlaygroundLevel::ForwardInput);
        IM->BindToKeyPressed(unsigned int('W'), ForwardInputBind);
    }
}

void PlaygroundLevel::UpdateLevel(double DeltaTime)
{
    TriangleObject->Transform.SetRotation(Rotation);
    TriangleObject->Transform.SetPosition(Vector2(cosf(PositionVal) * 25.0f, sinf(PositionVal) * 25.0f));
    TriangleObject->Transform.SetScale(Vector2((cosf(ScaleVal) + 1.5f) * 2.5f, (sinf(ScaleVal) + 1.5f)) * 2.5f);

    Rotation += 0.01f;
    ScaleVal += 0.01f;

    // Make Debug Lines
    Matrix2D DebugMatrix = TriangleObject->Transform.Matrix;
    Vector2 XAxis(DebugMatrix._11, DebugMatrix._21);
    Vector2 YAxis(DebugMatrix._12, DebugMatrix._22);
    Vector2 Position(DebugMatrix._13, DebugMatrix._23);
    XAxis = XAxis + Position;
    YAxis = YAxis + Position;
    Renderer->DrawDebugLine(Position, XAxis, Vector4(1.f, 1.f, 1.f, 1.f));
    Renderer->DrawDebugLine(Position, YAxis, Vector4(1.f, 1.f, 1.f, 1.f));

    Vector2 LocalVector1(0.25f, 0.4f);
    Vector2 GlobalVector1 = DebugMatrix * LocalVector1;
    Vector2 LocalVector2(0.5f, 0.5f);
    Vector2 GlobalVector2 = DebugMatrix * LocalVector2;

    Renderer->DrawDebugLine(GlobalVector1, GlobalVector2, Vector4(0.f, 1.f, 0.f, 1.f));
}

void PlaygroundLevel::ForwardInput()
{
    PositionVal += 0.01f;
}
