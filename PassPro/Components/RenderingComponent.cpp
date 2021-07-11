#include "RenderingComponent.h"
#include "../ObjectManager/Object.h"

CRenderingComponent::CRenderingComponent(Object* InParent, RMesh* ComponentMesh) : IComponent(InParent), Mesh(ComponentMesh)
{
	Renderer = RenderManager::Get();
}

CRenderingComponent::~CRenderingComponent()
{
	delete Mesh;
}

void CRenderingComponent::Update(double DeltaTime)
{
}

void CRenderingComponent::Render()
{
	if (Object2D* Owner = static_cast<Object2D*>(GetOwner()))
	{
		Renderer->RenderMesh(Mesh, Owner->Transform);
	}
}
