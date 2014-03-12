#include "pch.h"
#include "Cursor.h"

using namespace Tungsten::GUI;
using namespace Tungsten;

Cursor::Cursor()
{
	stateID = 0;
	cursorImage.width = 50;
	cursorImage.height = 50;
	cursorImage.textureCoords = { 0, 0, 0U - 1, 0U - 1 };
	cursorImage.SetDepth(0);
}

Cursor::~Cursor()
{

}

void Cursor::SetState(UINT state)
{
	stateID = state;
	cursorImage.image = states[stateID];
}

UINT Cursor::GetState()
{
	return stateID;
}

void Cursor::Draw(D3D11SpriteRenderState* graphics)
{
	cursorImage.Draw(graphics);
	
	
}

void Cursor::Update(InputState* input)
{
	cursorImage.position = input->mouse.GetMouseCoords();
}

void Cursor::PushState(Texture tex)
{
	states.PushBack(tex);
}

