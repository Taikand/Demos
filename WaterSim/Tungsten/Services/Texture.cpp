#include "pch.h"
#include "Texture.h"

using namespace Tungsten;

Texture::Texture()
{
	if (NullTexture.data)
	{
		this->Handle<TextureData>::operator=(NullTexture);
	}
	
}

Texture::Texture(Handle<TextureData>& ref)
{
	this->Handle<TextureData>::operator=(ref);
}

const Texture& Texture::operator=(Handle<TextureData>& ref)
{
	this->Handle<TextureData>::operator=(ref);
	return *this;
}