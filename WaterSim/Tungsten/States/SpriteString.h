#pragma once
#include "../Services/IImporterService.h"
#include "../DataContainers.h"
#include "SpriteBatch.h"
namespace Tungsten
{
	class SpriteString : public DynamicArray<Sprite>
	{
	private:
		SpriteFont font;
		Pixels size = 16;
		PPoint cursor = { 0, 0 };
		PPoint bounds;
		std::string text;
		float depth = 0.5f;
		Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
	public:

		SpriteString(SpriteFont font);
		SpriteString(SpriteFont font,const char* str);
		const SpriteString& operator=(const char* arg);
		void SetSize(Pixels size);
		void SetCursor(PPoint cursor);
		void SetDepth(float depth);
		void SetColor(Color color);
		void Draw(SpriteBatch* graphics);
		//Returns relative bounds
		PPoint GetBounds();
		
		~SpriteString();
	};
}


