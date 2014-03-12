#pragma once
#include <pch.h>

#include "../DataContainers.h"

namespace Tungsten
{

struct SpriteVertex
{
	//Screen Position
	Vector<4,float> pos;
	//The position to be sampled from the texture
	Vector<2,float> tex;
	//Tint to change colour
	Vector<4,float> tint;
	
};
//All messages to/from this class are defined in UV Space
class Sprite
{
private:
	
	//UV Space to screen space transform
	inline float XTr(float x);
	inline float YTr(float y);
	//Inverses
	inline float iXTr(float x);
	inline float iYTr(float y);
public:
	SpriteVertex vertices[4];
	Sprite();
	
	Sprite(Vector<2> topLeft, Vector<2> bottomRight, float depth = 1, Vector<4> tint = { 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite(Vector<2> topLeft, Vector<2> bottomRight, Vector<2>topLeftTexture, Vector<2>bottomRightTextue, float depth = 1, Vector<4> tint = { 1.0f, 1.0f, 1.0f, 1.0f });
	void SetTextureCoords	(Vector<2,float> topleft,Vector<2,float> bottomright);
	float GetWidth();
	float GetHeight();
	~Sprite					(void);
	
};

}

