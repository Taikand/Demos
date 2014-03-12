#include "pch.h"
#include "D3D11HeightMapState.h"

using namespace Tungsten;

D3D11HeightMapState::D3D11HeightMapState(const WCHAR* pShader, const WCHAR* vShader)
{
	grid = NULL;
	mapBuffer = NULL;
	indexBuffer = NULL;
	heightNormBuffer = NULL;

	MemoryBlock bytes;
	PlatformTools::CreateByteCodeFromFile(pShader, &bytes);
	device->CreatePixelShader(bytes.ptr, bytes.width, NULL, &ps);

	bytes.Release();

	PlatformTools::CreateByteCodeFromFile(vShader, &bytes);
	device->CreateVertexShader(bytes.ptr, bytes.width, NULL, &vs);

	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "MAP", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), bytes.ptr, bytes.width, &layout);
	bytes.Release();

	

}


D3D11HeightMapState::~D3D11HeightMapState()
{
}

void D3D11HeightMapState::Apply()
{
	D3D11CommonState::Apply();
	Services.Graphics()->ClearContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 1.0f;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.MaxAnisotropy = 8;
	samplerDesc.MaxLOD = 1.0f;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MipLODBias = 0.0f;
	ID3D11SamplerState* sampler;
	device->CreateSamplerState(&samplerDesc, &sampler);
	context->PSSetSamplers(0, 1, &sampler);

	context->PSSetShader(ps, NULL, NULL);
	context->VSSetShader(vs, NULL, NULL);
	context->IASetInputLayout(layout);

}

void D3D11HeightMapState::SetGrid(Vector<2,int> cellCount,Vector<2,int> textureRes,int textureStep,float heightNorm,float scaleFactor)
{
	if (mapBuffer != NULL)
		mapBuffer->Release();
	if (indexBuffer != NULL)
		indexBuffer->Release();
	if (heightNormBuffer != NULL)
		heightNormBuffer->Release();

	delete[] grid;
	grid = new HeightMapGrid(cellCount.x, cellCount.y, textureRes.x, textureRes.y, textureStep);
	
	D3D11_BUFFER_DESC buffDesc;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffDesc.CPUAccessFlags = NULL;
	buffDesc.MiscFlags = NULL;
	buffDesc.StructureByteStride = NULL;
	buffDesc.Usage = D3D11_USAGE_IMMUTABLE;
	buffDesc.ByteWidth = grid->GetGeometry().width;
	
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = grid->GetGeometry().ptr;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	device->CreateBuffer(&buffDesc, &data, &mapBuffer);


	buffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffDesc.ByteWidth = grid->GetIndex().width;
	data.pSysMem = grid->GetIndex().ptr;
	device->CreateBuffer(&buffDesc, &data, &indexBuffer);

	buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.ByteWidth = sizeof(float)*4;
	//Pad 2 floats
	float cbuffer1[4];
	cbuffer1[0] = heightNorm;
	cbuffer1[1] = scaleFactor;
	data.pSysMem = &heightNorm;
	device->CreateBuffer(&buffDesc, &data, &heightNormBuffer);



}

void D3D11HeightMapState::Draw(Camera& perspective)
{
	ID3D11Buffer* constBuffer;
	D3D11_BUFFER_DESC constBufferDesc;

	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.ByteWidth = sizeof(CameraBuffer);
	constBufferDesc.CPUAccessFlags = NULL;
	constBufferDesc.MiscFlags = NULL;
	constBufferDesc.StructureByteStride = NULL;
	constBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = perspective.GetCameraMatrix();

	device->CreateBuffer(&constBufferDesc, &data, &constBuffer);

	context->VSSetConstantBuffers(0, 1, &constBuffer);
	context->VSSetConstantBuffers(1, 1, &heightNormBuffer);

	constBufferDesc.ByteWidth = sizeof(light);
	data.pSysMem = &light;
	ID3D11Buffer* lightBuf;
	device->CreateBuffer(&constBufferDesc, &data, &lightBuf);
	context->PSSetConstantBuffers(0, 1, &lightBuf);

	context->VSSetShaderResources(0, 1, &(*map).val);
	context->PSSetShaderResources(0, 1, &(*terrain).val);
	context->IASetIndexBuffer(indexBuffer,DXGI_FORMAT_R32_UINT,0);
	UINT stride = sizeof(MapVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mapBuffer, &stride, &offset);
	

	context->DrawIndexed(grid->GetIndex().width / sizeof(UINT32),0,0);
	constBuffer->Release();
}