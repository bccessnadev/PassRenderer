struct InputVertex
{
	float4 Pos : SV_POSITION;
	float4 RGBA : COLOR;
};

float4 main(InputVertex Input) : SV_TARGET
{
	return Input.RGBA;
}