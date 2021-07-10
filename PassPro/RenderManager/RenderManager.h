#pragma once

#include <d3d11.h>
#include <array>
#include "../Math/VectorLibrary.h"

struct TShader
{
	const void* ByteCode = nullptr;
	unsigned int ByteCodeSize = 0;
};

struct TVertexShader : public TShader
{
	ID3D11VertexShader* Shader = nullptr;
};

struct TPixelShader : public TShader
{
	ID3D11PixelShader* Shader = nullptr;
};

struct Vertex2D
{
	Vector2 Position;
	Vector4 Color;

	Vertex2D(Vector2 InPosition, Vector4 InColor)
	{
		Position = InPosition;
		Color = InColor;
	}

	Vertex2D(float InX, float InY, Vector4 InColor)
	{
		Position.X = InX;
		Position.Y = InY;
		Color = InColor;
	}
};

struct DebugVertex2D
{
	Vector2 Position;
	Vector4 Color;

	DebugVertex2D() : Position(), Color() {};

	DebugVertex2D(Vector2 InPosition, Vector4 InColor)
	{
		Position = InPosition;
		Color = InColor;
	}

	DebugVertex2D(float InX, float InY, Vector4 InColor)
	{
		Position.X = InX;
		Position.Y = InY;
		Color = InColor;
	}
};

class RenderManager
{
public:
	
	/* Getter for singleton instance */
	static RenderManager* Get();

	static RenderManager* Initialize(HWND hWnd);

	~RenderManager();

	/* Null checks and releases ObjectToRelease */
	static void SafeRelease(IUnknown* OjbectToRelease);

	void PreRender();
	void PresentRender();

	ID3D11Device* GetDevice() { return DxDevice; }

	TVertexShader* GetDefault2DVertexShader() { return &Default2DVertexShader; };
	TPixelShader* GetDefault2DPixelShader() { return &Default2DPixelShader; };

	void RenderMesh(class RMesh* Mesh);

	void DrawDebugLine(const Vector2& PointA, const Vector2& PointB, const Vector4& Color);
	
protected:

	// For init
	ID3D11Device* DxDevice = nullptr;
	IDXGISwapChain* DxSwapChain = nullptr;

	// For drawing
	ID3D11DeviceContext* DxDeviceContext = nullptr;
	ID3D11RenderTargetView* DxRenderTargetView = nullptr;
	D3D11_VIEWPORT DxViewport = D3D11_VIEWPORT();

	TVertexShader Default2DVertexShader;
	TPixelShader Default2DPixelShader;

	// Debug Rendering
	ID3D11InputLayout* DebugInputLayout = nullptr;
	ID3D11VertexShader* Debug2DVertexShader = nullptr;
	ID3D11PixelShader* Debug2DPixelShader = nullptr;
	ID3D11Buffer* DebugVertexBuffer = nullptr;

	static const size_t MAX_LINE_VERTS = 1000;
	size_t DebugVertCount = 0;
	std::array<DebugVertex2D, MAX_LINE_VERTS> DebugLineVerts;

	void RenderDebugLines();

private:
	/* Private Default Constructor due to class being singleton */
	RenderManager() {};

	/* Private initialization Constructor due to class being singleton */
	RenderManager(HWND);

	/* Singleton instance of this class */
	static RenderManager* Instance;
};