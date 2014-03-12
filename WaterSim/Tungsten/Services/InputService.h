#pragma once
#include "pch.h"
#include "../DataContainers.h"

namespace Tungsten
{
	enum MouseButton
	{
		LButton = 0x1,
		RButton = 0x2,
		MButton = 0x4,

		//Left Button	
		Button1 = 0x1,
		//Right Button	
		Button2 = 0x2,
		//Middle Button	
		Button3 = 0x4,

		//XButton 1		
		Button4 = 0x8,
		//XButton 2		
		Button5 = 0x10,

		AnyButton = 0x1F
	};

	class InputService
	{
	private:
		int index;


	public:
		class tag_keyboard
		{
		private:
			UINT keys[256];
		public:
			void Push(UINT vKey);
			void Pop(UINT vKey);
			bool IsPressed(UINT vKey);
			bool IsPressed(char c);
			friend class InputService;
		} keyboard;
		class tag_mouse
		{
		private:
			SHORT wheelDelta;
			USHORT buttonFlags;
			Tungsten::Vector<2, long> position;
			Tungsten::Vector<2, long> movement;
		public:
			void SetFlags(USHORT mouseButtonFlags);
			bool IsPressed(MouseButton button);
			void SetCursor(LONG x, LONG y);
			void SetPosition(LONG x, LONG y);
			void SetMovement(LONG x, LONG y);
			Tungsten::Vector<2, long> GetMouseCoords();
			Tungsten::Vector<2, long> GetMouseMovement();
			short GetWheelDelta();
			void SetWheelDelta(SHORT wheelDelta);
			friend class InputService;

		} mouse;

		InputService();
		~InputService(void);
		void Initialise(HWND windowHandle);
		//Pass the lParam of the WM_INPUT event for processing
		void Refresh();
#if defined _WINRTAPP

#endif
#if defined _DESKTOPAPP
		RAWINPUTDEVICE inputDevices[2];
		void HandleInputEvent(LPARAM lParam);
#endif
	};
	typedef InputService InputState;


}

