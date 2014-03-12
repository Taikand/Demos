struct INPUT
{
	//vertex postion to compose a Quad 
	float2 position : POSITION;
	float2 texCoord	: TEXTURE;
	//x,z coordinates for every instance
	float2 i_pos	: IPOSITION;
};
struct OUTPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXTURE;
};

cbuffer PerFrame : register(b0)
{
	float4x4	viewMatrix;
	float4x4	cameraRotation;
	float2		cameraOrientation;
}
cbuffer Sampler : register(b1)
{
	float2	texelSize;
	float	heightNorm;
}


Texture2D<float> heightmap	: register(t0);

float BilinearFiltering(float2 sampleCoord)
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
	
	t[0]=lerp(t[0],t[1],sampleCoord.x-topleft.x);
	t[1]=lerp(t[2],t[3],sampleCoord.x-topleft.x);
	t[0]=lerp(t[0],t[1],sampleCoord.y-topleft.y);
	return t[0];
}

OUTPUT main( INPUT input ) 
{
	OUTPUT output;
	output.position.xy=input.position.xy;

	//output.position.y=40*heightmap.Load(int3(input.heightCoord,0.0f));
	output.position.z=0.0f;
	output.position.w=1.0f;
	output.position=mul(cameraRotation,output.position);
	output.position.xz+=input.i_pos.xy;
	output.position.y+=1*(BilinearFiltering(output.position.xz) );
	//output.texCoord=float2(output.position.y/40,output.position.y/40);
	output.texCoord=input.texCoord;
	
	output.position=mul(viewMatrix,output.position);
	
	return output;
}