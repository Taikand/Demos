#include "pch.h"
#include "D3D11SpriteRenderState.h"

using namespace Tungsten;



D3D11SpriteRenderState::D3D11SpriteRenderState(const WCHAR* pShader,const WCHAR* vShader)
	:vertexStride(sizeof(SpriteVertex))
{
	MemoryBlock bytes;
	PlatformTools::CreateByteCodeFromFile(pShader,&bytes);
	device->CreatePixelShader(bytes.ptr,bytes.width,NULL,&ps);

	bytes.Release();

	PlatformTools::CreateByteCodeFromFile(vShader,&bytes);
	device->CreateVertexShader(bytes.ptr,bytes.width,NULL,&vs);

	D3D11_INPUT_ELEMENT_DESC inputDesc[]=
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXTURE",	0,DXGI_FORMAT_R32G32_FLOAT		,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},			
		{"TINT",	0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	device->CreateInputLayout(inputDesc,ARRAYSIZE(inputDesc),bytes.ptr,bytes.width,&layout);
	bytes.Release();

	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbDesc.MiscFlags = NULL;
	vbDesc.StructureByteStride = NULL;
	vbDesc.Usage = D3D11_USAGE_DYNAMIC;
	
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	
	ibDesc.CPUAccessFlags = NULL;
	ibDesc.MiscFlags = NULL;
	ibDesc.StructureByteStride = NULL;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;

}


D3D11SpriteRenderState::~D3D11SpriteRenderState(void)
{
	
}

void D3D11SpriteRenderState::Begin()
{
	for (unsigned int i = 0; i < data.GetSize(); i++)
	{
		data.Clear();
	}
}

void D3D11SpriteRenderState::End()
{
	unsigned int maxSize = 0;

	for (unsigned int i = 0; i < data.GetSize(); i++)
	{
		if (maxSize<data[i].val.GetSize())
			maxSize = data[i].val.GetSize();
	}
	
	
	D3D11_SUBRESOURCE_DATA bufferData;

	ibDesc.ByteWidth = maxSize * 6*sizeof(UINT);
	UINT* indexData = CreateIndexes(maxSize);
	bufferData.pSysMem = indexData;
	bufferData.SysMemPitch = NULL;
	bufferData.SysMemSlicePitch = NULL;
	ID3D11Buffer* indexBuffer;
	device->CreateBuffer(&ibDesc, &bufferData, &indexBuffer);
	DXGI_FORMAT format=DXGI_FORMAT_R32_UINT;
	UINT offset = 0;
	context->IASetIndexBuffer(indexBuffer, format, offset);

	vbDesc.ByteWidth = maxSize*sizeof(Sprite);
	ID3D11Buffer* vertexBuffer;
	UINT stride = sizeof(SpriteVertex);
	device->CreateBuffer(&vbDesc, NULL, &vertexBuffer);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	for (unsigned int i = 0; i < data.GetSize(); i++)
	{
		context->PSSetShaderResources(0, 1,& (data[i].tag)->val );
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		ZeroMemory(&mappedSubResource,sizeof(D3D11_MAPPED_SUBRESOURCE));

		context->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubResource);
		memcpy(mappedSubResource.pData, data[i].val.GetPtr(), data[i].val.GetByteWidth());
		context->Unmap(vertexBuffer, 0);

		context->DrawIndexed(6 * data[i].val.GetSize(), 0, 0);
		
	}
	vertexBuffer->Release();
	indexBuffer->Release();
	delete[] indexData;

}



void D3D11SpriteRenderState::Apply()
{
	D3D11CommonState::Apply();
	Services.Graphics()->ClearContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(layout);

	context->PSSetShader(ps,NULL,NULL);
	context->VSSetShader(vs,NULL,NULL);

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 1.0f;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.MaxLOD = 1.0f;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MipLODBias = 0.0f;
	ID3D11SamplerState* sampler;
	device->CreateSamplerState(&samplerDesc, &sampler);
	context->PSSetSamplers(0,1,&sampler);
}

UINT* D3D11SpriteRenderState::CreateIndexes(UINT spriteCount)
{
	int indexCount = spriteCount * 6;
	UINT* p = new UINT[indexCount];
	for (unsigned int i = 0; i < spriteCount; i++)
	{
		UINT* current=p + i * 6;
		current[0] = i * 4 + 0;
		current[1] = i * 4 + 1;
		current[2] = i * 4 + 2;
		current[3] = i * 4 + 2;
		current[4] = i * 4 + 1;
		current[5] = i * 4 + 3;
	}
	return p;
}