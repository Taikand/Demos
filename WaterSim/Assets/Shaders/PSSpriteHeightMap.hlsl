struct INPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXTURE;
};
Texture2D tex : register(t0);
SamplerState sampl : register(s0);

float4 main(INPUT input) : SV_TARGET
{
	float4 ret=tex.Sample(sampl,input.texCoord);
	clip(ret.a-0.98);
	return ret;
}