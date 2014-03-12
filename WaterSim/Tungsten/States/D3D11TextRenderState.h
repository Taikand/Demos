#pragma once
#include "Tungsten\States\D3D11SpriteRenderState.h"
namespace Tungsten
{

	class D3D11TextRenderState :
		protected D3D11SpriteRenderState
	{
	public:
		D3D11TextRenderState(WCHAR* vShader,WCHAR* pShader);
		~D3D11TextRenderState();
		Sprite	MakeCharSprite(Vector<2, float> cursor, float size, SpriteCharData charData);
		void	DrawString(Vector<2, float>& cursor, float size, SpriteFont font, char* string, float allign = 0.0f);
		void	DrawStringCentered(Vector<2, float> center, float size, SpriteFont font, char* string);

	};

}