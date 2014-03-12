struct INPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXTURE;
	float4 normal	: NORMAL;
};
Texture2D tex : register(t0);
SamplerState sampl : register(s0);

cbuffer Light : register(b0)
{
	
	float4 lightDir;
	float4 ambientLight;
	float4 diffuseLight;
	float4 specularLight;
	
}
float4 ParallelPhongLight(float4 sampledColour,float3 normal)
{
	sampledColour *= ambientLight*ambientLight.a;
	float diffuse = dot(-lightDir, normal);
	if (diffuse > 0)
	{
		sampledColour += diffuse*diffuseLight;
	}
	return sampledColour;
	
}

float4 main(INPUT input) : SV_TARGET
{
	//return float4(input.texCoord,0.0f,1.0f);
	return ParallelPhongLight(tex.Sample(sampl,input.texCoord),input.normal);
}