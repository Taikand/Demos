#include "pch.h"
#include "IGUIElement.h"

using namespace Tungsten::GUI;
using namespace Tungsten;


IGUIElement::~IGUIElement()
{
	for (unsigned int i = 0; i < childArray.GetSize(); i++)
	{
		delete childArray[i];
	}
}

void IGUIElement::DrawChild(D3D11SpriteRenderState* graphics)
{
	for (unsigned int i = 0; i < childArray.GetSize(); i++)
	{
		childArray[i]->Draw(graphics);
	}
}

void IGUIElement::UpdateChild(InputState* input)
{
	for (unsigned int i = 0; i < childArray.GetSize(); i++)
	{
		childArray[i]->Update(input);
	}
}

void IGUIElement::SetDepth(float depth)
{
	this->depth = depth;
}