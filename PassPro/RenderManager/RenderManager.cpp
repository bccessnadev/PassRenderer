#include "RenderManager.h"

#pragma comment(lib, "d3d11.lib")

#include "Mesh.h"
#include <DirectXMath.h>

#include "Shaders/VS_Default.h"
#include "Shaders/PS_Default.h"
#include "Shaders/VS_Debug2D.h"

RenderManager* RenderManager::Instance = nullptr;

RenderManager* RenderManager::Get()
{
	return Instance;
}

RenderManager* RenderManager::Initialize(HWND hWnd)
{
	// If and instance already exists, return null pointer to signify that the initialization failed due to it already being initialized
	if (Instance)
	{
		return nullptr;
	}

	Instance = new RenderManager(hWnd);
	return Instance;
}

RenderManager::RenderManager(HWND hWnd)
{
	// Attach D3D11 to window
	RECT WndRect;
	GetClientRect(hWnd, &WndRect);

	// Swap Chain
	D3D_FEATURE_LEVEL DxFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC DxSwapChainDes;
	ZeroMemory(&DxSwapChainDes, sizeof(DXGI_SWAP_CHAIN_DESC));
	DxSwapChainDes.BufferCount = 2; // Set from 1 to 2 to support DXGI_SWAP_EFFECT_DISCARD
	DxSwapChainDes.OutputWindow = hWnd;
	DxSwapChainDes.Windowed = true;
	DxSwapChainDes.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // Upgraded version of DXGI_SWAP_EFFECT_DISCARD
	DxSwapChainDes.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DxSwapChainDes.BufferDesc.Width = WndRect.right - WndRect.left;
	DxSwapChainDes.BufferDesc.Height = WndRect.bottom - WndRect.top;
	DxSwapChainDes.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	DxSwapChainDes.SampleDesc.Count = 1; // Would need to be changed for anti aliasing

	HRESULT Hr;
	Hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG/* Need to change this when not debugging*/, &DxFeatureLevel, 1, D3D11_SDK_VERSION, &DxSwapChainDes, &DxSwapChain, &DxDevice, NULL, &DxDeviceContext);

	// Render Target View
	ID3D11Resource* BackBuffer;
	Hr = DxSwapChain->GetBuffer(0, __uuidof(BackBuffer), (void**)&BackBuffer);
	if (BackBuffer)
	{
		Hr = DxDevice->CreateRenderTargetView(BackBuffer, NULL, &DxRenderTargetView);
		BackBuffer->Release();
	}

	// View Port
	DxViewport.Width = (float)DxSwapChainDes.BufferDesc.Width;
	DxViewport.Height = (float)DxSwapChainDes.BufferDesc.Height;
	DxViewport.TopLeftX = DxViewport.TopLeftY = 0;
	DxViewport.MinDepth = 0;
	DxViewport.MaxDepth = 1;

	// Shaders
	//	Default 2D
	Default2DVertexShader.ByteCode = VS_Default;
	Default2DVertexShader.ByteCodeSize = sizeof(VS_Default);
	Hr = DxDevice->CreateVertexShader(VS_Default, sizeof(VS_Default), NULL, &Default2DVertexShader.Shader);
	Default2DPixelShader.ByteCode = PS_Default;
	Default2DPixelShader.ByteCodeSize = sizeof(PS_Default);
	Hr = DxDevice->CreatePixelShader(PS_Default, sizeof(PS_Default), NULL, &Default2DPixelShader.Shader);

	// Debug Rendering
	/* Currently using default things since the structs are the same as of now, 
	 but this will likely need to be changed in the future as more things are added to the default vertex */

	//	Input layout
	D3D11_INPUT_ELEMENT_DESC InputDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8 /* POS is 8 bytes because it is 2 floats. So color has an offset of 8 */, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	Hr = DxDevice->CreateInputLayout(InputDesc, 2/* Num elements in InputDesc */, VS_Default, sizeof(VS_Default), &DebugInputLayout);

	//	Vertex Buffer
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.ByteWidth = sizeof(DebugVertex2D) * MAX_LINE_VERTS;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;

	Hr = DxDevice->CreateBuffer(&BufferDesc, NULL, &DebugVertexBuffer);

	// Constant Buffer
	D3D11_BUFFER_DESC CBuffDesc;
	ZeroMemory(&CBuffDesc, sizeof(CBuffDesc));
	CBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CBuffDesc.Usage = D3D11_USAGE_DYNAMIC;

	CBuffDesc.ByteWidth = sizeof(DirectX::XMMATRIX); // Needs to be multiple of 16, so I can't use the Transform2D
	Hr = DxDevice->CreateBuffer(&CBuffDesc, 0, &Transform2D_CBuff);

	//	Shaders
	Hr = DxDevice->CreateVertexShader(VS_Debug2D, sizeof(VS_Debug2D), NULL, &Debug2DVertexShader);
	Debug2DPixelShader = Default2DPixelShader.Shader;

}

void RenderManager::SafeRelease(IUnknown* OjbectToRelease)
{
	if (OjbectToRelease)
	{
		OjbectToRelease->Release();
	}
}

