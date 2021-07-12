#include "../../WorldSize.h"

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
	OutputVertex Output = (OutputVertex) 0;
	Output.Pos = float4(Input.Pos.x / HalfNumXUnits, Input.Pos.y / HalfNumYUnits, 0.f, 1.0f);
	Output.RGBA = Input.RGBA;
	return Output;
}