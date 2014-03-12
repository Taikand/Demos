Texture2D spriteTex : register(t0); 
SamplerState sample	: register(s0);

static const float alphaTolerance = 0.05f;

struct INPUT
{
	float4 pos : SV_POSITION ;
	float2 texcoord : TEXTURE ;
	float4 tint : TINT;
};

float4 main(INPUT input) : SV_TARGET
{

	/*spriteTex.GetDimensions(0,width,height,levels);
	float4 color=spriteTex.Sample(sample,float2(input.texcoord.x/width,input.texcoord.y/height));*/
	float4 color = spriteTex.Sample(sample, input.texcoord);
	clip(color.a - alphaTolerance);
	color=color*input.tint;
	return color;
}