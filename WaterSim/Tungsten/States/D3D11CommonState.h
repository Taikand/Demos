#pragma once
#include "pch.h"
#include "..\ServiceLocator.h"
#include "..\Services\D3DRenderer.h"

namespace Tungsten
{

class D3D11CommonState
{
public:
	
	virtual void Apply();
	
protected:
	D3D11CommonState();
	static ID3D11Device*		device;
	static ID3D11DeviceContext* context;
	

//Commonly used functions
	void		CreateBuffers(MemoryBlock vertexData,MemoryBlock indexData,ID3D11Buffer** vBuffer,ID3D11Buffer** iBuffer);
	void		PSSetShaderResource(ID3D11ShaderResourceView* shaderView,	int index);
	void		VSSetShaderResource(ID3D11ShaderResourceView* shaderView,	int index);
	void		VSSetConstantBuffer(MemoryBlock buffer,						int index);
	void		PSSetConstantBuffer(MemoryBlock buffer,						int index);
	
	//void		DrawInstanced(MemoryBlock vertexData,MemoryBlock indexData,MemoryBlock instanceData);
};



}