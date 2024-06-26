#pragma once
#include <vector>
#include "RenderManager.h"

/**
 * @brief The RMesh class represents a 2D mesh used for rendering.
 *
 * This class provides functionality to create and manage 2D meshes, including their vertices,
 * vertex buffer, input layout, and associated shaders. It also includes static methods to create
 * common shapes such as triangles and squares.
 */
class RMesh
{
	friend class RenderManager;

public:
	RMesh();

	 /** 
     * Constructs a mesh with the specified vertices and optional shaders.
     * 
     * @param MeshVerticies A vector of vertices defining the mesh.
     * @param MeshVertexShader A pointer to the vertex shader to use with the mesh (optional).
     * @param MeshPixelShader A pointer to the pixel shader to use with the mesh (optional).
     */
	RMesh(const std::vector<Vertex2D>& MeshVerticies, TVertexShader* MeshVertexShader = 0, TPixelShader* MeshPixelShader = 0);

	~RMesh();

	/**
	 * Creates a triangle mesh.
	 *
	 * @param Point1 The first point of the triangle.
	 * @param Point2 The second point of the triangle.
	 * @param Point3 The third point of the triangle.
	 * @param Color The color of the triangle.
	 * @return A pointer to the created triangle mesh.
	 */
	static RMesh* Triangle(const Vector2 Point1, const Vector2 Point2, const Vector2 Point3, const Vector4 Color);

	/**
	 * Creates a square mesh.
	 *
	 * @param Size The size of the square.
	 * @param Color The color of the square.
	 * @return A pointer to the created square mesh.
	 */
	static RMesh* Square(const Vector2 Size, const Vector4 Color);

protected:

	/** Constructs the input layout for 2D rendering */
	void Construct2DInputLayout();

	/** Constructs the vertex buffer for the mesh */
	void ConstructVertexBuffer();

	/** A pointer to the render manager. */
	RenderManager* Renderer = nullptr;

	/** A vector of vertices defining the mesh. */
	std::vector<Vertex2D> Verticies;
	
	/** A pointer to the vertex buffer. */
	ID3D11Buffer* VertexBuffer = nullptr;

	/** A pointer to the input layout. */
	ID3D11InputLayout* InputLayout = nullptr;

	/** A pointer to the vertex shader. */
	TVertexShader* VertexShader = nullptr;

	/** A pointer to the pixel shader. */
	TPixelShader* PixelShader = nullptr;
};