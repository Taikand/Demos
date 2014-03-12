#pragma once
#include "Texture.h"
#include "../Handle.h"

namespace Tungsten
{
	typedef unsigned int Pixels;
	struct SpriteCharData
	{
		Pixels x;
		Pixels y;
		Pixels width;
		Pixels height;
	};



	struct implSpriteFont
	{
		SpriteCharData	charData[256];
		Texture			texture;
	};


	typedef Handle<implSpriteFont> SpriteFont;
	



}
