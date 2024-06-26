#pragma once
#include "Component.h"
#include "../RenderManager/RenderManager.h"
#include "../RenderManager/Mesh.h"

/** 
* Adds a rendered element to an object
*
* Renders a mesh at the location of the parent object
*/
class CRenderingComponent : public IComponent
{
public:
	/** Constructs a RenderingComponent that renders the given mesh */
	CRenderingComponent(Object* InParent, RMesh* ComponentMesh);
	~CRenderingComponent();

	/** Renders the mesh */
	virtual void Render() override;

protected:
	/** Reference to the render manager to render the mesh */
	RenderManager* Renderer = nullptr;

	/** Mesh that is rendered at the location of the parent object */
	RMesh* Mesh = nullptr;
	
};