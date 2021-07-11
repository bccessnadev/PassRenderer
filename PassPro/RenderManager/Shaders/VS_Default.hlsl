/* 
Rule of three
Three things must match:
	1. C++ Vertex Struct
	2. Input Layout
	3. HLSL Vertex Struct
*/

struct InputVertex
{
	float2 Pos : POSITION;
	float4 RGBA : COLOR;
};

struct OutputVertex
{
	float4 Pos : SV_POSITION;
	float4 RGBA : COLOR;
};

cbuffer WVP : register(b0)
{
	float4x4 GPUTransform;
}

OutputVertex main(InputVertex Input)
{
	OutputVertex Output = (OutputVertex)0;
	float3x3 Transform =
	float3x3(
	GPUTransform._11, GPUTransform._21, GPUTransform._31,
	GPUTransform._12, GPUTransform._22, GPUTransform._32,
	GPUTransform._13, GPUTransform._23, GPUTransform._33
	);
	float2 WorldPos = mul(Transform, float3(Input.Pos, 1));
	Output.Pos = float4(WorldPos, 0.f, 1.f);
	Output.RGBA = Input.RGBA;
	return Output;
}