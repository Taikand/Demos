#pragma once
#include "Services\ISpriteTextService.h"
#include "States\D3D11TextRenderState.h"

namespace Tungsten
{

	class DebugWriter :
		public ISpriteTextService,public D3D11TextRenderState
	{
	private:
		//For debug messages
		Vector<2, float> cursorPos;
		SpriteFont	debugFont;
	public:
		void Write(char* text);
		void Clear();
		DebugWriter(WCHAR* vShader,WCHAR* pShader,SpriteFont defaultFont);
		~DebugWriter();
	};

}