#pragma once
#include "pch.h"

#include "Sprite.h"
#include "..\DataContainers.h"
#include "..\ServiceLocator.h"


namespace Tungsten
{

	
	
	inline Rectangle pxrel(Texture tex, PRectangle val)
	{
		D3D11_TEXTURE2D_DESC desc;
		((ID3D11Texture2D*)(tex->elem2))->GetDesc(&desc);
		Rectangle ret;
		ret.x = val.x / (float)desc.Width;
		ret.y = val.y / (float)desc.Height;
		ret.z = val.z / (float)desc.Width;
		ret.w = val.w / (float)desc.Height;
		if (val.z == -1) ret.z = 1.0f;
		if (val.w == -1) ret.w = 1.0f;
		return ret;
	
	}

class SpriteBatch
{
protected:
	Dictionary<DynamicArray<Sprite>,Texture> data;

public:
	

	void		Draw		(Texture texture,Sprite& sprite);
	void		Draw		(
							Texture texture,
							Vector<2> upperLeftUV,			Vector<2> lowerRightUV,
							Vector<2> upperLeftTextureUV = { 0.0f, 0.0f },
							Vector<2> lowerRightTextureUV = { 1.0f, 1.0f },
							float depth = 0.5f,
							Vector<4> tint = { 1.0f, 1.0f, 1.0f, 1.0f }
							);
	void		Draw		(
							Texture texture,
							Rectangle positionUV, Rectangle texUV,
							float depth = 0.5f,
							Vector<4> tint = Vector<4>(1.0f, 1.0f, 1.0f, 1.0f)
							
							);
	static
	Sprite		MakeSprite	(
							Rectangle positionUV,
							Rectangle texUV = { 0.0f, 0.0f, 1.0f, 1.0f },
							float depth = 0.5f,
							Vector<4> tint = Vector<4>(1.0f, 1.0f, 1.0f, 1.0f)
							);
	void		Draw		(
							Texture texture,
							PRectangle position,
							//Default value leads to {0,0,1,1} rectangle
							PRectangle texPixels = { 0U, 0U, 0U-1, 0U-1 },
							float depth = 0.5f,
							Vector<4> tint = Vector<4>(1.0f, 1.0f, 1.0f, 1.0f)
							);
	void		Draw		(Texture texture, DynamicArray<Sprite>* vec);
	
	SpriteBatch(void);
	~SpriteBatch(void);
};

}