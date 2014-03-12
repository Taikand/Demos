#include "pch.h"
#include "SpriteBatch.h"

namespace Tungsten
{


SpriteBatch::SpriteBatch(void)
{
}


SpriteBatch::~SpriteBatch(void)
{
	data.Clear();
}



void SpriteBatch::Draw(Texture texture, Sprite& sprite)
{
	auto batch = data.Seek(texture);
	if (!batch)
	{
		data.Register(DynamicArray<Sprite>(), texture);
		batch = data.Seek(texture);
	}
	batch->PushBack(sprite);
}
void SpriteBatch::Draw(
	Texture texture,
	Rectangle positionUV,
	Rectangle texUV,
	float depth,
	Vector<4> tint
	)
{
	Draw(texture, MakeSprite(positionUV, texUV, depth, tint));

}

void SpriteBatch::Draw(Texture texture,
	Vector<2> upperLeft, Vector<2> lowerRight,
	Vector<2> upperLeftTexture, Vector<2> lowerRightTexture,
	float depth,
	Vector<4> tint
	)
{
	Draw(texture, MakeSprite({ upperLeft, lowerRight }, { upperLeftTexture, lowerRightTexture }, depth, tint));
}

Sprite SpriteBatch::MakeSprite(Rectangle positionUV, Rectangle texUV,
	float depth,
	Vector<4> tint)
{
	Sprite ret = Sprite({ positionUV.x, positionUV.y }, { positionUV.z, positionUV.w }, depth, tint);
	ret.SetTextureCoords({ texUV.x, texUV.y }, { texUV.z, texUV.w });
	return ret;
}

void SpriteBatch::Draw(
	Texture texture,
	PRectangle position,

	PRectangle texPixels,
	float depth,
	Vector<4> tint
	)
{

	Rectangle pos = px(position);
	if (position.z == -1) pos.z = 1.0f;
	if (position.w == -1) pos.w = 1.0f;
	Rectangle tex = pxrel(texture, texPixels);


	Draw(texture, MakeSprite(pos, tex, depth, tint));


}

void SpriteBatch::Draw(Texture texture, DynamicArray<Sprite>* vec)
{
	for (UINT i = 0; i < vec->GetSize(); i++)
	{
		this->Draw(texture, (*vec)[i]);
	}
}

}