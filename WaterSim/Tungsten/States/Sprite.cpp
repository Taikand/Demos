#include "pch.h"
#include "Sprite.h"
using namespace Tungsten;

Sprite::Sprite()
{

}

Sprite::Sprite(Vector<2,float> topLeft,Vector<2,float> bottomRight,float depth,Vector<4,float> tint)
{
	//Normalise in the 0-1 interval
	//depth=depth/100;
	/*
	0---1
	| @ |
	2---3
	*/
	vertices[0].pos=(Vector<4,float>(XTr(topLeft.x),YTr(topLeft.y)			,depth,1.0f));
	vertices[1].pos=(Vector<4,float>(XTr(bottomRight.x),YTr(topLeft.y)		,depth,1.0f));
	vertices[2].pos=(Vector<4,float>(XTr(topLeft.x),YTr(bottomRight.y)		,depth,1.0f));
	vertices[3].pos=(Vector<4,float>(XTr(bottomRight.x),YTr(bottomRight.y) ,depth,1.0f));

	vertices[0].tint=tint;
	vertices[1].tint=tint;
	vertices[2].tint=tint;
	vertices[3].tint=tint;
	
	
}

Sprite::Sprite(Vector<2> topLeft,Vector<2> bottomRight,Vector<2>topLeftTexture,Vector<2>bottomRightTextue,float depth,Vector<4> tint)
{
	vertices[0].pos=(Vector<4,float>(XTr(topLeft.x),YTr(topLeft.y)			,depth,1.0f));
	vertices[1].pos=(Vector<4,float>(XTr(bottomRight.x),YTr(topLeft.y)		,depth,1.0f));
	vertices[2].pos=(Vector<4,float>(XTr(topLeft.x),YTr(bottomRight.y)		,depth,1.0f));
	vertices[3].pos=(Vector<4,float>(XTr(bottomRight.x),YTr(bottomRight.y) ,depth,1.0f));

	vertices[0].tint=tint;
	vertices[1].tint=tint;
	vertices[2].tint=tint;
	vertices[3].tint=tint;
	this->SetTextureCoords(topLeftTexture,bottomRightTextue);
}

Sprite::~Sprite()
{

}

void Sprite::SetTextureCoords(Vector<2,float> topLeft,Vector<2,float> bottomRight)
{
	vertices[0].tex=Vector<2,float>(topLeft.x,topLeft.y);
	vertices[1].tex=Vector<2,float>(bottomRight.x,topLeft.y);
	vertices[2].tex=Vector<2,float>(topLeft.x,bottomRight.y);
	vertices[3].tex=Vector<2,float>(bottomRight.x,bottomRight.y);
	
}

float Sprite::GetHeight()
{
	return (vertices[0].pos.y-vertices[2].pos.y)/2;
}

float Sprite::GetWidth()
{
	return (vertices[1].pos.x-vertices[0].pos.x)/2;
}

float Sprite::XTr(float x)
{
	return x*2-1;
}

float Sprite::YTr(float y)
{
	return -(y*2-1);
}

float Sprite::iXTr(float x)
{
	return (x+1)/2;
}

float Sprite::iYTr(float y)
{
	return -((y+1)/2);
}