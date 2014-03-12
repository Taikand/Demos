#include "pch.h"
#include "GUIFrame.h"

using namespace Tungsten::GUI;
using namespace Tungsten;

GUIFrame::GUIFrame()
:frameContext(L"Assets\\Shaders\\PSSpriteRender.cso", L"Assets\\Shaders\\VSSpriteRender.cso")
{
}


GUIFrame::~GUIFrame()
{
}

void GUIFrame::Draw(D3D11SpriteRenderState* graphics)
{
	DrawChild(graphics);
}

void GUIFrame::Draw()
{
	if (childArray.GetSize() == 0) return;
	frameContext.Apply();
	frameContext.Begin();
	Draw(&frameContext);
	frameContext.End();
}

void GUIFrame::Update(InputState* input)
{
	UpdateChild(input);
}

void GUIFrame::Update()
{
	InputState* input = Services.Input();
	Update(input);
}

void GUIFrame::Bind(IGUIElement* elem)
{
	this->childArray.PushBack(elem);
}
