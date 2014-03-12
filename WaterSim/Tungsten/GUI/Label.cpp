#include "pch.h"
#include "Label.h"

namespace Tungsten
{
	namespace GUI
	{
		Label::Label(SpriteFont font)
			: string(font, "")
		{
			string.SetDepth(depth - 0.1f);
		}

		void Label::Draw(D3D11SpriteRenderState* graphics)
		{
			backImage.width = string.GetBounds().x;
			backImage.height = string.GetBounds().y;
			backImage.Draw(graphics);
			string.Draw(graphics);

		}

		void Label::Update(InputState* input)
		{

		}
		void Label::SetDepth(float depth)
		{
			this->depth = depth;
			backImage.SetDepth(depth);
			string.SetDepth(depth - 0.1f);
		}

		Label::~Label()
		{
		}
	}
	

}
