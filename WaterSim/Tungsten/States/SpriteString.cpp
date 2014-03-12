#include "pch.h"
#include "SpriteString.h"

using namespace Tungsten;

SpriteString::SpriteString(SpriteFont font)
:font(font)
{
}

SpriteString::SpriteString(SpriteFont font,const char* str)
: font(font)
{
	operator=(str);
}

const SpriteString& SpriteString::operator=(const char* str)
{
	this->Clear();
	PPoint activeCursor = cursor;
	text = str;
	while (*str != 0)
	{
		if (*str != '\n')
		{
			SpriteCharData ch = font->charData[(short)*str];
			PRectangle tex = { ch.x, ch.y, ch.x + ch.width, ch.y + ch.height };
			PRectangle pos = { activeCursor, { activeCursor.x + Pixels(((float)size / ch.height)*ch.width), activeCursor.y + size } };
			activeCursor.x += pos.lowerRight.x - pos.upperLeft.x;
			this->PushBack(SpriteBatch::MakeSprite(px(pos),pxrel(font->texture,tex),depth,color));
			if (activeCursor.x > bounds.x) bounds.x = activeCursor.x;
		}
		else
		{
			activeCursor.x = activeCursor.x;
			activeCursor.y += size;
		}
		str++;
		
		
	}
	bounds.y = activeCursor.y + size;
	return *this;
}

void SpriteString::SetSize(Pixels size)
{
	this->size = size;
	operator=(text.c_str());
}

void SpriteString::SetCursor(PPoint cursor)
{
	this->cursor = cursor;
	operator=(text.c_str());
}

void SpriteString::SetColor(Color color)
{
	this->color = color;
	operator=(text.c_str());
}

void SpriteString::SetDepth(float depth)
{
	this->depth = depth;
	operator=(text.c_str());
}

void SpriteString::Draw(SpriteBatch* graphics)
{
	graphics->Draw(font->texture, this);
}

PPoint SpriteString::GetBounds()
{
	return bounds;
}


SpriteString::~SpriteString()
{
}
