#include "pch.h"
#include "WaterPhysics.h"
#include "Tungsten\PlatformTools.h"


using namespace Tungsten;
using namespace Tungsten::PlatformTools;

WaterPhysics::WaterPhysics(WCHAR* pShader, WCHAR* vShader)
{
	camera = new Camera();
	MemoryBlock blob;
	CreateByteCodeFromFile(pShader, &blob);
	device->CreatePixelShader(blob.ptr, blob.width, NULL, &ps);
	CreateByteCodeFromFile(vShader, &blob);
	device->CreateVertexShader(blob.ptr, blob.width, NULL, &vs);

	D3D11_INPUT_ELEMENT_DESC iaDesc[]=
	{
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,NULL},
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, NULL }
	};
	device->CreateInputLayout(iaDesc, 2, blob.ptr, blob.width, &ia);

	animationTimer.Start();

	waterTex = Services.Import()->LoadWICTexture(L"Assets\\water.jpg");

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.MaxAnisotropy = 10;
	samplerDesc.MaxLOD = 10;
	samplerDesc.MinLOD = 0;
	samplerDesc.MipLODBias = 0;

	device->CreateSamplerState(&samplerDesc, &ss);

	
}


WaterPhysics::~WaterPhysics()
{
	ps->Release();
	vs->Release();
	ia->Release();
	ss->Release();
	delete camera;
}

void WaterPhysics::Apply()
{
	Services.Graphics()->ClearContext();
	this->D3D11CommonState::Apply();
	context->VSSetShader(vs, NULL, NULL);
	context->PSSetShader(ps, NULL, NULL);
	context->IASetInputLayout(ia);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	context->PSSetSamplers(0, 1, &ss);
	
	


	
}

void WaterPhysics::InitGrid(int width, int height, int cellsPerUnit)
{
	
	
	if (grid.index != NULL)
	{
		delete[] grid.index;
		buffers.index->Release();
	}
	if (grid.vertex != NULL)
	{
		delete[] grid.vertex;
		buffers.vertex->Release();
	}
	int cellCount = (width*cellsPerUnit + 1);
	cellCount *= (height* cellsPerUnit + 1);
	grid.vertex = new Vertex[cellCount];
	width *= cellsPerUnit;
	height *= cellsPerUnit;

	for (int y = 0; y <= height; y++)
	{
		Vertex* cursor = grid.vertex + y*(width + 1);
		for (int x = 0; x <= width; x++)
		{
			cursor[x].x = float(x) / cellsPerUnit;
			cursor[x].y = float(y) / cellsPerUnit;
			cursor[x].u = float(x )/cellsPerUnit;
			cursor[x].v = float(y )/cellsPerUnit;
		}
	}

	int indexWidth = (width+1)* 2 + 1;
	int indexCount = indexWidth*height;
	
	//Arcane arts inside

	grid.index = new UINT[indexCount];
	for (int y = 0; y < height; y++)
	{
		UINT* cursor = grid.index + indexWidth*y;
		if ((y % 2))
		{
			for (int x = 0; x <indexWidth-1; x += 2)
			{
				cursor[x] = (width+1)*y + width-x/2;
				cursor[x + 1] = cursor[x] + width+1;
			}
			//Glue
			cursor[indexWidth - 1] = cursor[indexWidth - 2];
		}
		else
		{
			for (int x = 0; x <indexWidth - 1; x += 2)
			{
				cursor[x] = (width+1)*y + x/2;
				cursor[x + 1] = cursor[x] + width+1;
			}
			//Glue
			cursor[indexWidth - 1] = cursor[indexWidth - 2];
		}
		
	}


	CreateBuffers(  {(void*)grid.vertex, cellCount*sizeof(Vertex) }, { grid.index, indexCount*sizeof(UINT) }, &buffers.vertex, &buffers.index);
}
void WaterPhysics::Draw()
{

	animationTimer.Tick();
	perFrame buffer;
	buffer.viewMatrix = *camera->GetCameraMatrix();
	buffer.time = (float)animationTimer.GetTotalFloat();
	MemoryBlock blob;
	blob.ptr = &buffer;
	blob.width = sizeof(perFrame);
	VSSetConstantBuffer(blob, 1);
	VSSetConstantBuffer(&wavebuffer, 0);
	PSSetShaderResource(waterTex->elem1, 0);


	UINT offset = 0;
	UINT strides = sizeof(Vertex);
	context->IASetVertexBuffers(0, 1, &buffers.vertex, &strides, &offset);
	context->IASetIndexBuffer(buffers.index, DXGI_FORMAT_R32_UINT, 0);
	D3D11_BUFFER_DESC desc;
	buffers.index->GetDesc(&desc);
	context->DrawIndexed(desc.ByteWidth/sizeof(UINT),0,0);
	
}

void WaterPhysics::SetWave(Wave& arg, int index)
{
	normalize(arg.direction);
	wavebuffer[index] = arg;
}