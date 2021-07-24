#include "Mesh.h"

using namespace std;

RMesh::RMesh()
{
	Renderer = RenderManager::Get();
	VertexShader = Renderer->GetDefault2DVertexShader();
	PixelShader = Renderer->GetDefault2DPixelShader();
}

RMesh::RMesh(const std::vector<Vertex2D>& MeshVerticies, TVertexShader* MeshVertexShader, TPixelShader* MeshPixelShader)
{
	Renderer = RenderManager::Get();
	VertexShader = MeshVertexShader ? MeshVertexShader : Renderer->GetDefault2DVertexShader();
	PixelShader = MeshPixelShader ? MeshPixelShader : Renderer->GetDefault2DPixelShader();

	Verticies = MeshVerticies;

	Construct2DInputLayout();
	ConstructVertexBuffer();
}

RMesh* RMesh::Triangle(const Vector2 Point1, const Vector2 Point2, const Vector2 Point3, const Vector4 Color) 
{
	vector<Vertex2D> TriangleVerts;
	TriangleVerts.push_back(Vertex2D(Point1, Color));
	TriangleVerts.push_back(Vertex2D(Point2, Color));
	TriangleVerts.push_back(Vertex2D(Point3, Color));

	return new RMesh(TriangleVerts);
}

RMesh* RMesh::Square(const Vector2 Size, const Vector4 Color)
{
	const Vector2 HalfSize = Size * 0.5f;
	vector<Vertex2D> SquareVerts;
	SquareVerts.push_back(Vertex2D(HalfSize, Color));
	SquareVerts.push_back(Vertex2D(Vector2(HalfSize.X, -HalfSize.Y), Color));
	SquareVerts.push_back(Vertex2D(Vector2(-HalfSize.X, -HalfSize.Y), Color));
	SquareVerts.push_back(Vertex2D(Vector2(-HalfSize.X, -HalfSize.Y), Color));
	SquareVerts.push_back(Vertex2D(Vector2(-HalfSize.X, HalfSize.Y), Color));
	SquareVerts.push_back(Vertex2D(HalfSize, Color));

	return new RMesh(SquareVerts);
}

RMesh::~RMesh()
{
	RenderManager::SafeRelease(VertexBuffer);
	RenderManager::SafeRelease(InputLayout);
}

void RMesh::Construct2DInputLayout()
{
	if (ID3D11Device* Device = Renderer->GetDevice())
	{
		D3D11_INPUT_ELEMENT_DESC InputDesc[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8 /* POS is 8 bytes because it is 2 floats. So color has an offset of 8 */, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		Device->CreateInputLayout(InputDesc, 2/* Num elements in InputDesc */, VertexShader->ByteCode, VertexShader->ByteCodeSize, &InputLayout);
	}
}

void RMesh::ConstructVertexBuffer()
{
	if (ID3D11Device* Device = Renderer->GetDevice())
	{
		D3D11_BUFFER_DESC BufferDesc;
		D3D11_SUBRESOURCE_DATA SubData;
		ZeroMemory(&BufferDesc, sizeof(BufferDesc));
		ZeroMemory(&SubData, sizeof(SubData));
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.ByteWidth = sizeof(Vertex2D) * Verticies.size();
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;

		SubData.pSysMem = Verticies.data();

		Device->CreateBuffer(&BufferDesc, &SubData, &VertexBuffer);
	}
}
