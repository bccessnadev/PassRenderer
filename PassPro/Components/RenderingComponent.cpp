#include "RenderingComponent.h"

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
	Renderer->RenderMesh(Mesh);
}
