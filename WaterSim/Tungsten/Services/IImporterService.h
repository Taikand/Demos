#pragma once
#include "pch.h"
#include "../DataContainers.h"
#include "Texture.h"
#include "SpriteFont.h"
namespace Tungsten
{
	



	class IImporterService
	{
	public:
		virtual Texture		LoadWICTexture(const WCHAR* path)=0;
		virtual Texture		LoadDDSTexture(const WCHAR* path)=0;
		virtual SpriteFont	LoadFont(const WCHAR* binaryPath,const WCHAR* texturePath)=0;
	};


}