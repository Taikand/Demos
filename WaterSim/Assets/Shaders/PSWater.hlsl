struct Input
{
	float4 pos : SV_POSITION;
	float2 uv  : UV;
};

Texture2D tex : register(t0);
SamplerState sampl : register(s0);

float4 main(Input input) : SV_TARGET
{
	return tex.Sample(sampl,input.uv);
}