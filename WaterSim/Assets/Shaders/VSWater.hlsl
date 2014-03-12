

struct Wave
{
	float2 direction;
	float phase;
	float freq;
	float amplitude;
	float3 _pad;
};

cbuffer Waves : register(b0)
{
	Wave wave1;
	Wave wave2;
	Wave wave3;
	Wave wave4;
}

cbuffer perFrame : register(b1)
{
	float4x4 viewMatrix;
	float time;
	float3 _pad;
}

struct Input
{
	float2 pos : POSITION;
	float2 uv : UV; 
};
struct Output
{
	float4 pos : SV_POSITION;
	float2 uv  : UV;
};

float waveSim(Wave currentWave, float2 pos,out float4 normal)
{
	normal = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float height;
	height = 2*currentWave.amplitude;
	height *= sin((dot(currentWave.direction, pos)*currentWave.freq + time*currentWave.phase+1)/2);
	return height;
}

Output main( Input input  ) 
{
	Output ret;
	float4 normal;
	float height = waveSim(wave1, input.pos, normal);
	height += waveSim(wave2, input.pos, normal);
	height += waveSim(wave3, input.pos, normal);
	height += waveSim(wave4, input.pos, normal);
	ret.pos = mul(viewMatrix, float4(input.pos.x,height,input.pos.y,1.0f));
	ret.uv = input.uv;

	return ret;
}