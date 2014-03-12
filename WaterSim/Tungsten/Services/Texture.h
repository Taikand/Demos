#pragma once
#include "../DataContainers.h"
namespace Tungsten
{
	struct TextureData
		: public Pair<ID3D11ShaderResourceView*, ID3D11Resource*>
	{
		TextureData()
		{
			tag = NULL;
			val = NULL;
		}
		~TextureData()
		{
			if (tag)
				tag->Release();
			if (val)
				val->Release();
		}
	};

	class Texture : public Handle<TextureData>
	{
	public:
		Texture();
		const Texture& operator=(Handle<TextureData>& ref);
		Texture(Handle<TextureData>& ref);

	};

	//typedef  Handle<TextureData> Texture;

	extern Texture NullTexture;

}
