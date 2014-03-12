#pragma once
#include "Event.h"
#include "../DataContainers.h"
#include "../ServiceLocator.h"
#include "../States/D3D11SpriteRenderState.h"
namespace Tungsten
{
	namespace GUI
	{
		class IGUIElement
		{
		protected:
			float depth=0.5f;
			DynamicArray<IGUIElement*> childArray;
			void DrawChild(D3D11SpriteRenderState* graphics);
			void UpdateChild(InputState* input);
		public:
			
			virtual void Update(InputState* input) = 0;
			virtual void Draw(D3D11SpriteRenderState* graphics) = 0;
			virtual void SetDepth(float depth);
			virtual ~IGUIElement()=0;
		};

	}
}


