#pragma once
#include <functional>
#include "../Services/InputService.h"

namespace Tungsten
{
	namespace GUI
	{
		struct EventArgs
		{
			InputState* input;
		};
		class IGUIElement;
		class Event : public std::function<void(IGUIElement*, EventArgs*)>
		{
		private:
			typedef std::function<void(IGUIElement*, EventArgs*)> implEvent;
		public:
			Event();
			Event(void(*func)(IGUIElement*, EventArgs*));
			Event(implEvent& ref);
			Event& operator=(void(*func)(IGUIElement*, EventArgs*) );
			template<typename T>
			void Bind(void(T::*func)(IGUIElement*, EventArgs*) , T* thisPtr)
			{
				this->implEvent::operator=(std::bind(func,thisPtr, std::placeholders::_1, std::placeholders::_2));
			}
		};
		//typedef std::function<void(IGUIElement*, EventArgs*)> Event;
		
		extern Event NullEvent;
	}
}
