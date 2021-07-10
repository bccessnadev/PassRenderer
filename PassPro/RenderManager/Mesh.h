#pragma once
#include <vector>
#include "RenderManager.h"

class RMesh
{
	friend class RenderManager;

public:
	RMesh();
	RMesh(const std::vector<Vertex2D>& MeshVerticies, TVertexShader* MeshVertexShader = 0, TPixelShader* MeshPixelShader = 0);

	~RMesh();

	/* Returns a triangle mesh */
	static RMesh* Triangle(Vector2 Point1, Vector2 Point2, Vector2 Point3, Vector4 Color);

protected:

	void Construct2DInputLayout();
	void ConstructVertexBuffer();

	RenderManager* Renderer = nullptr;

	std::vector<Vertex2D> Verticies;
	//std::vector<unsigned int> Indicies;
	ID3D11Buffer* VertexBuffer = nullptr;
	//ID3D11Buffer* IndexBuffer = nullptr;
	ID3D11InputLayout* InputLayout = nullptr;
	TVertexShader* VertexShader = nullptr;
	TPixelShader* PixelShader = nullptr;
};