#pragma once
#include "Component.h"
#include "../RenderManager/RenderManager.h"
#include "../RenderManager/Mesh.h"


class CRenderingComponent : public IComponent
{
public:
	CRenderingComponent(Object* InParent, RMesh* ComponentMesh);
	~CRenderingComponent();

	virtual void Update(double DeltaTime) override;

	virtual void Render() override;

protected:
	RenderManager* Renderer = nullptr;
	RMesh* Mesh = nullptr;
	
};