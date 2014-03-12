#pragma once
#include "..\ServiceLocator.h"
#include "IGUIElement.h"
#include "StaticImage.h"

namespace Tungsten
{
	namespace GUI
	{
		class Cursor : public IGUIElement
		{
		private:
			DynamicArray<Texture> states;
			UINT stateID;
			StaticImage cursorImage;
			
		public:
			
			void SetState(UINT state);
			UINT GetState();
			void PushState(Texture tex);
			void Update(InputState* input);
			void Draw(D3D11SpriteRenderState* graphics);
			Cursor();
			~Cursor();
		};
	}
}



