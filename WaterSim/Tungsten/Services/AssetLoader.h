#pragma once
#include "pch.h"
#include "../PlatformTools.h"
#include "IImporterService.h"


namespace Tungsten
{


class AssetLoader: public IImporterService
{
private:
	Dictionary<Texture,std::wstring> textureCache;
public:
	
	Texture LoadWICTexture(const WCHAR* path);
	Texture LoadDDSTexture(const WCHAR* path);
	SpriteFont LoadFont(const WCHAR* binaryPath,const WCHAR* texturePath);
	AssetLoader(void);
	~AssetLoader(void);
};

}