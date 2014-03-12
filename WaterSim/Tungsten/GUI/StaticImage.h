#pragma once
#include "IGUIElement.h"
#include "../ServiceLocator.h"
#include "../States/D3D11SpriteRenderState.h"
namespace Tungsten
{
	namespace GUI
	{
		class StaticImage
			:public IGUIElement
		{
		
		public:
			void SetDepth(float depth);
			PPoint position;
			Pixels width;
			Pixels height;
			PRectangle textureCoords;
			Texture image;
			void Update(InputState* input);
			void Draw(D3D11SpriteRenderState* graphics);
			
			StaticImage();
			~StaticImage();
		};
	}
}


