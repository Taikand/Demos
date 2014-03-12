struct INPUT
{
	float2 mapCoord		: MAP;
	float2 position		: POSITION;
	float2 texCoord		: TEXTURE;
};
struct OUTPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXTURE;
	float3 normal	: NORMAL;
};

cbuffer PerFrame : register(b0)
{
	float4x4 viewMatrix;
}
cbuffer Sampler : register(b1)
{
	float	heightNorm;
	float	scaleFactor;
}

Texture2D<float> heightmap	: register(t0);

float3 CalculateNormal(float4 heights)
{
	float3 normX;
	float3 normY;

	normX.y = heights[0] - heights[1];
	normX.y *= heightNorm;
	normX.x = scaleFactor;
	normX.z = 0;
	normX = normalize(normX);
	

	normY.y = heights[0] - heights[2];
	normY.y *= heightNorm;
	normY.z = -scaleFactor;
	normY.x = 0;
	normY = normalize(normY);
	

	return cross(normX, normY);
	
}

float BilinearFiltering(float2 sampleCoord,out float3 normal)
{
	int2 topleft;
	topleft.x=floor(sampleCoord.x);
	topleft.y=floor(sampleCoord.y);
	float4 t;
	/*	x--->
		0---1 y
		|	| ||
		2---3 \/
	*/
	
	t[0]=heightmap.Load(int3(topleft,0.0f));
	t[1]=heightmap.Load(int3(topleft.x+1,topleft.y,0.0f));
	t[2]=heightmap.Load(int3(topleft.x,topleft.y+1,0.0f));
	t[3]=heightmap.Load(int3(topleft.x+1,topleft.y+1,0.0f));

	normal = CalculateNormal(t);
	
	t[0]=lerp(t[0],t[1],sampleCoord.x-topleft.x);
	t[1]=lerp(t[2],t[3],sampleCoord.x-topleft.x);
	t[0]=lerp(t[0],t[1],sampleCoord.y-topleft.y);
	return t[0]-0.25; //BaseHeight 0.25
}

OUTPUT main( INPUT input ) 
{
	OUTPUT output;
	output.position.xz=input.position.xy*scaleFactor;
	//output.position.y=40*heightmap.Load(int3(input.mapCoord,0.0f));
	output.position.y=heightNorm*BilinearFiltering(input.mapCoord,output.normal);
	output.texCoord=float2(output.position.y/40,output.position.y/40);
	output.texCoord=input.texCoord;
	output.position.w=1.0f;
	output.position=mul(viewMatrix,output.position);
	
	return output;
}