RenderManager::~RenderManager()
{
	SafeRelease(DxDevice);
	SafeRelease(DxDeviceContext);
	SafeRelease(DxSwapChain);
	SafeRelease(DxRenderTargetView);
	SafeRelease(Default2DVertexShader.Shader);
	SafeRelease(Default2DPixelShader.Shader);
	SafeRelease(Transform2D_CBuff);
	SafeRelease(DebugInputLayout);
	SafeRelease(Debug2DVertexShader);
	SafeRelease(DebugVertexBuffer);
}

void RenderManager::PreRender()
{
	float BackColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	DxDeviceContext->ClearRenderTargetView(DxRenderTargetView, BackColor);

	// Output manager
	ID3D11RenderTargetView* TempRTVs[] = { DxRenderTargetView };
	DxDeviceContext->OMSetRenderTargets(1, TempRTVs, NULL /* Will probably need to set the depth stencil here eventually */);

	// Rasterizer
	DxDeviceContext->RSSetViewports(1, &DxViewport);
}

void RenderManager::RenderMesh(RMesh* Mesh, const Transform2D& MeshTransform)
{
	// Input Assembler
	DxDeviceContext->IASetInputLayout(Mesh->InputLayout);
	ID3D11Buffer* TempVertexBuffers[] = { Mesh->VertexBuffer };
	UINT TempStrides[] = { sizeof(Vertex2D) };
	UINT TempOffsets[] = { 0 };
	DxDeviceContext->IASetVertexBuffers(0, 1, TempVertexBuffers, TempStrides, TempOffsets);
	DxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Vertex Shader
	DxDeviceContext->VSSetShader(Mesh->VertexShader->Shader, 0, 0);

	//	Send Transform to the GPU
	//		Have to do this weird way of getting the 3x3 matrix to the GPU due to how the GPU like to space memory
	Matrix2D MeshMatrix = MeshTransform.GetMatrix();
	DirectX::XMMATRIX DXTransformMatrix(
		MeshMatrix._11, MeshMatrix._12, MeshMatrix._13, 0.f, 
		MeshMatrix._21, MeshMatrix._22, MeshMatrix._23, 0.f,
		MeshMatrix._31, MeshMatrix._32, MeshMatrix._33, 0.f, 
		0.f, 0.f, 0.f, 0.f);

	D3D11_MAPPED_SUBRESOURCE GPUBuffer;
	DxDeviceContext->Map(Transform2D_CBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
	memcpy(GPUBuffer.pData, &DXTransformMatrix, sizeof(DirectX::XMMATRIX));
	DxDeviceContext->Unmap(Transform2D_CBuff, 0);

	DxDeviceContext->VSSetConstantBuffers(0, 1, &Transform2D_CBuff);

	// Pixel Shader
	DxDeviceContext->PSSetShader(Mesh->PixelShader->Shader, 0, 0);

	// Draw
	DxDeviceContext->Draw(Mesh->Verticies.size(), 0);
}

void RenderManager::DrawDebugLine(const Vector2& PointA, const Vector2& PointB, const Vector4& Color)
{
	if (DebugVertCount + 1 < MAX_LINE_VERTS)
	{
		DebugLineVerts[DebugVertCount] = DebugVertex2D(PointA, Color);
		DebugLineVerts[DebugVertCount + 1] = DebugVertex2D(PointB, Color);
		DebugVertCount += 2;
	}
}

void RenderManager::DrawDebugRectangle(const Transform2D& Transform, const Vector4& Color)
{
	const Vector2 Center = Transform.GetPosition();
	const Vector2 Extent = Transform.GetScale() * 0.5f;
	const float RectangleRotation = Transform.GetRotationAngle();

	const Vector2 PointA = Center + Extent.Rotate(RectangleRotation);
	const Vector2 PointB = Center + Vector2(Extent.X, -Extent.Y).Rotate(RectangleRotation);
	const Vector2 PointC = Center + Vector2(-Extent.X, -Extent.Y).Rotate(RectangleRotation);
	const Vector2 PointD = Center + Vector2(-Extent.X, Extent.Y).Rotate(RectangleRotation);

	DrawDebugLine(PointA, PointB, Color);
	DrawDebugLine(PointB, PointC, Color);
	DrawDebugLine(PointC, PointD, Color);
	DrawDebugLine(PointD, PointA, Color);
}

void RenderManager::RenderDebugLines()
{
	DxDeviceContext->IASetInputLayout(DebugInputLayout);

	DxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	DxDeviceContext->UpdateSubresource(DebugVertexBuffer, 0, NULL, DebugLineVerts.data(), 0, 0);

	UINT Strides[] = { sizeof(DebugVertex2D) };
	UINT Offsets[] = { 0 };
	DxDeviceContext->IASetVertexBuffers(0, 1, &DebugVertexBuffer, Strides, Offsets);

	DxDeviceContext->VSSetShader(Debug2DVertexShader, nullptr, 0);
	DxDeviceContext->PSSetShader(Debug2DPixelShader, nullptr, 0);

	DxDeviceContext->Draw((UINT)DebugVertCount, 0);

	// Clear the drawn lines
	DebugVertCount = 0;
}

void RenderManager::PresentRender()
{
	RenderDebugLines();

	// Can limit frame rate here
	DxSwapChain->Present(0, 0);
}