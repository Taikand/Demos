#include "pch.h"
#include "Event.h"

namespace Tungsten
{
	namespace GUI
	{
		void NullEventFunction(IGUIElement*, EventArgs*)
		{

		}
		Event::Event()
		{
			this->implEvent::operator=(NullEvent);
		}
		Event::Event(implEvent& ref)
		{
			this->implEvent::operator=(ref);
		}
		Event& Event::operator=(void(*func)(IGUIElement*, EventArgs*))
		{
			this->implEvent::operator=(func);
			return *this;
		}
		Event::Event(void(*func)(IGUIElement*, EventArgs*))
		{
			this->implEvent::operator=(func);
		}
		

		Event NullEvent = NullEventFunction;
	}
}