#include "pch.h"

#include "..\ServiceLocator.h"
#include "AssetLoader.h"

using namespace Tungsten;




		



 
//void SpriteTextService::DebugWrite( char* text)
//{
//	//Services.Graphics()->PSSetShaderResource( ((tag_SpriteFont*)debugFont)->texture.shaderView,0);
//	DrawString(cursorPos,4,debugFont,text);
//}
//
//
//
//void SpriteTextService::DrawString(Vector<2,float>& cursor,float size,SpriteFont font,char* string,float allign)
//{
//	//SpriteFont::implSpriteFont* p=reinterpret_cast<SpriteFont::implSpriteFont*>(font);
//	//SpriteFont::SpriteChar* charData=p->charData;
//	//char* iterator=string;
//	//while(*iterator!=0)
//	//{
//	//	//Skip all new line characters
//	//	if(*iterator!='/n')
//	//	iterator++;
//	//	
//	//}
//	//int stringWidth=iterator-string;
//	//Sprite* data=new Sprite[stringWidth];
//	//UINT32* vertexIndex=new UINT32[stringWidth*6];
//	//
//	//int index;
//	////Normalise
//	//size=size/100;
//
//	//SpriteFont::SpriteChar currentChar;
//	//for(index=0;index<stringWidth;index++)
//	//{
//	//	currentChar=charData[(unsigned char)string[index]];
//	//	if(string[index]=='\n')
//	//	{
//	//		cursor.y+=size;
//	//		cursor.x=allign;
//	//	}
//	//	else
//	//	{
//	//		font.MakeCharSprite(cursor,size,currentChar,data+index);
//	//		vertexIndex[index*6+0]=index*4+0;
//	//		vertexIndex[index*6+1]=index*4+1;
//	//		vertexIndex[index*6+2]=index*4+2;
//	//		vertexIndex[index*6+3]=index*4+2;
//	//		vertexIndex[index*6+4]=index*4+1;
//	//		vertexIndex[index*6+5]=index*4+3;
//	//		cursor.x+=data[index].GetWidth();
//	//	}
//	//}
//	////Direct Drawing TODO: get this out
//	//MemoryBlock dataBlock;
//	//dataBlock.ptr=data;
//	//dataBlock.width =(stringWidth)*sizeof(Sprite);
//	//MemoryBlock indexBlock;
//	//indexBlock.ptr=vertexIndex;
//	//indexBlock.width =(stringWidth)*6*sizeof(UINT32);
//	////TODO
//	////Services.Graphics()->SetBuffers(dataBlock,indexBlock);
//	////Services.Graphics()->DrawIndexed(stringWidth*6,0,0);
//	//delete[] data;
//	//delete[] vertexIndex;
//
//}
//
//void SpriteTextService::DrawStringCentered(Vector<2,float> center,float size,SpriteFont font,char* string)
//{
//	//SpriteFont::implSpriteFont* p=reinterpret_cast<SpriteFont::implSpriteFont*>(font);
//	//SpriteFont::SpriteChar* charData=p->charData;
//	//char* iterator=string;
//	//while(*iterator!=0)
//	//{
//	//	//Skip all new line characters
//	//	if(*iterator!='/n')
//	//	iterator++;
//	//	
//	//}
//	//int stringWidth=iterator-string;
//	//
//	//int index;
//	////Normalise
//	//size=size/100;
//
//	//Vector<2,float> currentCursor;
//	//// TODO: remove
//	//currentCursor.y=0;
//	//currentCursor.x=0;
//
//	//float maxWidth=0;
//	//SpriteFont::SpriteChar currentChar;
//	////Get the cursor for centering the text
//	//for(index=0;index<stringWidth;index++)
//	//{
//	//	currentChar=charData[(unsigned char)string[index]];
//	//	if(string[index]=='\n')
//	//	{
//	//		currentCursor.y+=size;
//	//		currentCursor.x=0;
//	//	}
//	//	else
//	//	{
//	//		currentCursor.x+=size*currentChar.width /currentChar.height;
//	//		if(maxWidth<currentCursor.x) maxWidth=currentCursor.x;
//	//	}
//	//}
//	//currentCursor.x=center.x-maxWidth/2;
//
//	//currentCursor.y=center.y-currentCursor.y/2;
//	//DrawString(currentCursor,size*100,font,string,currentCursor.x);
//}
//
//SpriteTextService::SpriteTextService()
//{
//	debugFont=LoadSpriteFont(L"Assets\\Fonts\\Arial.bfd",L"Assets\\Fonts\\Arial.png");
//	cursorPos.x=0;
//	cursorPos.y=0;
//}
//
//SpriteTextService::~SpriteTextService()
//{
//	cursorPos.x=0;
//	cursorPos.y=0;
//}
//
//void SpriteTextService::DebugClear()
//{
//	cursorPos.x=0;
//	cursorPos.y=0;
//}