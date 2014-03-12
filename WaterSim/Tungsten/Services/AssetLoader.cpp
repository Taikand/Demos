#include "pch.h"
#include "AssetLoader.h"
#include "D3DRenderer.h"
#include "DirectXTK\DDSTextureLoader.h"


using namespace Tungsten;

Texture Tungsten::NullTexture;

AssetLoader::AssetLoader(void)
{
	// #! Hardcoded
	NullTexture = LoadWICTexture(L"Assets\\null.png");

}


AssetLoader::~AssetLoader(void)
{
}

Texture AssetLoader::LoadWICTexture(const WCHAR* path)
{
	Texture* p=textureCache.Seek(path);
	Handle<TextureData> ret;
	if(!p)
	{

		TextureData* pair=new TextureData();
		pair->tag = NULL;
		pair->val = NULL;
		DirectX::CreateWICTextureFromFile(
			((D3DRenderer*)Services.Graphics())->GetDevice(),
			((D3DRenderer*)Services.Graphics())->GetContext(),
			path,&pair->tag,
			&pair->val);
		
		if (pair->tag == NULL)
		{
			ret = NullTexture;
		}
		else
		{
			ret = Handle<TextureData>(pair);
		}
		
		textureCache.Register(ret,path);
	
		
	}
	else
	{
		ret=*p;

	}
	return ret;
}

Texture AssetLoader::LoadDDSTexture(const WCHAR* path)
{
	Texture* p=textureCache.Seek(path);
	Handle<TextureData> ret;
	if(!p)
	{

		TextureData* pair=new TextureData();
		
		DirectX::CreateDDSTextureFromFile(((D3DRenderer*)Services.Graphics())->GetDevice(),path,&pair->tag,&pair->val);
	
		ret=Handle<TextureData>(pair);
		textureCache.Register(ret,path);
	
		
	}
	else
	{
		ret=*p;

	}
	return ret;
}

SpriteFont AssetLoader::LoadFont(const WCHAR* binaryPath,const WCHAR* texturePath)
{

	SpriteFont font(new implSpriteFont());



	HANDLE handle=PlatformTools::CreateFileHandle(binaryPath,PlatformTools::FileAccess::Read);

	ReadFile(handle,font->charData,sizeof(SpriteCharData)*256,NULL,NULL);
	CloseHandle(handle);
	
	font->texture=LoadWICTexture(texturePath);
	return font;
}