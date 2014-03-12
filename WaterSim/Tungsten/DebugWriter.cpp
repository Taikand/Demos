#include "pch.h"
#include "DebugWriter.h"

using namespace Tungsten;

DebugWriter::DebugWriter(WCHAR* vShader,WCHAR* pShader,SpriteFont defaultFont)
:D3D11TextRenderState(vShader,pShader)
{
	debugFont = defaultFont;
	Clear();
}


DebugWriter::~DebugWriter()
{

}

void DebugWriter::Write(char* text)
{
	D3D11CommonState* currentState=Services.Graphics()->GetCurrentState();
	this->Apply();
	DrawString(cursorPos, 4, debugFont, text);
	currentState->Apply();
}

void DebugWriter::Clear()
{
	cursorPos.x = 0;
	cursorPos.y = 0;
}