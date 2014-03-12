#include "pch.h"
#include "D3D11TextRenderState.h"

using namespace Tungsten;



D3D11TextRenderState::D3D11TextRenderState(WCHAR* vShader,WCHAR* pShader)
	:D3D11SpriteRenderState(pShader,vShader)
{
	
}


D3D11TextRenderState::~D3D11TextRenderState()
{
}

Sprite D3D11TextRenderState::MakeCharSprite(Vector<2, float> cursor, float size, SpriteCharData charData)
{

	float height = (float)charData.height;
	float width = (float)charData.width;
	width = size*width / height;
	height = size;

	Sprite ret = Sprite(Vector<2, float>(cursor.x, cursor.y), Vector<2, float>(cursor.x + width, cursor.y + height), 0.01f);
	ret.SetTextureCoords(
		Vector<2, float>((float)charData.x, (float)charData.y),
		Vector<2, float>((float)charData.x + charData.width, (float)charData.y + charData.height)
		);
	return ret;

}

void D3D11TextRenderState::DrawString(Vector<2, float>& cursor, float size, SpriteFont font, char* string, float allign)
{
	this->Begin();
	char* iterator=string;
	//TODO : DOES NOT DO ANYTHING
	while(*iterator!=0)
	{
		//Skip all new line characters
		if(*iterator!='/n')
		iterator++;
		
	}
	int stringWidth=iterator-string;
	
	
	int index;
	//Normalise
	size=size/100;

	SpriteCharData currentChar;
	for(index=0;index<stringWidth;index++)
	{
		currentChar=(*font).charData[(unsigned char)string[index]];
		if(string[index]=='\n')
		{
			cursor.y+=size;
			cursor.x=allign;
		}
		else
		{
			Sprite s=MakeCharSprite(cursor,size,currentChar);
			this->Draw((*font).texture, s);
			cursor.x+=s.GetWidth();
		}
	}

	this->End();
}
void D3D11TextRenderState::DrawStringCentered(Vector<2, float> center, float size, SpriteFont font, char* string)
{
	
	char* iterator=string;
	while(*iterator!=0)
	{
		//Skip all new line characters
		if(*iterator!='/n')
		iterator++;
		
	}
	int stringWidth=iterator-string;
	
	int index;
	//Normalise
	size=size/100;

	Vector<2,float> currentCursor;
	// TODO: remove
	currentCursor.y=0;
	currentCursor.x=0;

	float maxWidth=0;
	SpriteCharData currentChar;
	//Get the cursor for centering the text
	for(index=0;index<stringWidth;index++)
	{
		currentChar=font->charData[(unsigned char)string[index]];
		if(string[index]=='\n')
		{
			currentCursor.y+=size;
			currentCursor.x=0;
		}
		else
		{
			currentCursor.x+=size*currentChar.width /currentChar.height;
			if(maxWidth<currentCursor.x) maxWidth=currentCursor.x;
		}
	}
	currentCursor.x=center.x-maxWidth/2;

	currentCursor.y=center.y-currentCursor.y/2;
	DrawString(currentCursor,size*100,font,string,currentCursor.x);
}

