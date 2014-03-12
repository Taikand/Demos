#pragma once
#include "IGUIElement.h"
#include "StaticImage.h"
#include "Event.h"
namespace Tungsten
{
	namespace GUI
	{
		class SimpleButton :
			public StaticImage
		{
		public:
			Event onClick;
			Event onMouseOver;
			Event onLeftClick;
			SimpleButton()=default;
			SimpleButton& operator=(SimpleButton&) = delete;
			~SimpleButton();
			void Draw(D3D11SpriteRenderState* graphics);
			void Update(InputState* input);
		};

	}
}

