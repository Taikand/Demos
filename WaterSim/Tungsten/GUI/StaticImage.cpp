#include "pch.h"
#include "StaticImage.h"

using namespace Tungsten::GUI;
using namespace Tungsten;

StaticImage::StaticImage()
{
}


StaticImage::~StaticImage()
{
}

void StaticImage::Draw(D3D11SpriteRenderState* graphics)
{
	
	graphics->Draw(image, { position.x, position.y, position.x + width, position.y + height }, textureCoords,depth);
}

void StaticImage::Update(InputService* input)
{

}

void StaticImage::SetDepth(float depth)
{
	if (depth >= 1.0f) depth = 0.99f;
	if (depth <= 0.0f)	depth = 0.01f;
	this->depth = depth;
}