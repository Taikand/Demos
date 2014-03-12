#pragma once
#include "IGUIElement.h"
#include "StaticImage.h"
#include "../States/SpriteString.h"
namespace Tungsten
{
	namespace GUI
	{
		class Label : public IGUIElement
		{
		private:
			StaticImage backImage;
		public:
			SpriteString string;
			Texture& background=backImage.image;
			Label(SpriteFont font);
			void Draw(D3D11SpriteRenderState* graphics);
			void Update(InputState* input);
			void SetDepth(float depth);
			~Label();
		};

	}
}

