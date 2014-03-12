#include "pch.h"
#include "SimpleButton.h"

using namespace Tungsten;
using namespace Tungsten::GUI;




SimpleButton::~SimpleButton()
{
}

void SimpleButton::Draw(D3D11SpriteRenderState* graphics)
{
	this->StaticImage::Draw(graphics);
}

void SimpleButton::Update(InputState* input)
{
	if (PRectangle{ position.x, position.y, position.x + width, position.y + height }.Contains(input->mouse.GetMouseCoords()))
	{
		if (input->mouse.IsPressed(LButton))
		{
			onClick(this, (EventArgs*)input);
		}
		if (input->mouse.IsPressed(RButton))
		{
			onLeftClick(this, (EventArgs*)input);
		}
		if (!input->mouse.IsPressed(AnyButton))
		{
			onMouseOver(this, (EventArgs*)input);
		}

	}
	
}