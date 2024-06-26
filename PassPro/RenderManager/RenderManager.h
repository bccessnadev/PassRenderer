#pragma once

#include <d3d11.h>
#include <array>
#include "../Math/VectorLibrary.h"
#include "../Math/Transform.h"

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

/**
* 2D point to render on screen
*/
struct Vertex2D
{
	/** World space position of the point on the screen */
	Vector2 Position;

	/** Color of the point if not drawn as */
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

/**
* 2D point to render on screen via the debug shader
*/
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

/** Definitions of commonly used colors */
namespace Colors
{
	const Vector4 Red = Vector4(1.f, 0.f, 0.f, 1.f);
	const Vector4 Green = Vector4(0.f, 1.f, 0.f, 1.f);
	const Vector4 Blue = Vector4(0.f, 0.f, 1.f, 1.f);
	const Vector4 Cyan = Vector4(0.f, 1.f, 1.f, 1.f);
	const Vector4 Yellow = Vector4(1.f, 1.f, 0.f, 1.f);
}

/**
* Manager class for rendering needs
*/
class RenderManager
{
public:
	
	/** Getter for singleton instance. Will return null if Initialize has not been called */
	static RenderManager* Get();

	/**
	 * Initializes the RenderManager and sets up Direct3D 11 for rendering.
	 *
	 * This constructor sets up the Direct3D 11 rendering environment for the specified window.
	 * It initializes the swap chain, device, device context, render target view, viewport,
	 * shaders, input layout, vertex buffer, and constant buffer required for rendering.
	 *
	 * @param hWnd The handle to the window where the rendering will be displayed.
	 */
	static RenderManager* Initialize(HWND hWnd);

	~RenderManager();

	/** Null checks and releases ObjectToRelease */
	static void SafeRelease(IUnknown* OjbectToRelease);

	/**
	 * Prepares the rendering environment before rendering objects.
	 *
	 * This function clears the render target view to a specified color (black), sets the render target,
	 * and configures the viewport. It ensures that the frame starts with a clean slate and that rendering
	 * occurs in the correct area of the screen.
	 */
	void PreRender();

	/** Calls render functions and presents render target to the screen */
	void PresentRender();

	   /** Gets the Direct3D device.
     * 
     * The Direct3D device is used to create resources such as textures, buffers, and shaders, and to manage rendering states.
     * 
     * @return A pointer to the Direct3D device.
     */
	ID3D11Device* GetDevice() { return DxDevice; }

	 /** Gets the default 2D vertex shader.
     * 
     * The default 2D vertex shader is used to process vertices for 2D rendering.
     * 
     * @return A pointer to the default 2D vertex shader.
     */
	TVertexShader* GetDefault2DVertexShader() { return &Default2DVertexShader; };

	 /** Gets the default 2D pixel shader.
     * 
     * The default 2D pixel shader is used to process pixels for 2D rendering.
     * 
     * @return A pointer to the default 2D pixel shader.
     */
	TPixelShader* GetDefault2DPixelShader() { return &Default2DPixelShader; };

	 /** Renders a mesh with the given transform.
     * 
     * @param Mesh The mesh to render.
     * @param MeshTransform The transform to apply to the mesh.
     */
	void RenderMesh(class RMesh* Mesh, const Transform2D& MeshTransform);

	/** Draws a debug line between two points with the specified color.
	 *
	 * @param PointA The starting point of the line.
	 * @param PointB The ending point of the line.
	 * @param Color The color of the line.
	 */
	void DrawDebugLine(const Vector2& PointA, const Vector2& PointB, const Vector4& Color);

	/** Draws a debug rectangle with the specified transform and color.
	 *
	 * @param Transform The transform to apply to the rectangle.
	 * @param Color The color of the rectangle.
	 */
	void DrawDebugRectangle(const Transform2D& Transform, const Vector4& Color);
	
protected:

	// For init
	/** A pointer to the Direct3D device. */
	ID3D11Device* DxDevice = nullptr;

	/** A pointer to the swap chain.
	 *
	 * The swap chain manages the buffers used for displaying frames to the screen.
	 */
	IDXGISwapChain* DxSwapChain = nullptr;

	// For drawing
	/** A pointer to the Direct3D device context.
	 *
	 * The device context is used to issue rendering commands to the GPU, handle drawing operations, state changes, and resource bindings.
	 */
	ID3D11DeviceContext* DxDeviceContext = nullptr;

	 /** A pointer to the render target view.
     * 
     * The render target view allows a render target to be used as a rendering destination.
     */
	ID3D11RenderTargetView* DxRenderTargetView = nullptr;

	/** The viewport used for rendering.
	 *
	 * The viewport defines the portion of the render target where rendering will occur.
	 */
	D3D11_VIEWPORT DxViewport = D3D11_VIEWPORT();

	/** The default vertex shader for 2D rendering. */
	TVertexShader Default2DVertexShader;

	/** The default pixel shader for 2D rendering. */
	TPixelShader Default2DPixelShader;

	/** Constant buffer that holds the 2D transform matrix for the current shape being drawn. */
	ID3D11Buffer* Transform2D_CBuff = nullptr;

	// Debug Rendering
	/** A pointer to the input layout for debug rendering. */
	ID3D11InputLayout* DebugInputLayout = nullptr;

	/** A pointer to the vertex shader for debug rendering. */
	ID3D11VertexShader* Debug2DVertexShader = nullptr;

	/** A pointer to the pixel shader for debug rendering. */
	ID3D11PixelShader* Debug2DPixelShader = nullptr;

	/** A pointer to the vertex buffer for debug rendering. */
	ID3D11Buffer* DebugVertexBuffer = nullptr;

	/** The maximum number of vertices for debug lines. */
	static const size_t MAX_LINE_VERTS = 1000;

	/** The current count of debug vertices. */
	size_t DebugVertCount = 0;

	/** An array of debug vertices for drawing lines. */
	std::array<DebugVertex2D, MAX_LINE_VERTS> DebugLineVerts;

	/** Renders the debug lines. */
	void RenderDebugLines();

private:
	/** Private default constructor due to class being singleton. */
	RenderManager() {};

	/** Private initialization constructor due to class being singleton. Called by Initialize function
	 *
	 * @param hWnd The handle to the window where the rendering will be displayed.
	 */
	RenderManager(HWND);

	/** Singleton instance of this class. */
	static RenderManager* Instance;
};