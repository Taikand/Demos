#pragma once
#include "IGUIElement.h"
namespace Tungsten
{
	namespace GUI
	{
		class GUIFrame : public IGUIElement
		{
		protected:
			D3D11SpriteRenderState frameContext;
		public:
			void Draw(D3D11SpriteRenderState* graphics);
			void Update(InputState* input);
			void Update();
			void Draw();
			void Bind(IGUIElement* elem);
			GUIFrame();
			~GUIFrame();
		};
	}
}


