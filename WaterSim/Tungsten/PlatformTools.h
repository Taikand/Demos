#pragma once
#include "pch.h"
#include <sstream>
#include <string>
#include "DataContainers.h"


extern ::HWND g_mainWindow;
namespace Tungsten
{
	namespace PlatformTools
	{
		
		//Get content of file as array of bytes
		HRESULT CreateByteCodeFromFile(const WCHAR* filename,MemoryBlock* block);
		//Get content of file as string buffer
		HRESULT CreateStringBufferFromFile(const WCHAR* filename,::std::stringstream** p_stringBuff);

	

		HANDLE CreateFileHandle(const WCHAR* filename,int desiredAcces);

		inline void PostError(WCHAR* message=NULL)
		{

			DWORD error=GetLastError();
			if(!error)
			{
#if defined _DESKTOPAPP
				MessageBox(g_mainWindow,L"Undefined Error",L"Error",MB_OK);
#endif
#if defined _WINRTAPP
				Platform::String^ string=ref new Platform::String(L"Undefined Error");
				Windows::UI::Popups::MessageDialog^ dialog=ref new Windows::UI::Popups::MessageDialog(string);
				//dialog->ShowAsync();
#endif
				return;
			}
			WCHAR errorstring[100];
			DWORD errormessage=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_ARGUMENT_ARRAY,
			NULL,error,
			NULL,errorstring,
			100,NULL);

#if defined _DESKTOPAPP
			if(message)
			{
				std::wstring acc;
				acc += message;
				acc += L'\n';
				acc += errorstring;
				MessageBox(g_mainWindow, acc.c_str(),L"Fatal Error",MB_OK);
				return;
			}
			MessageBox(g_mainWindow,errorstring,L"Fatal Error",MB_OK);
			exit(0);
#endif
#if defined _WINRTAPP
			if(message)
			{
				std::wstring accumulator=message;
				accumulator+=L"\n";
				accumulator+=errorstring;
				Platform::String^ string=ref new Platform::String(accumulator.c_str());
				
				Windows::UI::Popups::MessageDialog^ dialog=ref new Windows::UI::Popups::MessageDialog(string);
				//dialog->ShowAsync();
			}
			
#endif
		}

		 enum FileAccess
		 {	
			 Create	=	0x00000001L,
			 Read	=	0x80000000L,
			 Write	=	0x40000000L
		 };
		inline bool Error(HRESULT result)
		{
			if ( FAILED(result) ) return true;
			return false;
		}
		inline bool Error(BOOL result)
		{
			if(!result) return true;
			return false;
		}
		inline void CheckFatalError(HRESULT result)
		{
			if ( FAILED(result) ) PostError();
		}
		inline void CheckFatalError(BOOL result)
		{
			if(!result) PostError();
		}

		//Platform::Array<byte>^ GetBytecodeFromFile(std::wstring filename);
	}
}