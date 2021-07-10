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

OutputVertex main(InputVertex Input)
{
	OutputVertex Output = (OutputVertex)0;
	Output.Pos = float4(Input.Pos.x, Input.Pos.y, 0.f, 1.0f);
	Output.RGBA = Input.RGBA;
	return Output;
}