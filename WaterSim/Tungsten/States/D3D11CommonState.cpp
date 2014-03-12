#pragma once
#include "pch.h"
#include "D3D11CommonState.h"
#include "Tungsten\PlatformTools.h"
using namespace Tungsten;

ID3D11Device*			D3D11CommonState::device=0;
ID3D11DeviceContext*	D3D11CommonState::context=0;

D3D11CommonState::D3D11CommonState()
{
	if(!device) device=((D3DRenderer*)Services.Graphics())->GetDevice();
	if(!context) context=((D3DRenderer*)Services.Graphics())->GetContext();

}

void D3D11CommonState::VSSetConstantBuffer(MemoryBlock buffer,int index)
{
	D3D11_BUFFER_DESC  bufferDesc;
	bufferDesc.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth=buffer.width;
	bufferDesc.CPUAccessFlags=NULL;
	bufferDesc.MiscFlags=NULL;
	bufferDesc.StructureByteStride=NULL;
	bufferDesc.Usage=D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA bufferData;
	bufferData.pSysMem=buffer.ptr;
	bufferData.SysMemPitch=0;
	bufferData.SysMemSlicePitch=0;

	ID3D11Buffer* constantBuffer;
	device->CreateBuffer(&bufferDesc,&bufferData,&constantBuffer);
	context->VSSetConstantBuffers(index,1,&constantBuffer);
	constantBuffer->Release();
}

void D3D11CommonState::PSSetConstantBuffer(MemoryBlock buffer,int index)
{
	D3D11_BUFFER_DESC  bufferDesc;
	bufferDesc.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
	//Must be multiple of 16 bytes
	bufferDesc.ByteWidth=buffer.width;

	bufferDesc.CPUAccessFlags=NULL;
	bufferDesc.MiscFlags=NULL;
	bufferDesc.StructureByteStride=NULL;
	bufferDesc.Usage=D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA bufferData;
	bufferData.pSysMem=buffer.ptr;
	bufferData.SysMemPitch=0;
	bufferData.SysMemSlicePitch=0;

	ID3D11Buffer* constantBuffer;
	device->CreateBuffer(&bufferDesc,&bufferData,&constantBuffer);
	context->PSSetConstantBuffers(index,1,&constantBuffer);
	constantBuffer->Release();
}

void D3D11CommonState::PSSetShaderResource(ID3D11ShaderResourceView* shaderView,int index)
{
	
	context->PSSetShaderResources(index,1,& shaderView );
}

void D3D11CommonState::VSSetShaderResource(ID3D11ShaderResourceView* shaderView,int index)
{
	
	context->VSSetShaderResources(index,1,&shaderView);
}

void D3D11CommonState::CreateBuffers(MemoryBlock vertexData, MemoryBlock indexData,ID3D11Buffer** vBuffer,ID3D11Buffer** iBuffer)
{
	D3D11_BUFFER_DESC vbDesc;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.ByteWidth = vertexData.width;
	vbDesc.CPUAccessFlags = NULL;
	vbDesc.MiscFlags = NULL;
	vbDesc.StructureByteStride = NULL;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertexData.ptr;
	data.SysMemPitch = NULL;
	data.SysMemSlicePitch = NULL;
	
	device->CreateBuffer(&vbDesc, &data, vBuffer);


	D3D11_BUFFER_DESC ibDesc;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.ByteWidth = indexData.width;
	ibDesc.CPUAccessFlags = NULL;
	ibDesc.MiscFlags = NULL;
	ibDesc.StructureByteStride = NULL;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	data.pSysMem = indexData.ptr;
	
	device->CreateBuffer(&ibDesc, &data, iBuffer);

	
	



}

void D3D11CommonState::Apply()
{
	Services.Graphics()->currentState = this;
}