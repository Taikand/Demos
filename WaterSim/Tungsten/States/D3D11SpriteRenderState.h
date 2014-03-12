#pragma once
#include "pch.h"
#include "D3D11CommonState.h"
#include "SpriteBatch.h"

namespace Tungsten
{

class D3D11SpriteRenderState :
	public D3D11CommonState,
	public SpriteBatch
{
public:
	D3D11SpriteRenderState(const WCHAR* psPath,const WCHAR* vShader);
	void Begin();
	void End();
	void Apply();
	
	~D3D11SpriteRenderState(void);

	

private:
	UINT* CreateIndexes(UINT spriteCount);
	const int vertexStride;
	
	D3D11_BUFFER_DESC vbDesc;
	D3D11_BUFFER_DESC ibDesc;
	
	ID3D11InputLayout* layout;
	ID3D11PixelShader* ps;
	ID3D11VertexShader* vs;


};




}
